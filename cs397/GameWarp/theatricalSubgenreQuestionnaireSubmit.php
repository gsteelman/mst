<?php include 'sessionHandler.php'; ?>

<?php
  include "includes/functions.php";
  
  // If there is no user, the questionnaire filling out is useless
  
  if ( isset($_SESSION["AcctNumber"]) )
  {
    
    // connect to the database
    my_mysql_connect();
    
    // Prepare the query
    $sql = "UPDATE TheatricalSubGenreQuestionnaire SET " .
    
    // Grab all the POST data now
    
    "wwii=" . $_POST["WorldWarTwo"] . ", " .
    "postApocalyptic=" . $_POST["PostApocalyptic"] .
    " WHERE AccountNumber='$_SESSION[AcctNumber]'";

    echo "$sql";
    
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
