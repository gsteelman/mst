package test_suite;

use base qw( TWikiTestCase ); # This base class sets up the basic test fixture

use strict;

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
    my $response = new Unit::Response();
    $response->charset("utf8");

    # Create a TWiki instance
    $twiki = new TWiki(undef, $query);

    # and use it to create some test webs
    $twiki->{store}->createWeb( $twiki->{user}, $testWeb );
    $twiki->{store}->createWeb( $twiki->{user}, $testUsersWeb );
}

sub tear_down {
    my $this = shift; # the Test::Unit::TestCase object

    # This will erase the test webs
    $this->removeWebFixture( $twiki, $testWeb );
    $this->removeWebFixture( $twiki, $testUsersWeb );

    # This will destroy the TWiki instance.  We use eval to suppress errors
    eval { $twiki->finish() };

    # This will automatically restore the state of $TWiki::cfg
    $this->SUPER::tear_down();
}

sub test_Quote {
    my $this = shift; # this is an instance of Test::Unit::TestCase; see the online docs for more help

    # We can munge $TWiki::cfg safely, because it will be restored in tear_down
    $TWiki::cfg{ScriptUrlPaths}{snarf} = "sausages";
    undef $TWiki::cfg{ScriptUrlPaths}{view};
    $TWiki::cfg{ScriptSuffix} = ".pm";
	
  my $txtSymbol = "GOOG";

  my $txtBDate = "1/1/2005";

  my $txtEDate = "2/1/2005";

  my $chkToday = "";

  my $chkHeaders = "";

  my $chkAdjusted = "";

  my $chkAttach = "";

  my $chkOverwrite = "";
  
  my $InputFile = "</home/miner012/gamewarp/working/Stock_Quotes_GOOG_test.csv";

  open INPUT, $InputFile or ( return $! );
    my $expected = $InputFile;
    print $expected . "\n";
  close INPUT;
  
  
  my $message = "This did not match.";
	
    my $actual = $twiki->handleCommonTags("%QUOTEDOWNLOAD{Symbol=\"$txtSymbol\" Beginningdate=\"$txtBDate\" Enddate=\"$txtEDate\" Today=\"$chkToday\" Header=\"$chkHeaders\" Adjusted=\"$chkAdjusted\" Filepath=\"$chkAttach\" Overwrite=\"$chkOverwrite\"}%", $testWeb, $testTopic);
    $this->assert_str_equals($expected, $actual, $message);
}

1
