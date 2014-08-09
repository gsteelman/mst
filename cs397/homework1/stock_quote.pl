# BEGINNING OF FILE
#------------------------------------------------------------------------------
# @file - stock_quote.pl
# @auth - Gary Steelman
# @desc - Retreives quotes of stocks from the Yahoo quote server.
# @edit - 9/14/2010
#------------------------------------------------------------------------------

use LWP::UserAgent;
use Time::localtime;
use Date::Calc qw(:all);
use Date::Manip;
use Switch;

#------------------------------------------------------------------------------
# @func - checkArgs
# @desc - Checks the command line arguments passed at run time for correctness
#           and parses them into useable formats
#------------------------------------------------------------------------------
sub procArgs
{
  my $tDate = 0;
  my $bDate = 0;
  my $eDate = 0;
  
  #0 or less arguments passed on the command line
  if ( (scalar @ARGV) <= 0 )
  {
    &printHelp;
    die;
  }
 
  #Process each command passed on the command line in order of their passage
  # for ( my $argnum = 0; $argnum <= $#ARGV; $argnum++ )
  for ( my $argnum = 0; $argnum <= (scalar @ARGV); $argnum++ )
  {
    #help file requested
    if ( lc( $ARGV[$argnum] ) eq "-help" )
    {
      &printHelp;
      die;
    }
    
    #stock symbol flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-s" )
    {
      #Last argument supplied with no stock symbol after 
      #OR the next argument starts with a -, implying there is a missing stock symbol
      if ( (($argnum + 1) > (scalar @ARGV)) || (substr($ARGV[$argnum + 1], 0, 1) eq "-") )
      {
        die "You must put the stock symbol after the -s flag\n";
      }
      
      else
      {
        push( @qd_stockSymbols, $ARGV[$argnum + 1] );
        $argnum++;
      }
      
      if ( $qd_stockSymbols[0] eq "" )
      {
        die "The stock symbol provided is invalid\n";
      }
    }
    
    #today flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-t" )
    {
      $tDate = 1;
      
      $qd_bDateArr[0] = localtime->mon + 1;
      $qd_bDateArr[1] = localtime->mday;
      $qd_bDateArr[2] = localtime->year + 1900;
      $qd_eDateArr[0] = localtime->mon + 1;
      $qd_eDateArr[1] = localtime->mday;
      $qd_eDateArr[2] = localtime->year + 1900;
    }
    
    #beginning date flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-b" )
    {
      $bDate = 1;      
      
      #Last argument supplied with no date after
      if ( ($argnum + 1) > (scalar @ARGV) )
      {
        die "You must put the beginning date after the -b flag\n";
      }
      
      else
      {
        #parse the beginning date, make sure it is a valid date
        #split on / . - _
        @qd_bDateArr = split( /[\/\.\-_]/, $ARGV[$argnum + 1] );
        $argnum++;
        
        if ( check_date( int $qd_bDateArr[2], int $qd_bDateArr[0], int $qd_bDateArr[1] ) == 0 )
        {
          die "The beginning date supplied is not a valid date\n";
        }
      }
    }
    
    #ending date flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-e" )
    {
      $eDate = 1;      
      
      #Last argument supplied with no date after
      if ( ($argnum + 1) > (scalar @ARGV) )
      {
        die "You must put the ending date after the -e flag\n";
      }
      
      else
      {
        #parse the ending date, make sure it is a valid date
        #split on / . - _
        @qd_eDateArr = split( /[\/\.\-_]/, $ARGV[$argnum + 1] );
        $argnum++;
        
        if ( check_date( int $qd_eDateArr[2], int $qd_eDateArr[0], int $qd_eDateArr[1] ) == 0 )
        {
          die "The ending date supplied is not a valid date\n";
        }
      }
    }
    
    #path flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-p" )
    {
      #Last argument supplied with no path after
      if ( ($argnum + 1) > (scalar @ARGV) )
      {
        die "You must put the output path after the -p flag\n";
      }
      
      else
      {
        $qd_outPath = $ARGV[$argnum + 1];
        $argnum++;
      }
    }
    
    #header flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-h" )
    {
      $qd_printHeader = 1;
    }
    
    #delete previous records flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-d" )
    {
      $qd_delPrev = 1;
    }
    
    #adjust prices flag flipped
    elsif ( lc( $ARGV[$argnum] ) eq "-a" )
    {
      $qd_adjPrices = 1;
    }
  }
  
  #Ensure that the beginning and ending dates were supplied together
  #and not with the today flag, etc.
  if ( ($bDate == 1 && $eDate == 0)
    || ($bDate == 0 && $eDate == 1)
    || (($bDate == 1 || $eDate == 1) && $tDate == 1)
     )
  {
    die "You must supply both a beginning and ending date together OR you may use today's date\n";
  }
  
  #Ensure that the ending date is the same as or after the beginning date.
  if ( ($bDate == 1) && ($eDate == 1) )
  {
    if ( &Date_Cmp( getPrettyDate( \@qd_bDateArr ), getPrettyDate( \@qd_eDateArr ) ) > 0 )
    {
      die "The ending date entered is before the starting date\n";
    }
  }
  
  #If a stock symbol was not supplied, prompt for entrance of symbols from STDIN
  if ( $qd_stockSymbols[0] eq "" )
  {
    print "\nPlease list the stock symbols for the quotes to retrieve. Must be separated by a single space a - or a _\n";
    print "Like this: GOOG-SPY_IGRSX VBIIX\n";
    
    #Requires STDIN to be defined, will not work when run from a web browser!
    chomp( my $userSymbols = <STDIN> );
    
    if ( $userSymbols eq "" )
    {
      die "The stock symbos provided are invalid\n";
    }
    
    @qd_stockSymbols = split( /[\/\.\-_ ]/, $userSymbols );
  }
}

#------------------------------------------------------------------------------
# @func - printHelp
# @desc - Print the help information for how to use this script properly
#------------------------------------------------------------------------------
sub printHelp
{
  print "==================== Help file: ====================\n";
  print "How to run this program: \n\n";
  print "perl stock_quote.pl -s SYM -t | -b MM.DD.YYYY -e MM.DD.YYYY -p \"path/subdirectory\" [other flags]\n\n";
  print "-s\tSpecify the stock symbol to retreive data for.\n";
  print "\tOmit this option to be prompted for a list of symbols.\n";
  print "-t\tGet today's quote data.\n";
  print "-b\tSpecify the start date for quote data retreival in the format \"MM.DD.YYYY\"\n";
  print "\tMust be used with -e and cannot be used with -t\n";
  print "\tMM, DD, and YYYY do not need to be the specified length\n";
  print "-e\tSpecify the end date for quote data retreival in the format \"MM.DD.YYYY\"\n";
  print "\tMust be used with -b and cannot be used with -t\n";
  print "\tMM, DD, and YYYY do not need to be the specified length\n";
  print "\tYou may use . / - _ characters to separate the number values\n";
  print "-p\tThe directory where to store the quote data. Must end in a / and be surrouned by \"\"s\n";
  print "-h\tInclude the table header in the output.\n";
  print "-d\tDelete the current quote data and store the newly retreived data.\n";
  print "\tOmit this option to append the retreived data to the previous data.\n";
  print "-a\tAdjust the quote data to scale to the adjusted close.\n";
  print "-help\tDisplay this help file.\n";
  print "\tOmitting all arguments at the command line will also display this help file.\n";
  print "\tAll arguments may be submitted in upper or lower case and will be accepted either way.\n";
}

#------------------------------------------------------------------------------
# @func - getPrettyDate
# @desc - Returns a string of the passed in date in a pretty format
# @pre  - Assumes the array passed in has 3 elements
#         [0] = month 
#         [1] = day
#         [2] = year
#------------------------------------------------------------------------------
sub getPrettyDate 
{
  # @localDate = @{$_[0]};
  # $localDate[0] . "." . $localDate[1] . "." . $localDate[2];
  
  #This way is shorter and faster, but less clear
  return ( $_[0]->[0] . "/" . $_[0]->[1] . "/" . $_[0]->[2] );
}

#------------------------------------------------------------------------------
# @func - getQuoteData
# @desc - Queries the Yahoo.com financial servers for the requested stock's
#           data given the different parameters. 
# @pre  - procArgs has been run and completed
#------------------------------------------------------------------------------
sub getQuoteData
{
  my @qd_result;
  my $qd_queryURL = "";
  
  foreach $stockSymbol ( @qd_stockSymbols )
  {
    # Create the URL to query with
    $qd_queryURL  = "http://chart.yahoo.com/table.csv";
    $qd_queryURL .= ("?s=" . uc( $stockSymbol ));
    $qd_queryURL .= ("&a=" . int ($qd_bDateArr[0] - 1));
    $qd_queryURL .= ("&b=" . int $qd_bDateArr[1]);
    $qd_queryURL .= ("&c=" . int $qd_bDateArr[2]);
    $qd_queryURL .= ("&d=" . int ($qd_eDateArr[0] - 1));
    $qd_queryURL .= ("&e=" . int $qd_eDateArr[1]);
    $qd_queryURL .= ("&f=" . int $qd_eDateArr[2]);
    $qd_queryURL .= "&g=d&q=q&y=0&z=dis&x=.csv";
    
    print $qd_queryURL . "\n";
    
    # Fetch server data using our URL
    my $ua        = new LWP::UserAgent;
    my $req       = new HTTP::Request 'GET', $qd_queryURL;
    
    # Store this stock's results in an index
    push( @qd_result, $ua->request($req)->content );
  }
  
  return ( @qd_result );
}

#------------------------------------------------------------------------------
# @func - adjQuoteData
# @desc - Adjusts the quote data to the adjusted ending price
# @pre  - Assumes that the quote data is in a specified format
#         [0] = date
#         [1] = open
#         [2] = high
#         [3] = low
#         [4] = close
#         [5] = volume
#         [6] = adj close
#------------------------------------------------------------------------------
sub adjQuoteData
{
  # Adjust the quote data based on the adjusted closing price
  my $ratio  = $_[0]->[6] / $_[0]->[4]; # Adjusted close / Actual close
  $_[0]->[1] = $_[0]->[1] * $ratio;     # Adjusted open
  $_[0]->[2] = $_[0]->[2] * $ratio;     # Adjusted high
  $_[0]->[3] = $_[0]->[3] * $ratio;     # Adjusted low
  $_[0]->[4] = $_[0]->[6];              # Adjusted close instead of Actual close
}

#------------------------------------------------------------------------------
# @func - monthNumToChars
# @desc - converts a month number to its 3 letter abbreviation
#------------------------------------------------------------------------------
sub monthNumToChars
{
  switch ( $_[0] )
  {
    case "01" { return "Jan"; }
    case "02" { return "Feb"; }
    case "03" { return "Mar"; }
    case "04" { return "Apr"; }
    case "05" { return "May"; }
    case "06" { return "Jun"; }
    case "07" { return "Jul"; }
    case "08" { return "Aug"; }
    case "09" { return "Sep"; }
    case "10" { return "Oct"; }
    case "11" { return "Nov"; }
    case "12" { return "Dec"; }
    else    { return "UNK"; }
  }
}

#------------------------------------------------------------------------------
# @func - main
# @desc - The main body of this script
#------------------------------------------------------------------------------
# Variables for use from command line.
@qd_stockSymbols;
@qd_bDateArr;
@qd_eDateArr;
$qd_outPath     = "";
$qd_outExt      = ".csv";
$qd_printHeader = 0;
$qd_delPrev     = 0;
$qd_adjPrices   = 0;

# Process the command line arguments
&procArgs;

print "Retrieving quote data from the server. If this takes more than a few seconds kill the script and try again, the server has stalled in answering.\n";

my @httpQueryResult = &getQuoteData;

# Reformat output to specific style and output to desired location
for ( my $i = 0; $i < (scalar @httpQueryResult); $i++ )
{    
  my @output;
  
  # Handle 404 for misspelled or nonexistent stock ticker symbol
  if ( ($httpQueryResult[$i] =~ /404 Not Found/) 
    || ($httpQueryResult[$i] eq "") 
    || ($httpQueryResult[$i] eq "Date,Open,High,Low,Close,Volume,Adj Close\n") 
    )
  {
    push( 
      @output, 
      "No quote data for the stock @qd_stockSymbols[$i] found. Check the symbol and dates and try again.\n" 
      );
  }
  
  else
  {
    # If header was requested
    if ( $qd_printHeader == 1 )
    {
      push( @output, "Open,High,Low,Close,Volume,Date\n" );
    }
  
    # Split the current quote's results into individual lines for easier transformation
    my @currStockQuote = split( /\n/, $httpQueryResult[$i] );
    
    # For each line of results in the stock quote data
    for ( my $j = 0; $j <= (scalar @currStockQuote - 1); $j++ )
    {    
      # Split the line's CSVs into separate values
      my @currStockQuoteDay = split( /,/, @currStockQuote[(scalar @currStockQuote - $j - 1)] );
      
      my $reformattedLine = "";
      
      # Adjust the numbers for the quote if requested
      if ( $qd_adjPrices == 1 )
      {
        adjQuoteData( \@currStockQuoteDay );
      }
      
      $reformattedLine = sprintf( "%.2f", $currStockQuoteDay[1] )  # Open
                 . "," . sprintf( "%.2f", $currStockQuoteDay[2] )  # High
                 . "," . sprintf( "%.2f", $currStockQuoteDay[3] )  # Low
                 . "," . sprintf( "%.2f", $currStockQuoteDay[4] )  # Close
                 . "," . $currStockQuoteDay[5];                    # Vol
      
      # Split up the date to piece back together
      my @currStockQuoteDayDate = split( /-/, @currStockQuoteDay[0] );
      
      $reformattedLine .= "," . (int $currStockQuoteDayDate[2])    # Day
                        . " " . monthNumToChars( $currStockQuoteDayDate[1] ) # Month as 3 letters
                        . " " . $currStockQuoteDayDate[0];         # Year
      
      push( @output, ($reformattedLine . "\n") );
    }
  }
  
  # Clean up the output path, change \ to /, append a / if one does not exist
  $qd_outPath =~ s/\\/\//;
  $qd_outPath =~ s/ /%20/;
  chomp( $qd_outPath );
  if ( rindex( $qd_outPath, "/" ) != (length( $qd_outPath ) - 1) )
  {
    $qd_outPath .= "/";
  }

  # Put the output to where it needs to go
  if ( $qd_outPath eq "" )
  {
    print "@output";
  }

  # Delete previous quotes
  elsif ( $qd_delPrev == 1 )
  {
    open( OUT_FILE, ">" . $qd_outPath . uc( $qd_stockSymbols[$i] ) . $qd_outExt ) or die $!;
    print OUT_FILE "@output";
    close OUT_FILE or die $!;
  }

  # Don't delete previous quotes
  else
  {
    open( OUT_FILE, ">>" . $qd_outPath . uc( $qd_stockSymbols[$i] ) . $qd_outExt ) or die $!;
    print OUT_FILE "@output";
    close OUT_FILE or die $!;
  }
}

print "Stock data retrieval successful.\n";

# END OF FILE