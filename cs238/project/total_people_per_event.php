<html>
<title>
Company Test
</title>
<body>

<!-- The php script for generating the table and handling database queries -->
<?php 

include "includes/functions.php";

my_mysql_connect();
echo "<h1><CENTER>Class</CENTER></h1>";  
//Displays the total people at each class
display_results(my_trusted_mysql_query( "SELECT Event_ID, count(Email) FROM C_ATTEND GROUP BY Event_ID"));
echo "<h1><CENTER>Session</CENTER></h1>";  
//Displays the total people at each Session
display_results(my_trusted_mysql_query( "SELECT Event_ID, count(Email) FROM S_ATTEND GROUP BY Event_ID"));
my_mysql_close();
        
?>

</body>
</html> 
