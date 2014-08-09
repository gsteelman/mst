<META name="verify-v1" content="6q6waintnJ2Z4K032AMMXjPPj3/YjkWR96eHAY3rD5I=" />
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
<META NAME="Author" CONTENT="Dale Twombly">
<META NAME="Keywords" CONTENT="Maelstrom, Group 13">
<META NAME="Description" CONTENT="Group 13's Database UI">
<META NAME="rating" content="General">
<META NAME="robots" content="All">
<META NAME="revisit-after" content="7 days">
<META NAME="distribution" content="global">
<title>Staff Member</title>
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
<!-- The php script for generating the tables and handling database queries --><!-- For proper HTML rendering, this must be left completely left-aligned! -->
<?php 
include "includes/functions.php";
//See if the page was called with POST data, meaning this page has been called before
if (isset($_POST['submit']))
{ 
  //Check various conditions to make sure input is valid.
  if ( !preg_match('/^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z.]{2,5}$/', $_POST['Email']) )
  {
    echo "Invalid Email entered. Email must be in the format \"name@server.com\"<br />";
  }
  //Input data was valid
  else
  {  
    //Copy $_POST data, sanitizing it to prevent SQL injection attacks.
    $q = safe_inputs( $_POST );    
    //Force zip code to a number
    $zip_num = (int)$q[Zip];
    $event_id = (int)$q[Event_ID];
    my_mysql_connect();
    
    //Pick the correct query type
    if ($_POST['query_type'] == 'insert')
    {    
      //Name can't be blank on insertion
      if ($_POST['Fname'] == '' || $_POST['Lname'] == '')
      {
        echo "Invalid Name entered. Niether fields of the name can be blank. <br />";
      }
      //Event_ID can't be blank on insertion
      else if ($_POST['Event_ID'] == '')
      {
        echo "Invalid Event ID entered. Event ID cannot be blank. <br />";
      }
      //Event_ID must be the same as a class or screening in the event table on insertion
      else if (count( my_trusted_mysql_query("SELECT Event_ID FROM EVENT WHERE Event_ID = $event_id AND E_Type = 'c'")) == 0 && count( my_trusted_mysql_query("SELECT Event_ID FROM EVENT WHERE Event_ID = $event_id AND E_Type = 's'")) == 0)
      {
        echo "Invalid Event ID entered. There is no class or screening with that Event ID. <br />";
      }
      //Person is already in the STAFF table.
      else if( count( my_trusted_mysql_query("SELECT Email FROM STAFF WHERE Email = '$q[Email]'")) > 0) 
      {
        //see if person is already in TEACH or ADMINISTER table with this event
        if( count( my_trusted_mysql_query("SELECT Email FROM TEACH WHERE Email = '$q[Email]' AND Event_ID = $event_id")) > 0 || count( my_trusted_mysql_query("SELECT Email FROM ADMINISTER WHERE Email = '$q[Email]' AND Event_ID = $event_id")) > 0 )
        {
            echo "The Person with the e-mail " . $q['Email'] . " is already a teacher or administer for the given event. " .
            "To edit this person's information, please select update instead of insert. To remove this person from the event, select Delete<br /><br />";
            $_POST['Fill'] = 'true';
        }
        else
        {
            //Perform the insertion into TEACH or ADMINISTER
            if( count( my_trusted_mysql_query("SELECT Email FROM EVENT WHERE Event_ID = $event_id AND E_Type = 'c'")) > 0)
            {
                $query = "INSERT INTO TEACH (Event_ID, Email)
                VALUES ('$q[Email]', $event_id)";

                my_trusted_mysql_query( $query );

                echo "Record inserted: <br />";
                display_results(my_trusted_mysql_query( "SELECT * FROM TEACH WHERE Email = '$q[Email]' AND Event_ID = $event_id" ));
            }
            if( count( my_trusted_mysql_query("SELECT Email FROM EVENT WHERE Event_ID = $event_id AND E_Type = 's'")) > 0)
            {
                $query = "INSERT INTO ADMINISTER (Event_ID, Email)
                VALUES ('$q[Email]', $event_id)";

                my_trusted_mysql_query( $query );

                echo "Record inserted: <br />";
                display_results(my_trusted_mysql_query( "SELECT * FROM ADMINISTER WHERE Email = '$q[Email]' AND Event_ID = $event_id" ));
            }

         }
      }
    
      else
      {
        //Perform the insertion into STAFF
        $query = "INSERT INTO STAFF (Email, Fname, Lname, Address, City, State, Zip, Comments, Password) 
        VALUES ('$q[Email]', '$q[Fname]', '$q[Lname]', '$q[Address]', '$q[City]', '$q[State]', $zip_num, '$q[Comments]', '$q[Password]')";

        my_trusted_mysql_query( $query );
        
        echo "Your information as a staff member: <br />";
        display_results(my_trusted_mysql_query( "SELECT * FROM STAFF WHERE Email = '$q[Email]'" ));

        //******Perform the insertion into TEACH or ADMINISTER
        if(count( my_trusted_mysql_query("SELECT Event_ID FROM EVENT WHERE Event_ID = $event_id AND E_Type = 'c'")) > 0)
        {
            //Perform the insertion into TEACH
            $query = "INSERT INTO TEACH (Event_ID, Email) VALUES ($event_id, '$q[Email]')";

            my_trusted_mysql_query( $query );

            echo "<br />Your e-mail is now associated with this event: <br />";
            display_results(my_trusted_mysql_query( "SELECT * FROM TEACH WHERE Email = '$q[Email]' AND Event_ID = $event_id" ));
        }
        if(count( my_trusted_mysql_query("SELECT Event_ID FROM EVENT WHERE Event_ID = $event_id AND E_Type = 's'")) > 0)
        {
            //Perform the insertion into ADMINISTER
            $query = "INSERT INTO ADMINISTER (Event_ID, Email) VALUES ($event_id, '$q[Email]')";

            my_trusted_mysql_query( $query );

            echo "<br />Remember this Event ID and the e-mail you used to sign up: <br />";
            display_results(my_trusted_mysql_query( "SELECT * FROM ADMINISTER WHERE Email = '$q[Email]' AND Event_ID = $event_id" ));
        }

        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    else if ($_POST['query_type'] == 'update')
    {
      //Person is not in the database.
      if( count( my_trusted_mysql_query("SELECT Email FROM STAFF WHERE Email = '$q[Email]'") ) == 0 )
      {
        echo "The person with the e-mail " . $q['Email'] . " is not currently in the database as staff member. " .
          "To add this person's information, please select insert instead of update.<br /><br />";
        $_POST['Fill'] = 'true';
      }     
      else
      {                
        //Makes a query to only update fields that were not left blank
        $query  = "UPDATE STAFF SET ";
        $query .=                       "Email='$q[Email]'";

        $query .= $q['Fname']    != '' ? ", Fname='$q[Fname]'" : "";
        $query .= $q['Lname']    != '' ? ", Lname='$q[Lname]'" : "";
        $query .= $q['Address'] != '' ? ", Address='$q[Address]'" : "";
        $query .= $q['City']    != '' ? ", City='$q[City]'"       : "";
        $query .= $q['State']   != '' ? ", State='$q[State]'"     : "";
        $query .= $q['Zip']     != '' ? ", Zip='$zip_num'"        : "";
        $query .= $q['Comments']     != '' ? ", Comments='$q[Comments]'"        : "";
        $query .= $q['Password']     != '' ? ", Password='$q[Password]'"        : "";
        $query .= " WHERE Email='$q[Email]'";

        echo "Old record: <br />";
        display_results( my_trusted_mysql_query( "SELECT * FROM STAFF WHERE Email = '$q[Email]'" ));
      
        my_trusted_mysql_query( $query );
        
        echo "<br />New updated record:";
        display_results( my_trusted_mysql_query( "SELECT * FROM STAFF WHERE Email = '$q[Email]'" ));

        my_mysql_close();
        
        $_POST['Fill'] = 'false';
      }
    }
    
    else if ($_POST['query_type'] == 'delete')
    {    
      //Person is not in the database.
      if( count( my_trusted_mysql_query("SELECT Email FROM STAFF WHERE Email = '$q[Email]'") ) == 0 )
      {
        echo "The person with the e-mail " . $q['Email'] . " is not currently in the database as a staff member. " .
          "To add this person's information, please select insert.<br /><br />";
        $_POST['Fill'] = 'true';
      } 
    
      else
      {        
        //Show the record that's about to be deleted.
        echo "Records deleted:";
        display_results( my_trusted_mysql_query( "SELECT * FROM STAFF WHERE Email = '$q[Email]'" ));

        $query = "DELETE FROM STAFF WHERE Email='$q[Email]'";
        my_trusted_mysql_query( $query );

        if( count( my_trusted_mysql_query("SELECT Email FROM TEACH WHERE Email = '$q[Email]'") ) > 0 )
        {
            display_results( my_trusted_mysql_query( "SELECT * FROM TEACH WHERE Email = '$q[Email]'" ));

            $query = "DELETE FROM TEACH WHERE Email='$q[Email]'";
        
            my_trusted_mysql_query( $query );
        }
        
        if( count( my_trusted_mysql_query("SELECT Email FROM ADMINISTER WHERE Email = '$q[Email]'") ) > 0 )
        {
            display_results( my_trusted_mysql_query( "SELECT * FROM ADMINISTER WHERE Email = '$q[Email]'" ));

            $query = "DELETE FROM ADMINISTER WHERE Email='$q[Email]'";
        
            my_trusted_mysql_query( $query );
        }

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
              <strong>Staff member insert/update/delete instructions:</strong><br />
              <li>The event ID of the class/screening must be be given when inserting a new staff 
                  member.</li>
              <li>When inserting a new staff member, you need to supply as much information as possible about the 
                  person.</li>
              <li>When deleting a staff member, you need only supply the person's e-mail address.<br /></li>
              <li>When updating a staff member's information, make sure the e-mails match, and leave any fields you do not want to change blank.<br /></li>
            </ul>
          </div><!-- The HTML for receiving user input from text boxes and such --><!-- For proper HTML rendering, the php scripts must be left completely left-aligned! -->
<form action="staff_manip.php" method="POST">
<fieldset>
<legend>Select query type</legend>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="insert" checked="checked" />Insert a new 
    staff member's information.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="update" />Update an already inserted&nbsp; 
    staff member's information.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="delete" />Delete an already inserted 
    staff member's information.<br />
</fieldset>
<br />
<br />
          <table class="style26" align="center">
            <tr>
            <td class="style36">Event ID:</td>
            <td class="style36">
<input type="text" name="Event_ID" value="
<?php
if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
{
echo $_POST['BCBSSuffix'];
}
?>" /> (Only valid for insert)</td>
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
              <td class="style28">First Name:</td>
              <td class="style27">
<input type="text" name="Fname" value="
<?php
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Fname']; 
  }
?>
"/>  (Not blank)              </td>
            </tr>
            <tr>
              <td class="style28">Last Name:</td>
              <td class="style27">
<input type="text" name="Lname" value="
<?php
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Lname']; 
  }
?>
"/>  (Not blank)              </td>
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
              <td class="style36">Comments:</td>
              <td class="style36">
              <TEXTAREA class=style5 id=txtRequest name=Comments rows=5 cols=35 value="
                 <?php 
                 if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
                    {
                      echo $_POST['Comments'];
                    }
                 ?>
              "></TEXTAREA>

            </td>
            </tr>
            <tr>
            <td class="style36">Password:</td>
            <td class="style36">
            <input type="text" name="Password" value="
<?php 
              if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
              {
               echo $_POST['Password'];
             }
?>" />                </td>
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
