# @file QuotePlugin.pm
# @desc Working through the tutorial here:
#       http://twiki.org/cgi-bin/view/TWiki/HowToMakeSimpleTWikiPlugin

package TWiki::Plugins::QuotePlugin;

# Always use strict to enforce variable scoping
use strict;

require TWiki::Func;    # The plugins API
require TWiki::Plugins; # For the API version

use vars qw( $VERSION $RELEASE $SHORTDESCRIPTION $debug $pluginName $NO_PREFS_IN_TOPIC );
no warnings;

$VERSION = '$Rev: 15942 (29 Apr 2009) $';
$RELEASE = 'The Quote Machine';
$SHORTDESCRIPTION = 'Stock quote rendering from Yahoo! servers.';
$NO_PREFS_IN_TOPIC = 1;
$pluginName = 'QuotePlugin';

sub initPlugin
{
  my( $topic, $web, $user, $installWeb ) = @_;

  # Register our functions.
  TWiki::Func::registerTagHandler( 'QUOTE', \&_QUOTE );
  TWiki::Func::registerTagHandler( 'QUOTEDOWNLOAD', \&_QUOTEDOWNLOAD );

  if( $TWiki::Plugins::VERSION < 1.1 ) {
      TWiki::Func::writeWarning( "This version of $pluginName works only with TWiki 4 and greater." );
      return 0;
  }

  # Get plugin debug flag
  $debug = TWiki::Func::getPreferencesFlag( "\U$pluginName\E_DEBUG" );

  # Plugin correctly initialized
  TWiki::Func::writeDebug( "- TWiki::Plugins::${pluginName}::initPlugin( $web.$topic ) is OK" ) if $debug;

  return 1;
}

# Don't believe we need anything in this one, since the form
# is on the TWiki page itself.
# sub preRenderingHandler
# {
  ### my ( $text ) = @_;   # do not uncomment, use $_[0], $_[1] instead

  # my ( $cnt, $attr ) = @_;
  # my $session = $TWiki::Plugins::SESSION;

  # $attr = new TWiki::Attrs($attr);
  # my $lbl = TWiki::Func::getPreferencesValue( "\U$TWiki::Plugins::SignaturePlugin::pluginName\E_SIGNATURELABEL" ) || 'Sign';

  # my $name = '';
  # $name = '_('.$attr->{name}.')_ &nbsp;' if $attr->{name};

  # return "<form name=\"Quote\" action=\"%TOPICURL%\" method=\"get\"> Symbols: <input type=\"text\" name=\"Symbols\" /><input type=\"submit\" value=\"Submit\" /></form>";
  # return 1;
# }

my @CommandLineArguments = ();

sub _QUOTE
{
  my($session, $params, $theTopic, $theWeb) = @_;
  # params is an array of each parameter specified in the {}s in the TWiki topic.

  # Set the "global" variables below like $PrintHeader appropriately for this call
  populateCommandLineArguments($session, $params, $theTopic, $theWeb);

  # Query, Process, and Return the results.
  return QuotePluginMain();
}

sub _QUOTEDOWNLOAD
{
  my($session, $params, $theTopic, $theWeb) = @_;
  # params is an array of each parameter specified in the {}s in the TWiki topic.

  # Set the "global" variables below like $PrintHeader appropriately for this call
  populateCommandLineArguments($session, $params, $theTopic, $theWeb);

  # return (#print $params);
  # return (#print @CommandLineArguments);

  my $OutputFile;

  #check to see if we should overwrite an existing file or just append
  $OutputFile = ">/home/miner012/gamewarp/working/Stock_Quotes_GOOG_test.csv";

  my $to_file = QuotePluginMain();

  #check to see if we are printing out the full quotes or the headerless quotes
  open OUTPUT, $OutputFile or ( return $! );
    print OUTPUT $to_file;
  close OUTPUT;


  # Query, Process, and Return the results.
  return $to_file;

}

sub populateCommandLineArguments
{
  my($session, $params, $theTopic, $theWeb) = @_;

  # Grab the symbol, else make it blank if it doesn't exist in the parameter list
  my $Symbol = $params->{"Symbol"} || '';
  if ( $Symbol ne '' )
  {
    push( @CommandLineArguments, "-s" );
    push( @CommandLineArguments, $Symbol );
  }

	my $Beginningdate = $params->{"Beginningdate"} || '';
  if ( $Beginningdate ne '' )
  {
    push( @CommandLineArguments, "-start" );
    push( @CommandLineArguments, $Beginningdate );
  }

	my $Enddate = $params->{"Enddate"} || '';
  if ( $Enddate ne '' )
  {
    push( @CommandLineArguments, "-end" );
    push( @CommandLineArguments, $Enddate );
  }

  my $Today = $params->{"Today"} || '';
  if ( $Today eq '1' )
  {
    push( @CommandLineArguments, "-t" );
  }

  my $Header = $params->{"Header"} || '';
  if ( $Header eq '1' )
  {
    push( @CommandLineArguments, "-h" );
  }

  my $Adjusted = $params->{"Adjusted"} || '';
  if ( $Adjusted eq '1' )
  {
    push( @CommandLineArguments, "-a" );
  }

  my $Filepath = $params->{"Filepath"} || '';
  if ( $Filepath ne '' )
  {
    push( @CommandLineArguments, "-f" );
    push( @CommandLineArguments, ($Filepath . "/") );
  }

  my $Overwrite = $params->{"Overwrite"} || '';
  if ( $Overwrite ne '' )
  {
    push( @CommandLineArguments, "-d" );
  }
}

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
#!/usr/bin/perl
# AUTHOR: Stewart Sanchez
# DATE: 9/15/2010
# FILE: hw1_cs397_stock_quotes.pl

use LWP::UserAgent;
use strict;

#####################
#
#  GLOBAL VARIABLES
#
#####################
my $TRUE = 1;
my $FALSE = 0;

my @MONTH_ABBREVIATIONS = qw(Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec);

my $PrintHeader = $FALSE;
my $OutputToFile = $FALSE;
my $OverwriteFile = $FALSE;
my $TodayOnlySpecified = $FALSE;
my $StartDateSpecified = $FALSE;

my @Symbols = ();
my $OutputDirectory;
my $StartDay;
my $StartMonth;
my $StartYear;
my $EndDay;
my $EndMonth;
my $EndYear;
my $AdjustedData;

my $QueryResultsErrorFlag;
my $OriginalQuotes;
my $ReformattedQuotes;

#####################
#
#  SUB ROUTINES
#
#####################
sub read_command_line_arguments
{
  #loop through all of the command line arguments
  foreach my $ArgNum (0 .. $#CommandLineArguments)
  {
    ##print out help information
    if($CommandLineArguments[$ArgNum] eq "-help")
    {
      print_help_information();
    }

    #determine what symbol to look for
    elsif($CommandLineArguments[$ArgNum] eq "-s")
    {
		  my $CheckingForSymbols = $TRUE;
		  do
			{
				#check to see if the following token is indeed a symbol
				$ArgNum++;
				if($ArgNum <= $#CommandLineArguments && $CommandLineArguments[$ArgNum] !~ /^-/)
				{

          @Symbols = split(/[\/\.\-_ ]/, $CommandLineArguments[$ArgNum]);

					#push(@Symbols, $CommandLineArguments[$ArgNum]);
				}
				else
				{
					$CheckingForSymbols = $FALSE;
				}
			} while($CheckingForSymbols == $TRUE)
    }

    #determine if the header line should be printed out
    elsif($CommandLineArguments[$ArgNum] eq "-h")
    {
      $PrintHeader = $TRUE;
    }

    #determine if the quote data is to be adjusted
    elsif($CommandLineArguments[$ArgNum] eq "-a")
    {
      $AdjustedData = $TRUE;
    }


    #determine if the header line should be printed out
    elsif($CommandLineArguments[$ArgNum] eq "-f")
    {
      #check to see if the following token is indeed a file path
      $ArgNum++;
      if($ArgNum <= $#CommandLineArguments && $CommandLineArguments[$ArgNum] !~ /^-/)
      {
        $OutputToFile = $TRUE;
        $OutputDirectory = $CommandLineArguments[$ArgNum];
      }
      else
      {
        #print "No file path was specified, will #print to standard output...\n";
      }
    }

    #determine if an existing file for the specified symbol should be overwritten or appended
    elsif($CommandLineArguments[$ArgNum] eq "-d")
    {
      #only make this check if -f has already been specified
      if($OutputToFile)
      {
        $OverwriteFile = $TRUE;
      }
      else
      {
        #print "Can't use the delete feature since no output file path was specified\n";
      }
    }

    #determine if only today's quote is to be retrieved
    elsif($StartDateSpecified == $FALSE && $CommandLineArguments[$ArgNum] eq "-t")
    {
      get_current_date();
      $TodayOnlySpecified = $TRUE;
    }

    #determine if a start date is specified
    elsif($TodayOnlySpecified == $FALSE && $CommandLineArguments[$ArgNum] eq "-start")
    {
      #check to see if the following token is indeed a date
      $ArgNum++;
      if($ArgNum <= $#CommandLineArguments && $CommandLineArguments[$ArgNum] =~ /^(0?[1-9]|1[0-2])(-|\/)(0?[1-9]|[1-2][0-9]|3[0-1])(-|\/)(19[0-9]{2}|20[0-9]{2})/)
      {
        #in case -end isn't specified, set start and end dates to the same date
        $StartDay = $3;
        $StartMonth = $1;
        $StartYear = $5;
        $EndDay = $3;
        $EndMonth = $1;
        $EndYear = $5;
      }
      else
      {
        #print "No start date was specified or an improper date was specified, will use the current date as the start date...\n";
        get_current_date();
      }

      $StartDateSpecified = $TRUE;
    }

    #determine if an end date is specified
    elsif($StartDateSpecified == $TRUE && $CommandLineArguments[$ArgNum] eq "-end")
    {
      #check to see if the following token is indeed a date
      $ArgNum++;

      if($ArgNum <= $#CommandLineArguments && $CommandLineArguments[$ArgNum] =~ /^(0?[1-9]|1[0-2])(-|\/)(0?[1-9]|[1-2][0-9]|3[0-1])(-|\/)(19[0-9]{2}|20[0-9]{2})/)
      {

        #make sure that the end date is a date after the start date
        if($5 > $StartYear || ($5 == $StartYear && $1 > $StartMonth) || ($5 == $StartYear && $1 == $StartMonth && $3 >= $StartDay))
        {
          $EndDay = $3;
          $EndMonth = $1;
          $EndYear = $5;
        }
        else
        {
          #print "The specified end date is a date prior to the specified start date.  The end date will be set to equal the start date.\n";

          #no change to the end date will be made here since the end date starts out being set equal to the start date
        }
      }
      else
      {
        #print "No end date was specified or an improper date was specified, will use the start date as the end date...\n";
      }
    }
  }

	if($StartDateSpecified == $FALSE && $TodayOnlySpecified == $FALSE)
	{
	  get_current_date();
    $TodayOnlySpecified = $TRUE;
	}
}

sub print_help_information
{
  #print "Welcome to the stock quote retriever!\n";
  #print "The following options are available:\n";
  #print "  -help = information about how to use the program\n";
  #print "  -s [SYMBOL] = retrieve quotes for the specified [SYMBOL] if it's available\n";
  #print "  -h = outputs the header line\n";
  #print "  -f [FILE PATH] = outputs the retrieved quote to a .csv file\n";
  #print "       if omitted, the quote will be printed to standard output\n";
  #print "  -d = deletes a stock quote file for the specified symbol if -f is specified\n";
  #print "       if omitted, an existing file for that symbol will be appended to\n";
  #print "  -t = retrieves today's quote for the specified symbol\n";
  #print "  -start [DATE] = specifies the starting day of the quote to retrieve\n";
  #print "       can't be used in conjuction with -t\n";
  #print "       if used with -end [DATE], gets quotes for each day between start and end\n";
  #print "       if -end [DATE] is not specified, then retrieves only the quote for 1 day\n";
  #print "  -end [DATE] = specifies the ending day of the quote to retrieve\n";
  #print "       can't be used in conjuction with -t\n";
  #print "       must be used after -start [DATE] has been specified\n";
  #print "       [DATE] must be a date that comes the date specified by -start\n";
  #print "\n";
  #print "  [DATE] can be inputted in multiple ways.  For instance, January 1, 2010 can\n";
  #print "  be written as 01\/01\/2010, 1\/1\/2010, 01-01-2010, or 1-1-2010\n";
}

sub get_current_date
{
  my($Seconds, $Minutes, $Hours, $Day, $Month, $Year) = localtime(time);

  #must adjust the year by 1900 to make it a 4-digit number
  #month comes pre-adjusted as current month - 1 (i.e. January = 00, February = 01, etc), so add 1
  $Year += 1900;
  $Month += 1;

  #to get 1 day's worth of quotes, set start date and end date to the same date
  $StartDay = $Day;
  $StartMonth = $Month;
  $StartYear = $Year;
  $EndDay = $Day;
  $EndMonth = $Month;
  $EndYear = $Year;
}

sub get_stock_quotes
{
  my($Symbol) = $_[0];

  #code provided by Thomas Weigert
  my $Url = "http://chart.yahoo.com/table.csv?s=$Symbol&a=$StartMonth&b=$StartDay&c=$StartYear&d=$EndMonth&e=$EndDay&f=$EndYear&g=d&q=q&y=0&z=dis&x=.csv";

  my $UserAgent = new LWP::UserAgent;
  my $Request = new HTTP::Request 'GET', $Url;
  my $Response = $UserAgent->request($Request)->content;

	#handle 404 for misspelled or nonexistent stock ticker symbol
  if(  ($Response =~ /404 Not Found/)
    || ($Response eq "")
    || ($Response eq "Date,Open,High,Low,Close,Volume,Adj Close\n")
    )
  {
	  $QueryResultsErrorFlag = $TRUE;
  }
	else
	{
	  $QueryResultsErrorFlag = $FALSE;
  }

  return $Response;
}

sub fix_quote_format
{
  my @Lines = split(/\n/, $OriginalQuotes);
  my $CurrentLineNumber = 0;

  #reverse the array since the quotes are printed from the most recent day to the oldest day
  #and we want to #print out the results in reverse (oldest to newest)
  @Lines = reverse(@Lines);

  #write the header line
  # $ReformattedQuotes = "Open,High,Low,Close,Volume,Date";

  if ($OutputToFile == $TRUE) {

    $ReformattedQuotes = "Open,High,Low,Close,Volume,Date\n";

  } else {

    # $ReformattedQuotes = "|  *Open*  |  *High*  |  *Low*  |  *Close*  |  *Volume*  |  *Date*  |%BR%";
    $ReformattedQuotes = "|  *Open*  |  *High*  |  *Low*  |  *Close*  |  *Volume*  |  *Date*  |\n";
    # $ReformattedQuotes = "|  *Open*  |  *High*  |  *Low*  |  *Close*  |  *Volume*  |  *Date*  |";

  }

  foreach my $Line (@Lines)
  {
    #ignore the last line since it will be the header line and we already have appended the proper header
	if($CurrentLineNumber != $#Lines)
	{
    my($Date, $Open, $High, $Low, $Close, $Volume, $Adjusted) = split(/,/, $Line);
	  my($Year, $Month, $Day) = split(/-/, $Date);

	  #remove the first '0' from the $Day variable if it exists
	  if(substr($Day, 0, 1) eq '0')
	  {
	    $Day = substr($Day, 1, 1);
    }

	  #update the date format to say 1 Jan 2010 instead of 2010-1-1
	  $Date = $Day . " ". $MONTH_ABBREVIATIONS[$Month - 1] . " " . $Year;

    #Adjust the numbers if necessary
    if ( $AdjustedData == $TRUE )
    {
      # Adjust the quote data based on the adjusted closing price
      my $ratio = $Adjusted / $Close;
      $Open   *= $ratio;
      $High   *= $ratio;
      $Low    *= $ratio;
      $Close   = $Adjusted;
    }


    my $space1 = "";
    my $space2 = ",";
    my $space3 = "\n";

    if ($OutputToFile == $FALSE) {

      # $space1 = "| ";
      $space1 = "| ";
      $space2 = " | ";
      # $space3 = " |%BR%";
      # $space3 = " |<br />";
      $space3 = " |\n";
      # $space3 = " |";

    }

    $ReformattedQuotes .= $space1 . sprintf( "%.2f", $Open )    # Open
                 . $space2 . sprintf( "%.2f", $High )  # High
                 . $space2 . sprintf( "%.2f", $Low )   # Low
                 . $space2 . sprintf( "%.2f", $Close ) # Close
                 . $space2 . $Volume
                 . $space2 . $Date
                 . $space3;

	  #reformat the order of information
	  # $ReformattedQuotes .= $Open . "," . $High . "," . $Low . "," . $Close . "," . $Volume . "," . $Date . "\n";
	}

	$CurrentLineNumber++;
  }
}

sub print_results
{
  my($Symbol) = $_[0];
  my $IndexOfNewLine;
  my $HeaderlessReformattedQuotes;
  my $newlineCut;

  # if ($OutputToFile == $TRUE) {

    # $newlineCut = "\n";

  # } else {

    # $newlineCut = "%BR%";

  # }

  $newlineCut = "\n";

  #remove the first line just in case the user didn't want the header line printed out
  $IndexOfNewLine = index($ReformattedQuotes, $newlineCut);
  $HeaderlessReformattedQuotes = substr($ReformattedQuotes, $IndexOfNewLine);

  ##print to a file
  if($OutputToFile == $TRUE)
  {
    my $OutputFile;

    #check to see if we should overwrite an existing file or just append
    if($OverwriteFile == $TRUE)
    {
      $OutputFile = ">" . $OutputDirectory . "Stock_Quotes_" . $Symbol . ".csv";
    }
    else
    {
      $OutputFile = ">>" . $OutputDirectory . "Stock_Quotes_" . $Symbol . ".csv";
    }

    #check to see if we are printing out the full quotes or the headerless quotes
    open OUTPUT, $OutputFile or ( return $! );
    if($PrintHeader == $TRUE)
    {
      print OUTPUT $ReformattedQuotes;
    }
    else
    {
      print OUTPUT $HeaderlessReformattedQuotes;
    }
    close OUTPUT;

    return "Quotes for $Symbol saved successfully to the working directory.\n";
  }

  ##print to standard output
  else
  {
    #check to see if we are printing out the full quotes or the headerless quotes
    if($PrintHeader == $TRUE)
    {
      # return ("| $Symbol ||||||" . "%BR%" . $ReformattedQuotes . "%BR%");
      return ("|  *$Symbol*  ||||||" . "\n" . $ReformattedQuotes);
    }
    else
    {
      # return ("| $Symbol ||||||" . "%BR%" . $HeaderlessReformattedQuotes . "%BR%");
      return ("|  *$Symbol*  ||||||" . $HeaderlessReformattedQuotes);
    }
  }
}


#####################
#
#  MAIN
#
#####################

# Make the Main a function that we can call from QUOTE or QUOTE DOWNLOAD.

sub QuotePluginMain
{
  my $ResultsToTWikify = '';

  # Push all of the variables into an array just like CommandLineArguments would be, but since
  # this isn't being called from a command line we don't have CommandLineArguments. So
  # make a fake one, then use that array instead of CommandLineArguments for the processing.
  read_command_line_arguments();

  #adjust the month by -1 since this is what the website does (January = 0, not 1)
  $StartMonth--;
  $EndMonth--;

  # Run through each symbol presented

  for(my $i = 0; $i < @Symbols; $i++)
  {
    $OriginalQuotes = get_stock_quotes($Symbols[$i]);

    ##print out the results if there were no query errors
    if($QueryResultsErrorFlag == $FALSE)
    {
      fix_quote_format();

      $ResultsToTWikify .= (print_results($Symbols[$i]) . "\n");
    }
    else
    {
      # my $OutputFile = ">" . $OutputDirectory . "Stock_Quotes_" . $Symbols[$i] . ".txt";
      # open OUTPUT, $OutputFile or die "Can't Open $OutputFile\n";
      # #print OUTPUT "Error getting results back from the server.  Check your symbol(s) and / or dates";
      # close OUTPUT;

      $ResultsToTWikify = "Error getting results back from the server. Check your symbol(s) and / or dates.";
    }
  }

  return $ResultsToTWikify;
}

1;
