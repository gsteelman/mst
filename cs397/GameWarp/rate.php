<?php include 'sessionHandler.php'; ?>

<?php
  include "includes/functions.php";
  
  $q = safe_inputs( $_POST );
	
  $cmd        = "";
  $storageLoc = ".";
  $username   = $_SESSION["username"];
	$gameuri = $q["gameuri"];
	$score = $q["score"];
  $comment = $q["comment"];
  $accntnum = $_SESSION["AcctNumber"];
   
  // connect to the database
  //my_mysql_connect();
  //Insert statement for GameSubGenreQuestionnaire
  //$sql="INSERT INTO UserGameRatings(AccountNumber, GameURI, Rating, Comment)
  //VALUES('$accntnum', '$gameuri', '$score', '$comment')";
  //my_trusted_mysql_query($sql);
  //my_mysql_close();
  
  // @note For Recommendation algorithm the parameter list needs to be:
 //             "0, <username>, <results storage location>"
 // @note For Rating algorithm the parameter list needs to be:
 //             "1, <username>, <gameURI>, <new rating>, <comment>, <results storage location>"
  
  //Nevermind, just run our algorithm.
  $cmd = "1 $username $gameuri $score \"$comment\" \"$storageLoc\" \"supadup\"";

  $output = shell_exec( "java -Xmx100M -Xms100M -jar GameWarp.jar $cmd" );
  
  header('Location: http://minersoft.org/gamewarp/rateagame.php');
  
?>
