<META name="verify-v1" content="6q6waintnJ2Z4K032AMMXjPPj3/YjkWR96eHAY3rD5I=" />
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
<META NAME="Author" CONTENT="Dale Twombly">
<META NAME="Keywords" CONTENT="Maelstrom, Group 13">
<META NAME="Description" CONTENT="Group 13's Database UI">
<META NAME="rating" content="General">
<META NAME="robots" content="All">
<META NAME="revisit-after" content="7 days">
<META NAME="distribution" content="global">
<title>Company</title>
<link href="includes/style.css" rel="stylesheet" type="text/css">
<script language="JavaScript" img src="includes/functions.js"></script>
<body>
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
<!-- The php script for generating the tables and handling database queries -->
<!-- For proper HTML rendering, this must be left completely left-aligned! -->
<?php 
include "includes/functions.php";

//See if the page was called with POST data, meaning this page has been called before
if (isset($_POST['submit']))
{ 
  //Copy $_POST data, sanitizing it to prevent SQL injection attacks.
  $q = safe_inputs( $_POST ); 

  //Check various conditions to make sure input is valid.
  if ( !preg_match('/^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z.]{2,5}$/', $q['Email']) )
  {
    echo "Invalid E-mail entered. E-mail must be in the format \"name@server.com\"<br />";
  }
  
  else if ( $q['Phone'] != '' && !preg_match('/^\d{3}\-\d{3}\-\d{4}$/', $q['Phone']) )
  {
    echo "Invalid phone number entered. Phone number must be in the format \"XXX-XXX-XXXX\"<br />";
  }
  
  else if ( $q['Phone2'] != '' && !preg_match('/^\d{3}\-\d{3}\-\d{4}$/', $q['Phone2']) )
  {
    echo "Invalid phone number 2 entered. Phone number 2 must be in the format \"XXX-XXX-XXXX\"<br />";
  }
  
  //Input data was valid
  else
  {  
    //Force zip code to a number
    $zip_num = (int)$q[Zip];
    my_mysql_connect();
    
    //Pick the correct query type
    if ($_POST['query_type'] == 'insert')
    {    
      //Name can't be blank on insertion
      if ($_POST['Name'] == '')
      {
        echo "Invalid Name entered. Name cannot be blank. <br />";
      }
    
      //Company is already in the database.
      else if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) > 0 )
      {
        echo "The company with the e-mail " . $q['Email'] . " already exists in the database. " .
          "To edit this company's information, please select update instead of insert.<br /><br />";
        $_POST['Fill'] = 'true';
      } 
    
      else
      {
        //Perform the insertion
        $company_query = "INSERT INTO COMPANY (Email, Name, Address, City, State, Zip) 
        VALUES ('$q[Email]', '$q[Name]', '$q[Address]', '$q[City]', '$q[State]', $zip_num)";

        my_trusted_mysql_query( $company_query );
        
        if ( $q['Phone'] != '' )
        {
          $company_phone_query = "INSERT INTO COMPANY_PHONE (Number, Email)
          VALUES ('$q[Phone]', '$q[Email]')";
        
          my_trusted_mysql_query( $company_phone_query );
        }
        
        if ( $q['Phone2'] != '' )
        {
          $company_phone_query = "INSERT INTO COMPANY_PHONE (Number, Email)
          VALUES ('$q[Phone2]', '$q[Email]')";
        
          my_trusted_mysql_query( $company_phone_query );
        }
        
        echo "Record inserted: <br />";
        display_results(my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));
        display_results(my_trusted_mysql_query( "SELECT Email, Number FROM COMPANY_PHONE WHERE Email = '$q[Email]'" ));
        
        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    
    else if ($_POST['query_type'] == 'update')
    {
      //Company is not in the database.
      if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) == 0 )
      {
        echo "The company with the e-mail " . $q['Email'] . " does not exist in the database. " .
          "To add this company's information, please select insert instead of update.<br /><br />";
        $_POST['Fill'] = 'true';
      } 
      
      else
      {                
        //Makes a query to only update fields that were not left blank
        $company_query  = "UPDATE COMPANY SET ";
        $company_query .=                       "Email='$q[Email]'";
        $company_query .= $q['Name']    != '' ? ", Name='$q[Name]'"       : "";
        $company_query .= $q['Address'] != '' ? ", Address='$q[Address]'" : "";
        $company_query .= $q['City']    != '' ? ", City='$q[City]'"       : "";
        $company_query .= $q['State']   != '' ? ", State='$q[State]'"     : "";
        $company_query .= $q['Zip']     != '' ? ", Zip='$zip_num'"        : "";
        $company_query .= " WHERE Email='$q[Email]'";

        echo "Old record: <br />";
        display_results( my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));
        //display_results( my_trusted_mysql_query( "SELECT Email, Number FROM COMPANY_PHONE WHERE Email = '$q[Email]'" ));
      
        my_trusted_mysql_query( $company_query );
        
        echo "<br />New updated record:";
        display_results( my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));
        //display_results( my_trusted_mysql_query( "SELECT Email, Number FROM COMPANY_PHONE WHERE Email = '$q[Email]'" ));

        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    
    else if ($_POST['query_type'] == 'delete')
    {    
      //Company is not in the database.
      if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) == 0 )
      {
        echo "The company with the e-mail " . $q['Email'] . " does not exist in the database. " .
          "To add this company's information, please select insert.<br /><br />";
        $_POST['Fill'] = 'true';
      } 
    
      else
      {        
        //Show the record that's about to be deleted.
        echo "Record deleted:";
        display_results( my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email = '$q[Email]'" ));
        display_results( my_trusted_mysql_query( "SELECT Email, Number FROM COMPANY_PHONE WHERE Email = '$q[Email]'" ));
      
        $company_query = "DELETE FROM COMPANY WHERE Email='$q[Email]'";
        
        my_trusted_mysql_query( $company_query );
        
        $company_phone_query = "DELETE FROM COMPANY_PHONE WHERE Email='$q[Email]'";
        
        my_trusted_mysql_query( $company_phone_query );
        
        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    
    else
    {
      echo "An unexpected selection has been made. <br />";
      my_mysql_close();
      die();
    }
  }
}
?>
          </div>

          <div class="style35">
            <ul>
              <strong>Company insert/update/delete instructions:</strong><br />
              <li>When inserting a new company, you need to supply as much information as possible about the company.</li>
              <li>When deleting a company, you need only supply the company's e-mail address.<br /></li>
              <li>When updating a company's information, make sure the e-mails match, and leave any fields you do not want to change blank.<br /></li>
            </ul>
          </div><!-- The HTML for receiving user input from text boxes and such --><!-- For proper HTML rendering, the php scripts must be left completely left-aligned! -->
<form action="company_manip.php" method="POST">
<fieldset>
<legend>Select query type</legend>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="insert" checked="checked" />Insert a new company's information.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="update" />Update an already inserted company's information.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="delete" />Delete an already inserted company's information.<br />
</fieldset>
<br />
<br />
          <table class="style26" align="center">
            <tr>
              <td class="style28">Name:</td>
              <td class="style27">
<input type="text" name="Name" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Name']; 
  }
?>
" />  (Not blank)              </td>
            </tr>
            <tr>
              <td class="style28">E-mail:</td>
              <td class="style27">
<input type="text" name="Email" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Email']; 
  }
?>" /> (xyz@abc.com)              </td>
            </tr>
            <tr>
              <td class="style28">Phone Number:</td>
              <td class="style27">
<input type="text" name="Phone" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Phone']; 
  }
?>" /> (XXX-XXX-XXXX)              </td>
            </tr>
            <tr>
              <td class="style28">Phone Number 2:</td>
              <td class="style27">
<input type="text" name="Phone2" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Phone2']; 
  }
?>" /> (XXX-XXX-XXXX)               </td>
            </tr>
            <tr>
              <td class="style28">Address:</td>
              <td class="style27">
<input type="text" name="Address" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true')
  {
    echo $_POST['Address']; 
  }
?>
" />               </td>
            </tr>
            <tr>
              <td class="style28">City:</td>
              <td class="style27"> <input type="text" name="City" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['City'];
  }
?>
" />               </td>
            </tr>
            <tr>              <td class="style28">State:</td>
              <td class="style27">              <!-- why the nbsp here? -->
                <!--&nbsp;--><select name="State">
                  <OPTION value=''></OPTION>
                  <OPTION value=AL>Alabama</OPTION>
                  <OPTION value=AK>Alaska</OPTION>
                  <OPTION value=AZ>Arizona</OPTION>
                  <OPTION value=AR>Arkansas</OPTION>
                  <OPTION value=CA>California</OPTION>
                  <OPTION value=CO>Colorado</OPTION>
                  <OPTION value=CT>Connecticut</OPTION>
                  <OPTION value=DE>Delaware</OPTION>
                  <OPTION value=DC>District of Columbia</OPTION>
                  <OPTION value=FL>Florida</OPTION>
                  <OPTION value=GA>Georgia</OPTION>
                  <OPTION value=HI>Hawaii</OPTION>
                  <OPTION value=ID>Idaho</OPTION>
                  <OPTION value=IL>Illinois</OPTION>
                  <OPTION value=IN>Indiana</OPTION>
                  <OPTION value=IA>Iowa</OPTION>
                  <OPTION value=KS>Kansas</OPTION>
                  <OPTION value=KY>Kentucky</OPTION>
                  <OPTION value=LA>Louisiana</OPTION>
                  <OPTION value=ME>Maine</OPTION>
                  <OPTION value=MD>Maryland</OPTION>
                  <OPTION value=MA>Massachusetts</OPTION>
                  <OPTION value=MI>Michigan</OPTION>
                  <OPTION value=MN>Minnesota</OPTION>
                  <OPTION value=MS>Mississippi</OPTION>
                  <OPTION value=MO>Missouri</OPTION>
                  <OPTION value=MT>Montana</OPTION>
                  <OPTION value=NE>Nebraska</OPTION>
                  <OPTION value=NV>Nevada</OPTION>
                  <OPTION value=NH>New Hampshire</OPTION>
                  <OPTION value=NJ>New Jersey</OPTION>
                  <OPTION value=NM>New Mexico</OPTION>
                  <OPTION value=NY>New York</OPTION>
                  <OPTION value=NC>North Carolina</OPTION>
                  <OPTION value=ND>North Dakota</OPTION>
                  <OPTION value=OH>Ohio</OPTION>
                  <OPTION value=OK>Oklahoma</OPTION>
                  <OPTION value=OR>Oregon</OPTION>
                  <OPTION value=PA>Pennsylvania</OPTION>
                  <OPTION value=RI>Rhode Island</OPTION>
                  <OPTION value=SC>South Carolina</OPTION>
                  <OPTION value=SD>South Dakota</OPTION>
                  <OPTION value=TN>Tennessee</OPTION>
                  <OPTION value=TX>Texas</OPTION>
                  <OPTION value=UT>Utah</OPTION>
                  <OPTION value=VT>Vermont</OPTION>
                  <OPTION value=VA>Virginia</OPTION>
                  <OPTION value=WA>Washington</OPTION>
                  <OPTION value=WV>West Virginia</OPTION>
                  <OPTION value=WI>Wisconsin</OPTION>
                  <OPTION value=WY>Wyoming</OPTION>
                  <OPTION value=International>INTERNATIONAL</OPTION>
                </select>                </td>
            </tr>
            <tr>
              <td class="style36">Zip:</td>
              <td class="style36">
<input type="text" name="Zip" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Zip'];
  }
?>
" />                </td>
            </tr>
            <tr>
              <td>
                <input type="submit" name="submit" value="Submit" />              </td>
            </tr>
          </table>
        <input type="hidden" name="Fill" value="true" /><!-- why the nbsp here? -->
<!--&nbsp;--></form>
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
