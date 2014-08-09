<?php include 'sessionHandler.php'; ?>

<?php
  include "includes/functions.php";
  
  // If there is no user, the questionnaire filling out is useless
  
  if ( isset($_SESSION["AcctNumber"]) )
  {
    
    // connect to the database
    my_mysql_connect();
    
    $result = array();
    
    // Prepare the query
    $sql = "UPDATE GameGenreQuestionnaire SET " .
    
    // Grab all the POST data now
    
    "action=" . $_POST["Action"] . ", " .
    "adventure=" . $_POST["Adventure"] . ", " .
    "actionAdventure=" . $_POST["ActionAdventure"] . ", " .
    "driving=" . $_POST["Driving"] . ", " .
    "rpg=" . $_POST["RolePlaying"] . ", " .
    "simulation=" . $_POST["Simulation"] . ", " .
    "sport=" . $_POST["Sport"] . ", " .
    "strategy=" . $_POST["Strategy"] . ", " .
    "puzzle=" . $_POST["Puzzle"] . ", " .
    "shooter=" . $_POST["Shooter"] . ", " .
    "rhythm=" . $_POST["Rhythm"] . ", " .
    "party=" . $_POST["Party"] . ", " .
    "platformer=" . $_POST["Platformer"] .
    " WHERE AccountNumber='$_SESSION[AcctNumber]'";

    $result = my_trusted_mysql_query($sql);
    
    $_SESSION["QuestionnaireFilled"] = 1;
    
    my_mysql_close();
    
    header('Location: http://minersoft.org/gamewarp/questionnaire.php');
  }
  else
  {
    header('Location: http://minersoft.org/gamewarp/newaccount.php');
  }
  
?>
