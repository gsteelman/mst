# @file GameWarpDataPlugin.pm
# @desc Working through the tutorial here:
#       http://twiki.org/cgi-bin/view/TWiki/HowToMakeSimpleTWikiPlugin

package TWiki::Plugins::GameWarpDataPlugin;

# Always use strict to enforce variable scoping
use strict;
use CGI qw(:all);
use DBI;
#use DBD::mysql;

require TWiki::Func;    # The plugins API
require TWiki::Plugins; # For the API version

use vars qw( $dbh $sth $sth_internal @array @arraytest $statement $VERSION $RELEASE $SHORTDESCRIPTION $debug $pluginName $NO_PREFS_IN_TOPIC );
no warnings;

$VERSION = '$Rev: 15942 (29 Apr 2009) $';
$RELEASE = 'The GameWarpData Machine';
$SHORTDESCRIPTION = 'GameWarp Data Rendering and Statistics.';
$NO_PREFS_IN_TOPIC = 1;
$pluginName = 'GameWarpDataPlugin';

sub initPlugin
{
  my( $topic, $web, $user, $installWeb ) = @_;

  # Register our functions.
  TWiki::Func::registerTagHandler( 'GAMEWARPDATA', \&_GAMEWARPDATA );

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

sub _GAMEWARPDATA
{
  # Query, Process, and Return the results.
  return GameWarpDataPluginMain();
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

#####################
#
#  GLOBAL VARIABLES
#
#####################
my $statement;

#####################
#
#  SUB ROUTINES
#
#####################


#####################
#
#  MAIN
#
#####################

# Make the Main a function that we can call from GAMEWARPDATA or GAMEWARPDATA DOWNLOAD.

# CONFIG VARIABLES
my $platform = "mysql";
my $database = "miner012";
my $host = "mysql.minersoft.org";
my $port = "3306";
my $user = "miner012";
my $password = "joeminer";

sub call_dbi
{
    $dbh=DBI->connect("dbi:$platform:$database:$host:$port", $user, $password)|| die "No";;
        $sth=$dbh->prepare($statement);
        $sth->execute();

    return $sth;
}

sub call_dbi_internal
{
    $dbh=DBI->connect("dbi:$platform:$database:$host:$port", $user, $password)|| die "No";;
        $sth_internal=$dbh->prepare($statement);
        $sth_internal->execute();

    return $sth_internal;
}

sub GameWarpDataPluginMain
{

  my $ResultsToTWikify = "";

  $statement="SELECT * FROM Account ORDER BY AccountNumber ASC";
#    $dbh=DBI->connect("dbi:$platform:$database:$host:$port", $user,$password,);
#        $sth=$dbh->prepare($statement);
#        $sth->execute();

  &call_dbi($statement);

  while (@array=$sth->fetchrow_array)
  {
    $ResultsToTWikify = $ResultsToTWikify
                          . "|  * !AccountNumber*  |  * !UserName*  |  * !E-Mail*  |  * !Admin*  |\n";
    $ResultsToTWikify = $ResultsToTWikify . "|  !" . $array[0]
                          . "  |  !" . $array[1]
                          . "  |  !" . $array[3]
                          . "  |  !" . $array[4]
                          . "  |\n";




    $statement="SELECT * FROM GameGenreQuestionnaire WHERE AccountNumber = $array[0] ORDER BY AccountNumber ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "| * !Game !Genre !Questionnaire* |  * !Action*  |  * !Adventure*  |  * !ActionAdventure*  |  * !Driving*  |  * !RolePlaying*  |  * !Simulation*  |  * !Sport*  |  * !Strategy*  |  * !Puzzle*  |  * !Shooter*  |  * !Rhythm*  |  * !Party*  |  * !Platformer*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |  !" . $arraytest[3]
                          . "  |  !" . $arraytest[4]
                          . "  |  !" . $arraytest[5]
                          . "  |  !" . $arraytest[6]
                          . "  |  !" . $arraytest[7]
                          . "  |  !" . $arraytest[8]
                          . "  |  !" . $arraytest[9]
                          . "  |  !" . $arraytest[10]
                          . "  |  !" . $arraytest[11]
                          . "  |  !" . $arraytest[12]
                          . "  |  !" . $arraytest[13]
                          . "  |\n";
    }



    $statement="SELECT * FROM GameSubGenreQuestionnaire WHERE AccountNumber = $array[0] ORDER BY AccountNumber ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "| * !Game !SubGenre !Questionnaire* |  * !Fighting*  |  * !Driving*  |  * !WRPG*  |  * !JRPG*  |  * !Baseball*  |  * !Basketball*  |  * !Golf*  |  * !Boxing*  |  * !MMA*  |  * !Wrestling*  |  * !Football*  |  * !Hockey*  |  * !Miscellaneous*  |  * !RealTime*  |  * !TurnBased*  |  * !Dancing*  |  * !Singing*  |  * !Instruments*  |  * !FirstPerson*  |  * !ThirdPerson*  |  * !ShootEmUp*  |  * !RailShooter*  |  * !Trivia*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |  !" . $arraytest[3]
                          . "  |  !" . $arraytest[4]
                          . "  |  !" . $arraytest[5]
                          . "  |  !" . $arraytest[6]
                          . "  |  !" . $arraytest[7]
                          . "  |  !" . $arraytest[8]
                          . "  |  !" . $arraytest[9]
                          . "  |  !" . $arraytest[10]
                          . "  |  !" . $arraytest[11]
                          . "  |  !" . $arraytest[12]
                          . "  |  !" . $arraytest[13]
                          . "  |  !" . $arraytest[14]
                          . "  |  !" . $arraytest[15]
                          . "  |  !" . $arraytest[16]
                          . "  |  !" . $arraytest[17]
                          . "  |  !" . $arraytest[18]
                          . "  |  !" . $arraytest[19]
                          . "  |  !" . $arraytest[20]
                          . "  |  !" . $arraytest[21]
                          . "  |  !" . $arraytest[22]
                          . "  |  !" . $arraytest[23]
                          . "  |\n";
    }



    $statement="SELECT * FROM TheatricalGenreQuestionnaire WHERE AccountNumber = $array[0] ORDER BY AccountNumber ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "| * !Theatrical !Genre !Questionnaire* |  * !Action*  |  * !Adventure*  |  * !Comedy*  |  * !CrimeAndGangster*  |  * !Drama*  |  * !EpicsAndHistorical*  |  * !Fantasy*  |  * !Horror*  |  * !MusicAndDancing*  |  * !Mystery*  |  * !ScienceFiction*  |  * !War*  |  * !Western*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |  !" . $arraytest[3]
                          . "  |  !" . $arraytest[4]
                          . "  |  !" . $arraytest[5]
                          . "  |  !" . $arraytest[6]
                          . "  |  !" . $arraytest[7]
                          . "  |  !" . $arraytest[8]
                          . "  |  !" . $arraytest[9]
                          . "  |  !" . $arraytest[10]
                          . "  |  !" . $arraytest[11]
                          . "  |  !" . $arraytest[12]
                          . "  |  !" . $arraytest[13]
                          . "  |\n";
    }



    $statement="SELECT * FROM TheatricalSubGenreQuestionnaire WHERE AccountNumber = $array[0] ORDER BY AccountNumber ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "| * !Theatrical !SubGenre !Questionnaire* |  * !WorldWarTwo*  |  * !PostApocalyptic*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |\n";
    }



    $statement="SELECT * FROM UserCurrentGamesPlaying WHERE AccountNumber = $array[0] ORDER BY GameURI ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "|  * !User !Current !Games !Playing*  |  * !GameURI*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |\n";
    }

    $statement="SELECT * FROM UserGameRatings WHERE AccountNumber = $array[0] ORDER BY GameURI ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "|  * !User !Game !Ratings*  |  * !GameURI*  |  * Rating*  |  * Comment*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |  !" . $arraytest[3]
                          . "  |\n";
    }

    $statement="SELECT * FROM UserGameConsoles WHERE AccountNumber = $array[0] ORDER BY Console ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "|  * !User !Game !Consoles*  |  * !Console*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |\n";
    }

    $statement="SELECT * FROM UserProfileAttributes WHERE AccountNumber = $array[0] ORDER BY Attribute ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "|  * !User !Profile !Attributes*  |  * !Attribute*  |  * !Score*  |  * !NumberRatings*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |  !" . $arraytest[3]
                          . "  |\n";
    }

    $statement="SELECT * FROM UserProfileGenre WHERE AccountNumber = $array[0] ORDER BY Genre ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "|  * !User !Profile !Genre*  |  * !Genre*  |  * !Score*  |  * !NumberRatings*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |  !" . $arraytest[3]
                          . "  |\n";
    }

    $statement="SELECT * FROM UserProfileTheatricalGenre WHERE AccountNumber = $array[0] ORDER BY Genre ASC";
    $ResultsToTWikify = $ResultsToTWikify
                          . "|  * !User !Profile !Theatrical !Genre*  |  * !Genre*  |  * !Score*  |  * !NumberRatings*  |\n";
    &call_dbi_internal($statement);
    while (@arraytest=$sth_internal->fetchrow_array)
    {
      $ResultsToTWikify = $ResultsToTWikify
                          . "  |   "
                          . "  |  !" . $arraytest[1]
                          . "  |  !" . $arraytest[2]
                          . "  |  !" . $arraytest[3]
                          . "  |\n";
    }

      $ResultsToTWikify = $ResultsToTWikify . "<BR><BR><BR>\n";
  }




  return $ResultsToTWikify;
}

1;
