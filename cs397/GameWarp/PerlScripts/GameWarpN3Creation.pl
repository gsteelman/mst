# @file GameWarpDataPlugin.pm
# @desc Working through the tutorial here:
#       http://twiki.org/cgi-bin/view/TWiki/HowToMakeSimpleTWikiPlugin

# Always use strict to enforce variable scoping
use strict;
use CGI qw(:all);
use DBI;
#use DBD::mysql;

use vars qw( $dbh $sth $sth_internal $sth_internal1 @array @array_internal @array_internal1 $statement $statement_internal $statement_internal1 );
no warnings;

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
my $host = "localhost";
#my $host = "mysql.minersoft.org";
my $port = "3306";
my $user = "miner012";
my $password = "joeminer";

&GenerateN3;

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
        $sth_internal=$dbh->prepare($statement_internal);
        $sth_internal->execute();

    return $sth_internal;
}

sub call_dbi_internal1
{
    $dbh=DBI->connect("dbi:$platform:$database:$host:$port", $user, $password)|| die "No";;
        $sth_internal1=$dbh->prepare($statement_internal1);
        $sth_internal1->execute();

    return $sth_internal1;
}

sub GenerateN3
{

  #Opens file to write to.
  my $file = "games.n3";

  open FILE, ">$file" or die "unable to open $file $!";

  #Setup the prefixs for the n3 file.
  print FILE "\@prefix game: <http://www.gamewarp.org/game#> .\n";
  print FILE "\@prefix gen: <http://www.gamewarp.org/genre#> .\n";
  print FILE "\@prefix tgen: <http://www.gamewarp.org/tgenre#> .\n";
  print FILE "\@prefix tags: <http://www.gamewarp.org/tags#> .\n";
  print FILE "\@prefix plat: <http://www.gamewarp.org/platform#> .\n";
  print FILE "\@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n\n";


  $statement="SELECT * FROM GameList ORDER BY GameURI ASC";
  &call_dbi($statement);
  while (@array=$sth->fetchrow_array)
  {
    #Set the gameN3 variable up.
    my $gameN3 = "";
    my $marker = "";

    #Set the game line.
    #game:theLegendOfZelda
    $gameN3 = $gameN3 . "game:" . $array[0] . "\n";

    #Set the second line
    # a gen:action, gen:adventure ;
    $gameN3 = $gameN3 . " a ";
    #Get a end marker to change from ", " to " ;\n" in the gameN3 variable.
    $statement_internal="SELECT * FROM GameGenres WHERE GameURI = '" . $array[0] . "' ORDER BY Genre ASC";
    &call_dbi_internal($statement_internal);
    while (@array_internal=$sth_internal->fetchrow_array)
    {
      $marker = $array_internal[1];
    }
    #Write all the genres to the gameN3 variable.
    $statement_internal1="SELECT * FROM GameGenres WHERE GameURI = '" . $array[0] . "' ORDER BY Genre ASC";
    &call_dbi_internal1($statement_internal1);
    while (@array_internal1=$sth_internal1->fetchrow_array)
    {
      $gameN3 = $gameN3 . "gen:" . $array_internal1[1];
      if($array_internal1[1] ne $marker) {
        $gameN3 = $gameN3 . ", ";
      } else {
        $gameN3 = $gameN3 . " ;\n";
      }
    }

    #Write the rdfs line
    # rdfs:label "The Legend of Zelda" ;
    $gameN3 = $gameN3 . " rdfs:lable \"" . $array[0] . "\" ;\n";

    #Write the tags line tgenre.
    # tags:tgenre tgen:fantasy ;
    $gameN3 = $gameN3 . " tags:tgenre ";
    #Get a end marker to change from ", " to " ;\n" in the gameN3 variable.
    $statement_internal="SELECT * FROM GameTheatricalGenres WHERE GameURI = '" . $array[0] . "' ORDER BY Genre ASC";
    &call_dbi_internal($statement_internal);
    while (@array_internal=$sth_internal->fetchrow_array)
    {
      $marker = $array_internal[1];
    }
    #Write all the genres to the gameN3 variable.
    $statement_internal1="SELECT * FROM GameTheatricalGenres WHERE GameURI = '" . $array[0] . "' ORDER BY Genre ASC";
    &call_dbi_internal1($statement_internal1);
    while (@array_internal1=$sth_internal1->fetchrow_array)
    {
      $gameN3 = $gameN3 . "tgen:" . $array_internal1[1];
      if($array_internal1[1] ne $marker) {
        $gameN3 = $gameN3 . ", ";
      } else {
        $gameN3 = $gameN3 . " ;\n";
      }
    }

    #Write the tags line platforms.
    # tags:availableOn plat:NintendoEntertainmentSystem, plat:Wii, plat:GameBoyAdvance ;
    $gameN3 = $gameN3 . " tags:availableOn ";
    #Get a end marker to change from ", " to " ;\n" in the gameN3 variable.
    $statement_internal="SELECT * FROM GamePlatforms WHERE GameURI = '" . $array[0] . "' ORDER BY Platform ASC";
    &call_dbi_internal($statement_internal);
    while (@array_internal=$sth_internal->fetchrow_array)
    {
      $marker = $array_internal[1];
    }
    #Write all the genres to the gameN3 variable.
    $statement_internal1="SELECT * FROM GamePlatforms WHERE GameURI = '" . $array[0] . "' ORDER BY Platform ASC";
    &call_dbi_internal1($statement_internal1);
    while (@array_internal1=$sth_internal1->fetchrow_array)
    {
      $gameN3 = $gameN3 . "plat:" . $array_internal1[1];
      if($array_internal1[1] ne $marker) {
        $gameN3 = $gameN3 . ", ";
      } else {
        $gameN3 = $gameN3 . " ;\n";
      }
    }


    #Write the tags line tags.
    # tags:tags tags:rendered2D, tags:played2D, tags:ghosts, tags:elves, tags:warlocks, tags:swords, tags:collection, tags:link .
    $gameN3 = $gameN3 . " tags:tags ";
    #Get a end marker to change from ", " to " ;\n" in the gameN3 variable.
    $statement_internal="SELECT * FROM GameAttributes WHERE GameURI = '" . $array[0] . "' ORDER BY Attribute ASC";
    &call_dbi_internal($statement_internal);
    while (@array_internal=$sth_internal->fetchrow_array)
    {
      $marker = $array_internal[1];
    }
    #Write all the genres to the gameN3 variable.
    $statement_internal1="SELECT * FROM GameAttributes WHERE GameURI = '" . $array[0] . "' ORDER BY Attribute ASC";
    &call_dbi_internal1($statement_internal1);
    while (@array_internal1=$sth_internal1->fetchrow_array)
    {
      $gameN3 = $gameN3 . "tags:" . $array_internal1[1];
      if($array_internal1[1] ne $marker) {
        $gameN3 = $gameN3 . ", ";
      } else {
        $gameN3 = $gameN3 . " .\n\n";
      }
    }





    print FILE $gameN3;
  }


  close FILE;
  return;
}

