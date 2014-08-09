<?php
  include "includes/functions.php";
  
  session_start();
  
  // clean input values and copy them into a new array
  $q = safe_inputs( $_POST );
  
  // connect to the database
  my_mysql_connect();
  
  $result = array();
  
  $result = my_trusted_mysql_query("SELECT AccountNumber FROM Account WHERE UserName = '$q[userName]' AND Password = '$q[password]'");
  
  $_SESSION["LoginErr"] = 1;
  
  if ( count($result) == 1 )
  {
	//echo $result[0];
	$_SESSION["username"] = $_POST["userName"];
	$_SESSION["AcctNumber"] = $result[0]["AccountNumber"];
  
  // For the questionnaire results, '1' means a message will be displayed to
  // inform the user the storage went properly.
  $_SESSION["QuestionnaireFilled"] = 0;
	
	$result = my_trusted_mysql_query("SELECT Admin FROM Account WHERE UserName = '$q[userName]' AND Password = '$q[password]'");
	
	$_SESSION["adminLvl"] = $result[0]["Admin"];
  }
  
  my_mysql_close();
  
  if ( isset($_SESSION["AcctNumber"]) )
  {
    $_SESSION["LoginErr"] = 0;
    header('Location: http://minersoft.org/gamewarp/');
  }
  else
  {
    header('Location: http://minersoft.org/gamewarp/newaccount.php');
  }
?>