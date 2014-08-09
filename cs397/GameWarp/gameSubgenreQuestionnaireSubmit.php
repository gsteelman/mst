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
    $sql = "UPDATE GameSubGenreQuestionnaire SET " .
    
    // Grab all the POST data now
    
    "fighting=" . $_POST["Fighting"] . ", " .
    "driving=" . $_POST["Driving"] . ", " .
    "wrpg=" . $_POST["WRPG"] . ", " .
    "jrpg=" . $_POST["JRPG"] . ", " .
    "baseball=" . $_POST["Baseball"] . ", " .
    "basketball=" . $_POST["Basketball"] . ", " .
    "golf=" . $_POST["Golf"] . ", " .
    "boxing=" . $_POST["Boxing"] . ", " .
    "mma=" . $_POST["MMA"] . ", " .
    "wrestling=" . $_POST["Wrestling"] . ", " .
    "football=" . $_POST["Football"] . ", " .
    "hockey=" . $_POST["Hockey"] . ", " .
    "miscellaneous=" . $_POST["Miscellaneous"] . ", " .
    "realTime=" . $_POST["RealTime"] . ", " .
    "turnBased=" . $_POST["TurnBased"] . ", " .
    "dancing=" . $_POST["Dancing"] . ", " .
    "singing=" . $_POST["Singing"] . ", " .
    "instruments=" . $_POST["Instruments"] . ", " .
    "fps=" . $_POST["FirstPerson"] . ", " .
    "tps=" . $_POST["ThirdPerson"] . ", " .
    "shmup=" . $_POST["ShootEmUp"] . ", " .
    "railShooter=" . $_POST["RailShooter"] . ", " .
    "trivia=" . $_POST["Trivia"] .
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
