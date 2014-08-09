<?php 
/*
This file is meant to run main.class with the appropriate parameters and to 
demonstrate how to pick up the output from the algorithms later
*/

// Please add a function called getStorageLocation() that returns a string
// where we want to store results to, ie "outputs/results" or something
include "includes/functions.php";

$userAction = 0; // 0 if doing a recommendation, 1 if doing a rating of a new game
$cmd        = "";
$storageLoc = escapeshellarg( getStorageLocation() );
$username   = escapeshellarg( $_POST['username'] ); // or where ever you pull this from, must be filled properly
$rating     = escapeshellarg( $_POST['rating'] );   // will just be blank if you call this from a recommend page
$comment    = escapeshellarg( $_POST['comment'] );  // the comment (optional) submitted by the user for the rating
$gameURI    = escapeshellarg( $_POST['gameURI'] );  // or where ever you pull this from, will just be blank for recommend

if ( $userAction == 0 )
{
  // "0, <username>, <results storage location>"
  $cmd = "0 $username $storageLoc";
}

else if ( $userAction == 1 )
{
  // "1, <username>, <gameURI>, <new rating>, <results storage location>"
  $cmd = "1 $username $gameURI $rating $comment $storageLoc";
}

$output = shell_exec( "java main.class $cmd" );

// $output will just be a 0 or 1 for successful/unsuccessful run of the program

/* 
main.class will store the results of the program into $storageLoc/results.txt
the stored string in results.txt can be a properly formatted HTML string or
whatever it needs to be. Suggest that it stores raw results and the HTML formating
is done elsewhere via a PHP script
*/

?>