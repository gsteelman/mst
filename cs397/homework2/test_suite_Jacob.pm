package test_suite_Jacob;

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

sub test_Quote_Jacob1 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol1 = "";
  my $txtBDate1 = "";
  my $txtEDate1 = "";
  my $chkToday1 = "";
  my $chkHeaders1 = "";
  my $chkAdjusted1 = "";
  my $chkAttach1 = "";
  my $chkOverwrite1 = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Jacob.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test1 = split(",", $lines[0]);

  #Populate the variables for getting quotes
  $txtSymbol1 = $test1[0];
  $txtBDate1 = $test1[1];
  $txtEDate1 = $test1[2];
  $chkToday1 = $test1[3];
  $chkHeaders1 = $test1[4];
  $chkAdjusted1 = $test1[5];
  $chkAttach1 = $test1[6];
  $chkOverwrite1 = $test1[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[1];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match.";

  #Get the quotes from the plugin
  my $actual1 = $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol1\" Beginningdate=\"$txtBDate1\" Enddate=\"$txtEDate1\" Today=\"$chkToday1\" Header=\"$chkHeaders1\" Adjusted=\"$chkAdjusted1\" Filepath=\"$chkAttach1\" Overwrite=\"$chkOverwrite1\"}%", $testWeb, $testTopic);

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual1, $message);
}

sub test_Quote_Jacob2 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol2 = "";
  my $txtBDate2 = "";
  my $txtEDate2 = "";
  my $chkToday2 = "";
  my $chkHeaders2 = "";
  my $chkAdjusted2 = "";
  my $chkAttach2 = "";
  my $chkOverwrite2 = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Jacob.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test2 = split(",", $lines[2]);

  #Populate the variables for getting quotes
  $txtSymbol2 = $test2[0];
  $txtBDate2 = $test2[1];
  $txtEDate2 = $test2[2];
  $chkToday2 = $test2[3];
  $chkHeaders2 = $test2[4];
  $chkAdjusted2 = $test2[5];
  $chkAttach2 = $test2[6];
  $chkOverwrite2 = $test2[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[3];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match.";

  #Get the quotes from the plugin
  my $actual2 = $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol2\" Beginningdate=\"$txtBDate2\" Enddate=\"$txtEDate2\" Today=\"$chkToday2\" Header=\"$chkHeaders2\" Adjusted=\"$chkAdjusted2\" Filepath=\"$chkAttach2\" Overwrite=\"$chkOverwrite2\"}%", $testWeb, $testTopic);

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual2, $message);
}

sub test_Quote_Jacob3 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol3 = "";
  my $txtBDate3 = "";
  my $txtEDate3 = "";
  my $chkToday3 = "";
  my $chkHeaders3 = "";
  my $chkAdjusted3 = "";
  my $chkAttach3 = "";
  my $chkOverwrite3 = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Jacob.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test3 = split(",", $lines[4]);

  #Populate the variables for getting quotes
  $txtSymbol3 = $test3[0];
  $txtBDate3 = $test3[1];
  $txtEDate3 = $test3[2];
  $chkToday3 = $test3[3];
  $chkHeaders3 = $test3[4];
  $chkAdjusted3 = $test3[5];
  $chkAttach3 = $test3[6];
  $chkOverwrite3 = $test3[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[5];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match.";

  #Get the quotes from the plugin
  my $actual3 = $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol3\" Beginningdate=\"$txtBDate3\" Enddate=\"$txtEDate3\" Today=\"$chkToday3\" Header=\"$chkHeaders3\" Adjusted=\"$chkAdjusted3\" Filepath=\"$chkAttach3\" Overwrite=\"$chkOverwrite3\"}%", $testWeb, $testTopic);

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual3, $message);
}

sub test_Quote_Jacob4 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol4 = "";
  my $txtBDate4 = "";
  my $txtEDate4 = "";
  my $chkToday4 = "";
  my $chkHeaders4 = "";
  my $chkAdjusted4 = "";
  my $chkAttach4 = "";
  my $chkOverwrite4 = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Jacob.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test4 = split(",", $lines[6]);

  #Populate the variables for getting quotes
  $txtSymbol4 = $test4[0];
  $txtBDate4 = $test4[1];
  $txtEDate4 = $test4[2];
  $chkToday4 = $test4[3];
  $chkHeaders4 = $test4[4];
  $chkAdjusted4 = $test4[5];
  $chkAttach4 = $test4[6];
  $chkOverwrite4 = $test4[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[7];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match.";

  #Get the quotes from the plugin
  my $actual4 = $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol4\" Beginningdate=\"$txtBDate4\" Enddate=\"$txtEDate4\" Today=\"$chkToday4\" Header=\"$chkHeaders4\" Adjusted=\"$chkAdjusted4\" Filepath=\"$chkAttach4\" Overwrite=\"$chkOverwrite4\"}%", $testWeb, $testTopic);

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual4, $message);
}

sub test_Quote_Jacob5 {
  my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

  # We can munge $TWiki::cfg safely, because it will be restored in tear_down
  $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
  undef $TWiki::cfg{ScriptUrlPaths}{view};
  $TWiki::cfg{ScriptSuffix} = ".pm";

  #Initalize variables for use in getting guotes.
  my $txtSymbol5 = "";
  my $txtBDate5 = "";
  my $txtEDate5 = "";
  my $chkToday5 = "";
  my $chkHeaders5 = "";
  my $chkAdjusted5 = "";
  my $chkAttach5 = "";
  my $chkOverwrite5 = "";

  #Get the testing information file
  my $read_test_info = "/home/miner012/gamewarp/test/unit/QuotePlugin/test_cases_Jacob.txt";
  my $test_info = TWiki::Func::readFile($read_test_info);

  #Parse the testing information file
  my @lines = split("\n", $test_info);
  my @test5 = split(",", $lines[8]);

  #Populate the variables for getting quotes
  $txtSymbol5 = $test5[0];
  $txtBDate5 = $test5[1];
  $txtEDate5 = $test5[2];
  $chkToday5 = $test5[3];
  $chkHeaders5 = $test5[4];
  $chkAdjusted5 = $test5[5];
  $chkAttach5 = $test5[6];
  $chkOverwrite5 = $test5[7];

  #Get the expected information file
  #my $filename = "/home/miner012/gamewarp/test/unit/QuotePlugin/Stock_Quotes_GOOG_test.txt";
  my $filename = $lines[9];
  my $expected = TWiki::Func::readFile( $filename );

  # Should be writing file with:
  # TWiki::Func::saveFile( $filename, $text )
  # Not with the following.

  #Set message to display if the test doesn't match
  my $message = "This did not match.";

  #Get the quotes from the plugin
  my $actual5 = $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol5\" Beginningdate=\"$txtBDate5\" Enddate=\"$txtEDate5\" Today=\"$chkToday5\" Header=\"$chkHeaders5\" Adjusted=\"$chkAdjusted5\" Filepath=\"$chkAttach5\" Overwrite=\"$chkOverwrite5\"}%", $testWeb, $testTopic);

  #Assert that the quotes match the expected file
  $this->assert_str_equals($expected, $actual5, $message);
}

1
