<?php

/**
 * file: populate.php
 * brief: populates the database with some information
 */
 
include "includes/functions.php";
include "includes/config.php";

//Connect to the database
my_mysql_connect();

//Delete all previous records in company table.
my_trusted_mysql_query( "DELETE FROM COMPANY" );
my_trusted_mysql_query( "DELETE FROM EVENT" );
my_trusted_mysql_query( "DELETE FROM CLASS_PARTICIPANT" );
my_trusted_mysql_query( "DELETE FROM SCREEN_PARTICIPANT" );
my_trusted_mysql_query( "DELETE FROM STAFF" );
my_trusted_mysql_query( "DELETE FROM C_ATTEND" );
my_trusted_mysql_query( "DELETE FROM S_ATTEND" );

//The array that stores each INSERT query as an element. 
//Can run through them in a loop later, easy-peasy
$population = array(
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('awesome@maelstrom.com', 'Maelstrom', '321 Money Ln', 'Rolla', 'MO', 64014)",
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('mage_killer@maelstrom.com', 'Mage_Killer', '456 Rock Face Rd', 'Middle-earth', 'TX', 22215)",
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('br@maelstrom.com', 'br?', 'Dirt Road', 'Brazil', 'BR', 11111)",
"INSERT INTO COMPANY (Email, Name, Address, City, State, Zip)
VALUES ('efsie@maelstrom.com', 'Efsie', 'Rich Pl', 'Gojira', 'JP', 01235)",

// Matt's Inserts
"INSERT INTO STAFF (Fname, Lname, Email, Address, City, State, Zip, Comments, Password)
VALUES ( 'James', 'Bond', 'laskdfl@maelstrom.com', '1803 awesome Rd', 'Rolla', 'MO', 65401, NULL, 12345)",
"INSERT INTO STAFF (Fname, Lname, Email, Address, City, State, Zip, Comments, Password)
VALUES ( 'Frank', 'Sims', 'FSims@maelstrom.com', 'Ice cap', 'North Pole', 'NP', 71374, NULL, 123123)",

"INSERT INTO SCREEN_PARTICIPANT (Email, Fname, Lname, Address, City, State, Zip, Comments, Time)
VALUES ('blarg@maelstrom.com', 'Pope', 'Joe', '123 Holy Rd', 'Vatican', 'Vatican', 77777, NULL, 7 )",

"INSERT INTO CLASS_PARTICIPANT (Email, Fname, Lname, Address, City, State, Zip, Comments, BCBSNum, BCBSSuffix, Birth_Date)
VALUES ('lala@maelstrom.com', 'Peter', 'Parker', '20 Ingram Street', 'Queens', 'NY', 11428, 'AKA spiderman', 7, 8, '4/3/1962' )",

"INSERT INTO EVENT (EVENT_ID, Event_Name, Start_Date, End_Date, Start_Time, End_Time, Comments, E_Type, S_Type, Session_Length)
VALUES (101,'Health Fair', 6, 9, 7, 8, NULL, 's', 'Fair', 15 )",
"INSERT INTO EVENT (EVENT_ID, Event_Name, Start_Date, End_Date, Start_Time, End_Time, Comments, E_Type, S_Type, Session_Length)
VALUES (102,'Quit Smoking', 6, 9, 7, 8, NULL, 'c', NULL, NULL )",

"INSERT INTO C_ATTEND (Email, Event_ID)
VALUES ('lala@maelstrom.com', 102)",

"INSERT INTO S_ATTEND (Email, Event_ID)
VALUES ('blarg@maelstrom.com', 101)"
);


//Perform the queries, huzzah
foreach ($population as $query) 
{ 
  echo "> " . $query . "<br />";
  my_trusted_mysql_query($query); 
}

//Confirm the insertions
display_results(my_trusted_mysql_query( "SELECT * FROM COMPANY" ));
display_results(my_trusted_mysql_query( "SELECT * FROM EVENT" ));
display_results(my_trusted_mysql_query( "SELECT * FROM CLASS_PARTICIPANT" ));
display_results(my_trusted_mysql_query( "SELECT * FROM SCREEN_PARTICIPANT" ));
display_results(my_trusted_mysql_query( "SELECT * FROM STAFF" ));
display_results(my_trusted_mysql_query( "SELECT * FROM C_ATTEND"));
display_results(my_trusted_mysql_query( "SELECT * FROM S_ATTEND"));


//Close connection to database
my_mysql_close();

?> 
