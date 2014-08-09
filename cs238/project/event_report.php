<META name="verify-v1" content="6q6waintnJ2Z4K032AMMXjPPj3/YjkWR96eHAY3rD5I=" />

<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">

<META NAME="Author" CONTENT="Dale Twombly">

<META NAME="Keywords" CONTENT="Maelstrom, Group 13">

<META NAME="Description" CONTENT="Group 13's Database UI">

<META NAME="rating" content="General">

<META NAME="robots" content="All">

<META NAME="revisit-after" content="7 days">

<META NAME="distribution" content="global">

<title>Event Report</title>

<link href="includes/style.css" rel="stylesheet" type="text/css">

<script language="JavaScript" img src="includes/functions.js"></script>



<body>



<style type="text/css">

    <!--

    .style21

    {

        color: #A5A9B5;

        width: 756px;

    }

    .style25

    {

        width: 54px;

    }

    .style26

    {

        font-family: Sylfaen;

    }

-->

</style>

<table width="100%" height="100%"  border="0" cellpadding="0" cellspacing="0">

  <tr>

    <td background="back.gif"><table width="800" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#CCCCCC" style="border:1 solid #790000;">

      <tr>

        <td colspan="2"><div align="left" style="background-color: #1195F0"><img src="header-1.jpg" width="800" height="136"></div></td>

      </tr>

      <tr>

        <td align="left" valign="top" 

              style="background-color: #1295F0" class="style25"><table align="left" border="0" cellpadding="0" cellspacing="0" width="152">

         <tr>

            <td width="152"><table width="152" border="0" align="left" cellpadding="0" cellspacing="0" bgcolor="#999999">

         <tr>

            <?php include("left_menu.html"); ?>  



         </tr>

</table>

</td>

          </tr>



        </table></td>

        <td align="left" width="100%" style="background-color: #FFFFFF" class="style26">

         <center>Events currently in the database:<br /><br /></center>

<?php 
include "includes/functions.php";

//Connect to the database
my_mysql_connect();     

display_results(my_trusted_mysql_query( "SELECT * FROM EVENT"));

$total_event = count(my_trusted_mysql_query( "SELECT * FROM EVENT"));

echo "<br />Total Events: ";   
echo "$total_event";

my_mysql_close();

?>

         <br /><br />   

         </td>

      </tr>

      <tr>

        <td colspan="2"><table align="left" border="1" cellpadding="0" cellspacing="0" width="100%">

  <tr>

    <td height="38" background="/images/index_r17_c9.jpg" class="style21">

        <div align="center">Patents and Copyrights owned by Maelstrom, Not for use by others</span><strong>.</strong><br>

        </div></td>

  </tr>

</table>

</td>

      </tr>

    </table></td>

  </tr>

</table>

