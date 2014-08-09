<?php include 'sessionHandler.php'; ?>

<html>
<head>
    <title>Contact Us</title>
    <?php include'style.html'; ?>
</head>
<body bgcolor="Black">
    <SPAN style="FONT-FAMILY: Arial">
        <table width="900" align="center" border="0" cellpadding="0" cellspacing="0">
            <?php include'menu.php'; ?>
                <tr><td><table width="100%" background="bg.jpg" background-attachment="fixed">
                    <tr><td width="5"></td><td>&nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Contact Us</span></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td><hr width="100%" /></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td><span class="sysnotes">Request  From: <?php echo $_POST["name"] ?> ( <?php echo $_POST["email"] ?> )</span></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>
<?php

if(!$_POST["email"] == "" && (!strstr($_POST["email"],"@") || !strstr($_POST["email"],"."))) 
{
	echo "<span class=\"sysnotes\">Use \"Back\" - please enter a valid e-mail.</span>"; 
}
else if (empty($_POST["name"]) || empty($_POST["email"]) || empty($_POST["phone"]) || empty($_POST["message"]))
{
	echo "<span class=\"sysnotes\">Use \"Back\" - please fill in all fields.</span>";
}
else
{
	date_default_timezone_set('America/Mexico_City');
	
	$name = $_POST["name"];
	$email = $_POST["email"];
	$phone = $_POST["phone"];
	$message = $_POST["message"];
	
	$todayis = date("l, F j, Y, g:i a") ;

	$attn = "Website Contact Form" ; 
	$subject = "Website Contact Form" ; 

	$body = " $todayis [CST] \n
	From: $name \n
	E-mail: $email \n
	Phone: $phone \n
	Message: $message
	";

	$from = "From: GameWarp\r\n";

	mail("datc5b@mst.edu", $subject, $body, $from);
	mail("gws4g2@mst.edu", $subject, $body, $from);
	
	echo "<span class=\"sysnotes\">Your contact request has been sent! Thank you!</span>";
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
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    </form>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>
</html>