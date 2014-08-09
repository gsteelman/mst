<?php include 'sessionHandler.php'; ?>

<html>
<head>
    <title>New Account</title>
    <?php include'style.html'; ?>
</head>
<body bgcolor="Black">
    <SPAN style="FONT-FAMILY: Arial">
        <table width="900" align="center" border="0" cellpadding="0" cellspacing="0">
            <?php include'menu.php'; ?>
                <tr><td><table width="100%" background="bg.jpg" background-attachment="fixed">
                    <tr><td width="5"></td><td>&nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">New Account</span></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td><hr width="100%" /></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>
<?php

include "includes/functions.php";

if(!$_POST["email"] == "" && (!strstr($_POST["email"],"@") || !strstr($_POST["email"],"."))) 
{
	echo "<span class=\"sysnotes\">Use \"Back\" - please enter a valid e-mail.</span>"; 
}
else if (empty($_POST["name"]) || empty($_POST["password"]) || empty($_POST["email"]))
{
	echo "<span class=\"sysnotes\">Use \"Back\" - please fill in all fields.</span>";
}
else
{
	// Array to hold all game genres
	$genrearray = array();
	$genrearray[0] = "action";
	$genrearray[1] = "adventure";
	$genrearray[2] = "actionAdventure";
	$genrearray[3] = "driving";
	$genrearray[4] = "rpg";
	$genrearray[5] = "simulation";
	$genrearray[6] = "sports";
	$genrearray[7] = "strategy";
	$genrearray[8] = "puzzle";
	$genrearray[9] = "shooter";
	$genrearray[10] = "rhythm";
	$genrearray[11] = "party";
	$genrearray[12] = "fighting";
	$genrearray[13] = "wrpg";
	$genrearray[14] = "jrpg";
	$genrearray[15] = "baseball";
	$genrearray[16] = "basketball";
	$genrearray[17] = "golf";
	$genrearray[18] = "boxing";
	$genrearray[19] = "mma";
	$genrearray[20] = "wrestling";
	$genrearray[21] = "football";
	$genrearray[22] = "hockey";
	$genrearray[23] = "miscellaneous";
	$genrearray[24] = "realTime";
	$genrearray[25] = "turnBased";
	$genrearray[26] = "dancing";
	$genrearray[27] = "singing";
	$genrearray[28] = "instruments";
	$genrearray[29] = "fps";
	$genrearray[30] = "tps";
	$genrearray[31] = "shmup";
	$genrearray[32] = "railShooter";
	$genrearray[33] = "trivia";
	
	// Array to hold all theatrical genres
	$theatrearray = array();
	$theatrearray[0] = "action";
	$theatrearray[1] = "adventure";
	$theatrearray[2] = "comedy";
	$theatrearray[3] = "crimeAndGangster";
	$theatrearray[4] = "drama";
	$theatrearray[5] = "epicsAndHistorical";
	$theatrearray[6] = "fantasy";
	$theatrearray[7] = "horror";
	$theatrearray[8] = "musicAndDancing";
	$theatrearray[9] = "mystery";
	$theatrearray[10] = "sciFi";
	$theatrearray[11] = "war";
	$theatrearray[12] = "western";
	$theatrearray[13] = "wwii";
	$theatrearray[14] = "postApocalyptic";
	
	// Array to hold all attributes
	$attributesarray = array();
	$attributesarray[0] = "rendered2D";
	$attributesarray[1] = "rendered3D";
	$attributesarray[2] = "played2D";
	$attributesarray[3] = "played3D";
	$attributesarray[4] = "played4D";
	$attributesarray[5] = "alignment";
	$attributesarray[6] = "zombies";
	$attributesarray[7] = "dragons";
	$attributesarray[8] = "elves";
	$attributesarray[9] = "warlocks";
	$attributesarray[10] = "ghosts";
	$attributesarray[11] = "vampires";
	$attributesarray[12] = "werewolves";
	$attributesarray[13] = "mummies";
	$attributesarray[14] = "trolls";
	$attributesarray[15] = "madScientists";
	$attributesarray[16] = "robots";
	$attributesarray[17] = "aliens";
	$attributesarray[18] = "armedForces";
	$attributesarray[19] = "terrorists";
	$attributesarray[20] = "nazis";
	$attributesarray[21] = "ninjas";
	$attributesarray[22] = "samurai";
	$attributesarray[23] = "pirates";
	$attributesarray[24] = "superheroes";
	$attributesarray[25] = "supervillains";
	$attributesarray[26] = "lasers";
	$attributesarray[27] = "laserGuns";
	$attributesarray[28] = "laserSwords";
	$attributesarray[29] = "swords";
	$attributesarray[30] = "guns";
	$attributesarray[31] = "grinding";
	$attributesarray[32] = "cooking";
	$attributesarray[33] = "casual";
	$attributesarray[34] = "miniGames";
	$attributesarray[35] = "collection";
	$attributesarray[36] = "horses";
	$attributesarray[37] = "pets";
	$attributesarray[38] = "userGeneratedContent";
	$attributesarray[39] = "timeSensitive";
	$attributesarray[40] = "scary";
	$attributesarray[41] = "survival";
	$attributesarray[42] = "multiplayer";
	$attributesarray[43] = "mmo";
	$attributesarray[44] = "online";
	$attributesarray[45] = "cooperative";
	$attributesarray[46] = "sandbox";
	$attributesarray[47] = "crafting";	
	
	// clean input values and copy them into a new array
	$q = safe_inputs( $_POST );
		
	$name = $q["name"];
	$password = $q["password"];
	$email = $q["email"];
	
	// connect to the database
	my_mysql_connect();
	 
	echo "Connecting to the database... <br>";
  
	// Insert statement for Account table
	$sql="INSERT INTO Account(UserName ,Password, Email, Admin)
	VALUES('$name', '$password', '$email', '0')";

	my_trusted_mysql_query($sql);
	
	// retreive the new account's accountnumber
	$accountnumber = mysql_insert_id();
	
	echo "Account number: $accountnumber <br>";
	
	//Insert statement for GameGenreQuestionnaire
	$sql="INSERT INTO  GameGenreQuestionnaire(AccountNumber)
	VALUES('$accountnumber')";
		
	my_trusted_mysql_query($sql);
	
	//Insert statement for GameSubGenreQuestionnaire
	$sql="INSERT INTO  GameSubGenreQuestionnaire(AccountNumber)
	VALUES('$accountnumber')";
		
	my_trusted_mysql_query($sql);
	
	//Insert statement for TheatricalGenreQuestionnaire
	$sql="INSERT INTO  TheatricalGenreQuestionnaire(AccountNumber)
	VALUES('$accountnumber')";
		
	my_trusted_mysql_query($sql);
	
	//Insert statement for TheatricalSubGenreQuestionnaire
	$sql="INSERT INTO  TheatricalSubGenreQuestionnaire(AccountNumber)
	VALUES('$accountnumber')";
		
	my_trusted_mysql_query($sql);
	
	// Insert statement for UserGameConsoles
	//$sql="INSERT INTO  UserGameConsoles(AccountNumber)
	//VALUES('$accountnumber')";
		
	//my_trusted_mysql_query($sql);
	
	// Insert statement for game genres 
	foreach ($genrearray as $genre)
	{
		//echo "Array element: $genre <br>";
		
		$sql="INSERT INTO UserProfileGenres(AccountNumber, Genre)
		VALUES('$accountnumber', '$genre')";
		
		my_trusted_mysql_query($sql);
	}
		
	// Insert statement for theatrical genres 
	foreach ($theatrearray as $genre)
	{
		//echo "Array element: $genre <br>";
	
		$sql="INSERT INTO UserProfileTheatricalGenres(AccountNumber, Genre)
		VALUES('$accountnumber', '$genre')";
		
		my_trusted_mysql_query($sql);
		
	}
	
	// Insert statement for attributes
	foreach ($attributesarray as $genre)
	{
		//echo "Array element: $genre <br>";
	
		$sql="INSERT INTO UserProfileAttributes(AccountNumber, Attribute)
		VALUES('$accountnumber', '$genre')";
		
		my_trusted_mysql_query($sql);
	}
	
	echo "Account Information successfully stored. <br>";
	
	// close connection
	my_mysql_close();
	
	echo "Disconnected from Database. <br>";
	
	date_default_timezone_set('America/Mexico_City');
	
	$todayis = date("l, F j, Y, g:i a") ;

	$attn = "Account Created" ; 
	$subject = "Account Created" ; 

	$body = " $todayis [CST] \n
	Your account information is as follows: \n
	Account Name: $name \n
	Password: $password \n
	E-mail: $email \n
	Please save this e-mail for your records.
	";

	$from = "From: GameWarp\r\n";

	mail($email, $subject, $body, $from);
	
	echo "You are now ready to start using the system! Thank you!";
}

?></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    </form>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>
</html>