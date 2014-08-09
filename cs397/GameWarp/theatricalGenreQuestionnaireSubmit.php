<?php include 'sessionHandler.php'; ?>

<?php
  include "includes/functions.php";
  
  // If there is no user, the questionnaire filling out is useless
  
  if ( isset($_SESSION["AcctNumber"]) )
  {
    
    // connect to the database
    my_mysql_connect();
    
    // Prepare the query
    $sql = "UPDATE TheatricalGenreQuestionnaire SET " .
    
    // Grab all the POST data now
    
    "action=" . $_POST["Action"] . ", " .
    "adventure=" . $_POST["Adventure"] . ", " .
    "comedy=" . $_POST["Comedy"] . ", " .
    "crimeAndGangster=" . $_POST["CrimeAndGangster"] . ", " .
    "drama=" . $_POST["Drama"] . ", " .
    "epicsAndHistorical=" . $_POST["EpicsAndHistorical"] . ", " .
    "fantasy=" . $_POST["Fantasy"] . ", " .
    "horror=" . $_POST["Horror"] . ", " .
    "musicAndDancing=" . $_POST["MusicAndDancing"] . ", " .
    "mystery=" . $_POST["Mystery"] . ", " .
    "sciFi=" . $_POST["ScienceFiction"] . ", " .
    "war=" . $_POST["War"] . ", " .
    "western=" . $_POST["Western"] .
    " WHERE AccountNumber='$_SESSION[AcctNumber]'";
    
    my_trusted_mysql_query($sql);
    
    $_SESSION["QuestionnaireFilled"] = 1;
    
    my_mysql_close();
    
    header('Location: http://minersoft.org/gamewarp/questionnaire.php');
  }
  else
  {
    header('Location: http://minersoft.org/gamewarp/newaccount.php');
  }
  
?>
