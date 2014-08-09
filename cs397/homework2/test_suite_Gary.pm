package test_suite_Gary;

use base qw( TWikiTestCase ); # This base class sets up the basic test fixture

use strict;
no warnings;
use File::Path;

sub new {
    my $self = shift()->SUPER::new(@_);
    return $self;
}

# Constants used in this test case
my $testWeb = 'TemporaryTestWeb'; # name of the test web
my $testTopic = 'TestTopic';      # name of a topic
my $testUsersWeb = 'TemporaryTestUsersUsersWeb'; # Name of a %MAINWEB% for our test users
my $twiki; # TWiki instance

sub set_up {
    my $this = shift; # the Test::Unit::TestCase object

    $this->SUPER::set_up();

    $TWiki::cfg{UsersWebName} = $testUsersWeb;
    $TWiki::cfg{MapUserToWikiName} = 1;
    $TWiki::cfg{Htpasswd}{FileName} = '/tmp/junkpasswd';
    $TWiki::cfg{PasswordManager} = 'TWiki::Users::HtPasswdUser';

    # Make up a simple query
    my $query = new Unit::Request("");
    $query->path_info("/$testWeb/$testTopic");

    # Create a TWiki instance
    $twiki = new TWiki(undef, $query);

    my $response = new Unit::Response();
    $response->charset("utf8");

    # and use it to create some test webs
    $twiki->{store}->createWeb( $twiki->{user}, $testWeb );
    $twiki->{store}->createWeb( $twiki->{user}, $testUsersWeb );
}

sub tear_down {
    my $this = shift; # the Test::Unit::TestCase object

    #Erase the temp files made by testing.
    #rmtree(['/home/miner012/gamewarp/data/TemporaryTestUsersUsersWeb', '/home/miner012/gamewarp/data/TemporaryTestWeb']);

    # This will erase the test webs
    $this->removeWebFixture( $twiki, $testWeb );
    $this->removeWebFixture( $twiki, $testUsersWeb );

    # This will destroy the TWiki instance.  We use eval to suppress errors
    eval { $twiki->finish() };

    # This will automatically restore the state of $TWiki::cfg
    $this->SUPER::tear_down();
}

sub test_Quote_Gary1 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol = "";
  my $txtBDate = "";
  my $txtEDate = "";
  my $chkToday = "";
  my $chkHeaders = "";
  my $chkAdjusted = "";
  my $chkAttach = "";
  my $chkOverwrite = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Gary.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test1 = split(",", $lines[1]);

  #Populate the variables for getting quotes
  $txtSymbol = $test1[0];
  $txtBDate = $test1[1];
  $txtEDate = $test1[2];
  $chkToday = $test1[3];
  $chkHeaders = $test1[4];
  $chkAdjusted = $test1[5];
  $chkAttach = $test1[6];
  $chkOverwrite = $test1[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[2];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match :: test_Quote_Gary1.";

  #Get the quotes from the plugin
  my $actual = $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol\" Beginningdate=\"$txtBDate\" Enddate=\"$txtEDate\" Today=\"$chkToday\" Header=\"$chkHeaders\" Adjusted=\"$chkAdjusted\" Filepath=\"$chkAttach\" Overwrite=\"$chkOverwrite\"}%", $testWeb, $testTopic);

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual, $message);
}

sub test_Quote_Gary2 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol = "";
  my $txtBDate = "";
  my $txtEDate = "";
  my $chkToday = "";
  my $chkHeaders = "";
  my $chkAdjusted = "";
  my $chkAttach = "";
  my $chkOverwrite = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Gary.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test1 = split(",", $lines[4]);

  #Populate the variables for getting quotes
  $txtSymbol = $test1[0];
  $txtBDate = $test1[1];
  $txtEDate = $test1[2];
  $chkToday = $test1[3];
  $chkHeaders = $test1[4];
  $chkAdjusted = $test1[5];
  $chkAttach = $test1[6];
  $chkOverwrite = $test1[7];

  # Have the quote tag retreive the data and store to files
  $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol\" Beginningdate=\"$txtBDate\" Enddate=\"$txtEDate\" Today=\"$chkToday\" Header=\"$chkHeaders\" Adjusted=\"$chkAdjusted\" Filepath=\"$chkAttach\" Overwrite=\"$chkOverwrite\"}%", $testWeb, $testTopic);

  my $filename = $lines[5];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match :: test_Quote_Gary2.";

  #Get the quotes from the file
  my $actual = TWiki::Func::readFile( "/home/miner012/gamewarp/working/Stock_Quotes_SPY.csv" );

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual, $message);
}

sub test_Quote_Gary5 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol = "";
  my $txtBDate = "";
  my $txtEDate = "";
  my $chkToday = "";
  my $chkHeaders = "";
  my $chkAdjusted = "";
  my $chkAttach = "";
  my $chkOverwrite = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Gary.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test1 = split(",", $lines[4]);

  #Populate the variables for getting quotes
  $txtSymbol = $test1[0];
  $txtBDate = $test1[1];
  $txtEDate = $test1[2];
  $chkToday = $test1[3];
  $chkHeaders = $test1[4];
  $chkAdjusted = $test1[5];
  $chkAttach = $test1[6];
  $chkOverwrite = $test1[7];

  # Have the quote tag retreive the data and store to files
  $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol\" Beginningdate=\"$txtBDate\" Enddate=\"$txtEDate\" Today=\"$chkToday\" Header=\"$chkHeaders\" Adjusted=\"$chkAdjusted\" Filepath=\"$chkAttach\" Overwrite=\"$chkOverwrite\"}%", $testWeb, $testTopic);

  # Test the GOOG part of the multidownload

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[6];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match :: test_Quote_Gary5.";

  #Get the quotes from the file
  my $actual = TWiki::Func::readFile( "/home/miner012/gamewarp/working/Stock_Quotes_GOOG.csv" );

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual, $message);
}

sub test_Quote_Gary3 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol = "";
  my $txtBDate = "";
  my $txtEDate = "";
  my $chkToday = "";
  my $chkHeaders = "";
  my $chkAdjusted = "";
  my $chkAttach = "";
  my $chkOverwrite = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Gary.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test1 = split(",", $lines[8]);

  #Populate the variables for getting quotes
  $txtSymbol = $test1[0];
  $txtBDate = $test1[1];
  $txtEDate = $test1[2];
  $chkToday = $test1[3];
  $chkHeaders = $test1[4];
  $chkAdjusted = $test1[5];
  $chkAttach = $test1[6];
  $chkOverwrite = $test1[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[9];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  # Have the quote tag retreive the data and store to files
  $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol\" Beginningdate=\"$txtBDate\" Enddate=\"$txtEDate\" Today=\"$chkToday\" Header=\"$chkHeaders\" Adjusted=\"$chkAdjusted\" Filepath=\"$chkAttach\" Overwrite=\"$chkOverwrite\"}%", $testWeb, $testTopic);

  #Set message to display if the test doesn't match
  my $message = "This did not match :: test_Quote_Gary3.";

  #Get the quotes from the plugin
  my $actual = TWiki::Func::readFile( "/home/miner012/gamewarp/working/Stock_Quotes_GOOG.csv" );

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual, $message);
}

sub test_Quote_Gary4 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol = "";
  my $txtBDate = "";
  my $txtEDate = "";
  my $chkToday = "";
  my $chkHeaders = "";
  my $chkAdjusted = "";
  my $chkAttach = "";
  my $chkOverwrite = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Gary.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test1 = split(",", $lines[11]);

  #Populate the variables for getting quotes
  $txtSymbol = $test1[0];
  $txtBDate = $test1[1];
  $txtEDate = $test1[2];
  $chkToday = $test1[3];
  $chkHeaders = $test1[4];
  $chkAdjusted = $test1[5];
  $chkAttach = $test1[6];
  $chkOverwrite = $test1[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[12];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  # Have the quote tag retreive the data and store to files
  $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol\" Beginningdate=\"$txtBDate\" Enddate=\"$txtEDate\" Today=\"$chkToday\" Header=\"$chkHeaders\" Adjusted=\"$chkAdjusted\" Filepath=\"$chkAttach\" Overwrite=\"$chkOverwrite\"}%", $testWeb, $testTopic);

  #Set message to display if the test doesn't match
  my $message = "This did not match :: test_Quote_Gary4.";

  #Get the quotes from the plugin
  my $actual = TWiki::Func::readFile( "/home/miner012/gamewarp/working/Stock_Quotes_GOOG.csv" );

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual, $message);
}

1;
