<META name="verify-v1" content="6q6waintnJ2Z4K032AMMXjPPj3/YjkWR96eHAY3rD5I=" />
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
<META NAME="Author" CONTENT="Dale Twombly">
<META NAME="Keywords" CONTENT="Maelstrom, Group 13">
<META NAME="Description" CONTENT="Group 13's Database UI">
<META NAME="rating" content="General">
<META NAME="robots" content="All">
<META NAME="revisit-after" content="7 days">
<META NAME="distribution" content="global">
<title>Special Query 3</title>
<link href="includes/style.css" rel="stylesheet" type="text/css">
<script language="JavaScript" img src="includes/functions.js"></script>
<body onLoad="MM_preloadImages('/images/index_r3_c7_f2.jpg','/images/index_r3_c9_f2.jpg','/images/index_r2_c1_f2.jpg','/images/index_r3_c1_f2.jpg','/images/index_r4_c1_f2.jpg','/images/index_r6_c1_f2.jpg','/images/index_r7_c1_f2.jpg','/images/index_r9_c1_f2.jpg','/images/index_r10_c1_f2.jpg','/images/index_r11_c1_f2.jpg','/images/index_r16_c2_f2.jpg','/images/header1.jpg','/images/header2.jpg','/images/header3.jpg','/images/header4.jpg','/images/header5.jpg','/images/header6.jpg','/images/header7.jpg','/images/header8.jpg','/images/header9.jpg','/images/header10.jpg');runSlideShow()">
<style type="text/css">
    <!--
    .style21
    {
        color: #000000;
        width: 756px;
        background-color: #CCCCCC;
    }
    .style33
    {
        color: #808080;
        font-family: Sylfaen;
    }
    .style34
    {
        color: #000000;
        width: 756px;
        text-align: left;
        height: 528px
    }
    .style35
    {
        text-align: left;
    }
    .style36
    {
        height: 31px;
    }
    .style37
    {
        height: 528px;
    }
    .style38
    {
        height: 136px;
    }
-->
</style>
<table width="100%" height="100%"  border="0" cellpadding="0" cellspacing="0">
  <tr>
    <td background="back.gif"><table width="800" border="0" align="center" 
      cellpadding="0" cellspacing="0" bgcolor="#CCCCCC" 
      style="border:1 solid #790000; background-color: #1495F1;">
      <tr>
        <td colspan="2" class="style38"><div align="left" style="background-color: #1195F0">

            <a href="admin_index.php" style="background-color: #AFB5C2"><img src="header-1.jpg" width="800" height="136" 

                style="border-width: 0px"></a></div></td>
      </tr>
      <tr>
        <td align="left" valign="top" style="background-color: #1295F0" class="style37">          <table align="left" border="0" cellpadding="0" cellspacing="0" width="152">
            <tr>
              <td width="152">                <table width="152" border="0" align="left" cellpadding="0" cellspacing="0" bgcolor="#999999">
                  <?php include("left_menu.html"); ?>
                </table>
              </td>
            </tr>
          </table>        </td>
        <td style="background-color: #FFFFFF; font-family: Sylfaen;" class="style34">
          <div align="center">

<?php 

include "includes/functions.php";

//See if the page was called with POST data, meaning this page has been called before
if (isset($_POST['submit']))
{ 
  //Copy $_POST data, sanitizing it to prevent SQL injection attacks.
  $q = safe_inputs( $_POST );    
  
  my_mysql_connect();
  
  //Check various conditions to make sure input is valid.
  if ( !preg_match('/^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z.]{2,5}$/', $_POST['Email']) )
  {
    echo "Invalid E-mail entered. E-mail must be in the format \"name@server.com\"<br />";
  }

  //Company is not in the database.
  if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) == 0 )
  {
    echo "The company with the e-mail " . $q['Email'] . " does not exist in the database. " .
      "To add this company's information, please select insert instead of update.<br /><br />";
    $_POST['Fill'] = 'true';
  }  
  
  else
  {
    echo "All events hosted by the company with e-mail " . $q['Email'] . ": <br />";
    display_results( my_trusted_mysql_query(    
      "SELECT * FROM EVENT WHERE Event_ID IN (SELECT Event_ID FROM HOSTS WHERE Email='$q[Email]')" 
    ));
   
    my_mysql_close();
    
    $_POST['Fill'] = 'false';
  }
}
?>
          </div>
          <div class="style35">
            <ul>
              <strong>View all classes or screenings hosted by a specific company:</strong><br />
              <li>The company must already be in the database.</li>
            </ul>
          </div>

<!-- The HTML for receiving user input from text boxes and such -->
<!-- For proper HTML rendering, the php scripts must be left completely left-aligned! -->
<form action="special_company_events.php" method="POST">
          <table class="style26" align="center">
            <tr>
              <td class="style28">Company's E-mail:</td>
              <td class="style27">
<input type="text" name="Email" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Email']; 
  }
?>
" />
              </td>
              <td>
                <input type="submit" name="submit" value="Submit" />
              </td>
            </tr>
          </table>
        <input type="hidden" name="Fill" value="true" />
        </form>
        </td>
      </tr>
      <tr>
        <td colspan="2">          <table align="left" border="1" cellpadding="0" cellspacing="0" width="100%">
            <tr>
              <td height="38" background="/images/index_r17_c9.jpg" class="style21">
                <div align="center">                  <span class="style33">                    Patents and Copyrights owned by Maelstrom, Not for use by others.                  </span>                  <!-- why the br? -->                  <!--<br />-->
                </div>              </td>
            </tr>
          </table>
        </td>
      </tr>
    </table>    </td>
  </tr>
</table>