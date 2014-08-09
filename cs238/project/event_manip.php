<META name="verify-v1" content="6q6waintnJ2Z4K032AMMXjPPj3/YjkWR96eHAY3rD5I=" />
<META HTTP-EQUIV="Content-Type" CONTENT="text/html; charset=iso-8859-1">
<META NAME="Author" CONTENT="Dale Twombly">
<META NAME="Keywords" CONTENT="Maelstrom, Group 13">
<META NAME="Description" CONTENT="Group 13's Database UI">
<META NAME="rating" content="General">
<META NAME="robots" content="All">
<META NAME="revisit-after" content="7 days">
<META NAME="distribution" content="global">
<title>Enter The Maelstrom</title>
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
  
  //Force zip code to a number
  $Zip_num = (int)$q['Zip'];
  
  //Force event ID into a number
  $Event_ID_num = (int)$q['Event_ID'];
   
  //"sunday, monday, tuesday, wednesday, thursday, friday, saturday"
  //Creates the class dates string
  $Class_Days_string = "";
  if ( count( $_POST['Class_Days'] ) > 0 )
  {
    foreach($_POST['Class_Days'] as $key => $value) 
    {
      $Class_Days_string .= $value . ', ';
    }
    
    $Class_Days_string = rtrim($Class_Days_string, ", ");
  }
  
  //Force session length into a number
  $Session_Length_num = (int)$q['Session_Length'];
  
  //Force occupants into a number
  $Occupants_num = (int)$q['Occupants'];
  
  //Set the event type
  $E_Type_char = ($_POST['S_Type'] != '' && $Session_Length_num != 0) ? 's' : 'c';
  
  my_mysql_connect();
  
  //Pick the correct query type
  if ($_POST['query_type'] == 'insert')
  {    
    //Email can't be blank on insertion
    if ($_POST['Email'] == '' || !preg_match('/^[a-zA-Z0-9._-]+@[a-zA-Z0-9-]+\.[a-zA-Z.]{2,5}$/', $_POST['Email']))
    {
      echo "Invalid Sponsoring Company e-mail entered. Sponsoring Company e-mail cannot be blank and must be in the format of (xyz@abc.com). <br />";
    }
  
    //Name can't be blank on insertion
    else if ($_POST['Event_Name'] == '')
    {
      echo "Invalid Event Name entered. Name cannot be blank. <br />";
    }
    
    //Start date can't be blank on insertion, also check if it's in the correct format
    else if ($_POST['Start_Date'] == '' || !preg_match('/^\d{2}\/\d{2}\/\d{4}$/', $_POST['Start_Date'] ))
    {
      echo "Invalid start date entered. Start date cannot be blank and must be in the format \"MM/DD/YYYY\". <br />";
    }
    
    //Start time can't be blank on insertion
    else if ($_POST['Start_Time'] == '' || !preg_match('/^((0?[1-9]|1[012])(:[0-5]\d){0,2}(\ [AP]M))$|^([01]\d|2[0-3])(:[0-5]\d){0,2}$/', $_POST['Start_Time']) )
    {
      echo "Invalid start time entered. Start time cannot be blank and must be in the format \"HH:MM\" or \"HH:MM AM\" or \"HH:MM PM\". <br />";
    }
    
    //End date cant' be blank on insertion, also check if it's in the correct format
    else if ($_POST['End_Date'] == '' || !preg_match('/^\d{2}\/\d{2}\/\d{4}$/', $_POST['End_Date'] ))
    {
      echo "Invalid end date entered. End date cannot be blank and must be in the format \"MM/DD/YYYY\". <br />";
    }
    
    //End time can't be blank on insertion
    else if ($_POST['End_Time'] == '' || !preg_match('/^((0?[1-9]|1[012])(:[0-5]\d){0,2}(\ [AP]M))$|^([01]\d|2[0-3])(:[0-5]\d){0,2}$/', $_POST['End_Time']) )
    {
      echo "Invalid end time entered. End time cannot be blank and must be in the format \"HH:MM\" or \"HH:MM AM\" or \"HH:MM PM\". <br />";
    }
  
    //Class dates can't be no days selected on insertion
    else if ($Class_Days_string == '')
    {
      echo "Invalid class days selected. Must choose at least one day. <br />";
    }
  
    //Address can't be blank on insertion
    else if ($_POST['Address'] == '')
    {
      echo "Invalid address entered. Address cannot be blank. <br />";
    }
    
    //City can't be blank on insertion
    else if ($_POST['City'] == '')
    {
      echo "Invalid city entered. City cannot be blank. <br />";
    }
    
    //State can't be blank on insertion
    else if ($_POST['State'] == '')
    {
      echo "Invalid state entered. State cannot be blank. <br />";
    }
    
    //Zip can't be blank on insertion
    else if ($Zip_num == 0)
    {
      echo "Invalid zip code entered. Zip code cannot be blank and must be a number. <br />";
    }
    
    else if (($_POST['S_Type'] != '' && $Session_Length_num == 0) || ($_POST['S_Type'] == '' && $Session_Length_num != 0))
    {
      echo "Your event appears to be a screening. <br />Screening Session Length must be more than zero (0) and Screening Type must not be blank. <br />";
    }
    
  
    //Selected company is not in the datbase.
    else if( count( my_trusted_mysql_query("SELECT Email FROM COMPANY WHERE Email = '$q[Email]'") ) == 0 )
    {
      echo "The company with the e-mail " . $q['Email'] . " does not exist in the database. " .
          "To add this event's information, please insert the company first, then try again.<br /><br />";
        $_POST['Fill'] = 'true';
    }
  
    else
    {
      //Perform the insertion 
      $event_query = "";
      
      if ( $E_Type_char == 'c' )
      {
        $event_query = "INSERT INTO EVENT (Event_Name, Start_Date, End_Date, Start_Time, End_Time, Comments, E_Type) 
        VALUES ('$q[Event_Name]', '$q[Start_Date]', '$q[End_Date]', '$q[Start_Time]', '$q[End_Time]', '$q[Comments]', '$E_Type_char')";
      }
      
      else
      {
        $event_query = "INSERT INTO EVENT (Event_Name, Start_Date, End_Date, Start_Time, End_Time, Comments, E_Type, S_Type, Session_Length) 
        VALUES ('$q[Event_Name]', '$q[Start_Date]', '$q[End_Date]', '$q[Start_Time]', '$q[End_Time]', '$q[Comments]', '$E_Type_char', '$q[S_Type]', $Session_Length_num)";
      }
      
      my_trusted_mysql_query( $event_query );
      
      //Grab the last-inserted record's number
      $Previous_Insertion_Event_ID = (int)mysql_insert_id();
      
      $location_query = "INSERT INTO LOCATION (Event_ID, Location_Name, Address, City, State, Zip, Occupants)
      VALUES ($Previous_Insertion_Event_ID, '$q[Location_Name]', '$q[Address]', '$q[City]', '$q[State]', $Zip_num, $Occupants_num)";
      
      my_trusted_mysql_query( $location_query );
      
      $class_days_query = "INSERT INTO CLASS_DATES (Event_ID, Days)
      VALUES ($Previous_Insertion_Event_ID, '$Class_Days_string')";
      
      my_trusted_mysql_query( $class_days_query );
      
      $hosts_query = "INSERT INTO HOSTS (Email, Event_ID) 
      VALUES ('$q[Email]', $Previous_Insertion_Event_ID)";
      
      my_trusted_mysql_query( $hosts_query );
      
      echo "Records inserted: <br />";
      display_results(my_trusted_mysql_query( "SELECT * FROM EVENT WHERE Event_ID = $Previous_Insertion_Event_ID" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM LOCATION WHERE Event_ID = $Previous_Insertion_Event_ID" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM CLASS_DATES WHERE Event_ID = $Previous_Insertion_Event_ID" ));
      display_results(my_trusted_mysql_query( "SELECT Event_ID, Email FROM HOSTS WHERE Event_ID = $Previous_Insertion_Event_ID" ));
      
      echo "<br /> <strong>Remember this Event ID! You will need this later if you want to edit the event's information!</strong><br />";
      my_mysql_close();
      
      $_POST['Fill'] = 'false';
    }
  }

  else if ($_POST['query_type'] == 'update')
  {
    //event ID can't be blank on delete
    if ( $Event_ID_num == 0 )
    {
      echo "Invalid Event ID entered. Event ID cannot be blank and must be a number. <br />";
    }

    //Start date can't be blank on insertion, also check if it's in the correct format
    else if ($_POST['Start_Date'] != '' && !preg_match('/^\d{2}\/\d{2}\/\d{4}$/', $_POST['Start_Date'] ))
    {
      echo "Invalid start date entered. Start date cannot be blank and must be in the format \"MM/DD/YYYY\". <br />";
    }
    
    //Start time can't be blank on insertion
    else if ($_POST['Start_Time'] != '' && !preg_match('/^((0?[1-9]|1[012])(:[0-5]\d){0,2}(\ [AP]M))$|^([01]\d|2[0-3])(:[0-5]\d){0,2}$/', $_POST['Start_Time']) )
    {
      echo "Invalid start time entered. Start time cannot be blank and must be in the format \"HH:MM\" or \"HH:MM AM\" or \"HH:MM PM\". <br />";
    }
    
    //End date cant' be blank on insertion, also check if it's in the correct format
    else if ($_POST['End_Date'] != '' && !preg_match('/^\d{2}\/\d{2}\/\d{4}$/', $_POST['End_Date'] ))
    {
      echo "Invalid end date entered. End date cannot be blank and must be in the format \"MM/DD/YYYY\". <br />";
    }
    
    //End time can't be blank on insertion
    else if ($_POST['End_Time'] != '' && !preg_match('/^((0?[1-9]|1[012])(:[0-5]\d){0,2}(\ [AP]M))$|^([01]\d|2[0-3])(:[0-5]\d){0,2}$/', $_POST['End_Time']) )
    {
      echo "Invalid end time entered. End time cannot be blank and must be in the format \"HH:MM\" or \"HH:MM AM\" or \"HH:MM PM\". <br />";
    }
    
    //Event is not in the database.
    else if( count( my_trusted_mysql_query("SELECT Event_ID FROM EVENT WHERE Event_ID = $Event_ID_num") ) == 0 )
    {
      echo "The event with the ID " . $q['Event_ID'] . " does not exist in the database. " .
        "To add this event's information, please select insert instead of update.<br /><br />";
      $_POST['Fill'] = 'true';
    }  

    //If the event's a screening (or being changed to one from a class!)
    else if (($_POST['S_Type'] != '' && $Session_Length_num == 0) || ($_POST['S_Type'] == '' && $Session_Length_num != 0) )
    {
      echo "Your event appears to be a screening. <br />Screening Session Length must be more than zero (0) and Screening Type must not be blank. <br />";
    }    

    else
    {                  
      //Makes a query to only update fields that were not left blank
      $event_query  = "UPDATE EVENT SET Event_ID=$Event_ID_num";                   
      $event_query .= $q['Event_Name']       != '' ? ", Event_Name='$q[Event_Name]'"         : "";
      $event_query .= $q['Start_Date']       != '' ? ", Start_Date='$q[Start_Date]'"         : "";
      $event_query .= $q['Start_Time']       != '' ? ", Start_Time='$q[Start_Time]'"         : "";
      $event_query .= $q['End_Date']         != '' ? ", End_Date='$q[End_Date]'"             : "";
      $event_query .= $q['End_Time']         != '' ? ", End_Time='$q[End_Time]'"             : "";
      $event_query .= $q['Comments']         != '' ? ", Comments='$q[Comments]'"             : "";
      //Don't change the event type
      //$event_query .=                                ", E_Type='$E_Type_char'"                   ;
      //Only allow updating of session type and length if the event was a screening to begin with
      if ( $E_Type_char == 's' )
      {
        $event_query .= $q['S_Type']       != '' ? ", S_Type='$q[S_Type]'"                 : "";
        $event_query .=$Session_Length_num != 0  ? ", Session_Length=$Session_Length_num"  : "";
      }

      $event_query .= " WHERE Event_ID=$Event_ID_num";
      
      $location_query = "UPDATE LOCATION SET Event_ID=$Event_ID_num";
      $location_query .= $q['Location_Name'] != '' ? ", Location_Name='$q[Location_Name]'"  : "";
      $location_query .= $q['Address']       != '' ? ", Address='$q[Address]'"              : "";
      $location_query .= $q['City']          != '' ? ", City='$q[City]'"                    : "";
      $location_query .= $q['State']         != '' ? ", State='$q[State]'"                  : "";
      $location_query .= $q['Zip']           != 0  ? ", Zip=$Zip_num"                        : "";
      $location_query .= $q['Occupants']     != 0  ? ", Occupants=$Occupants_num"           : "";
      $location_query .= " WHERE Event_ID=$Event_ID_num";
      
      $class_days_query = "UPDATE CLASS_DATES SET Event_ID=$Event_ID_num";
      $class_days_query .= $Class_Days_string != '' ? ", Days='$Class_Days_string'"  : "";
      $class_days_query .= " WHERE Event_ID=$Event_ID_num";
      
      echo "Old records: <br />";
      display_results(my_trusted_mysql_query( "SELECT * FROM EVENT WHERE Event_ID = $Event_ID_num" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM LOCATION WHERE Event_ID = $Event_ID_num" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM CLASS_DATES WHERE Event_ID = $Event_ID_num" ));
    
      my_trusted_mysql_query( $event_query );
      my_trusted_mysql_query( $location_query );
      my_trusted_mysql_query( $class_days_query );      
      
      echo "<br />New updated records:";
      display_results(my_trusted_mysql_query( "SELECT * FROM EVENT WHERE Event_ID = $Event_ID_num" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM LOCATION WHERE Event_ID = $Event_ID_num" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM CLASS_DATES WHERE Event_ID = $Event_ID_num" ));

      my_mysql_close();
      
      $_POST['Fill'] = 'false';
    }
  }
  
  else if ($_POST['query_type'] == 'delete')
  {    
    //event ID can't be blank on delete
    if ( $Event_ID_num == 0 )
    {
      echo "Invalid Event ID entered. Event ID cannot be blank and must be a number. <br />";
    }
  
    //Event is not in the database.
    else if( count( my_trusted_mysql_query("SELECT Event_ID FROM EVENT WHERE Event_ID=$Event_ID_num") ) == 0 )
    {
      echo "The event with the ID " . $q['Event_ID'] . " does not exist in the database. " .
        "To add this event's information, please select insert.<br /><br />";
      $_POST['Fill'] = 'true';
    } 
  
    else
    {        
      //Show the record that's about to be deleted.
      echo "Records deleted:<br />";
      echo "Event information:<br />";
      display_results(my_trusted_mysql_query( "SELECT * FROM EVENT WHERE Event_ID = $Event_ID_num" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM LOCATION WHERE Event_ID = $Event_ID_num" ));
      display_results(my_trusted_mysql_query( "SELECT * FROM CLASS_DATES WHERE Event_ID = $Event_ID_num" ));
      echo "<br />Company's association by hosting this event:<br />";
      display_results(my_trusted_mysql_query( "SELECT * FROM COMPANY WHERE Email IN (SELECT Email FROM HOSTS WHERE Event_ID=$Event_ID_num)" ));
      //display_results(my_trusted_mysql_query( "SELECT Event_ID, Email FROM HOSTS WHERE Event_ID = $Event_ID_num" ));
      //display_results(my_trusted_mysql_query( "SELECT Event_ID, Email FROM S_ATTEND WHERE Event_ID = $Event_ID_num" ));
      //display_results(my_trusted_mysql_query( "SELECT Event_ID, Email FROM C_ATTEND WHERE Event_ID = $Event_ID_num" ));
      echo "<br />People attending this event:<br />";
      display_results(my_trusted_mysql_query(    
        "SELECT * FROM SCREEN_PARTICIPANT WHERE Email IN (SELECT Email FROM S_ATTEND WHERE Event_ID=$Event_ID_num)"
      ));
      display_results(my_trusted_mysql_query(    
        "SELECT * FROM CLASS_PARTICIPANT WHERE Email IN (SELECT Email FROM C_ATTEND WHERE Event_ID=$Event_ID_num)"
      ));
      
      my_trusted_mysql_query( "DELETE FROM EVENT WHERE Event_ID=$Event_ID_num" );
      my_trusted_mysql_query( "DELETE FROM LOCATION WHERE Event_ID=$Event_ID_num" );
      my_trusted_mysql_query( "DELETE FROM CLASS_DATES WHERE Event_ID=$Event_ID_num" );
      my_trusted_mysql_query( "DELETE FROM HOSTS WHERE Event_ID=$Event_ID_num" );
      my_trusted_mysql_query( "DELETE FROM CLASS_PARTICIPANT WHERE Email IN (SELECT Email FROM C_ATTEND WHERE Event_ID=$Event_ID_num)" );
      my_trusted_mysql_query( "DELETE FROM SCREEN_PARTICIPANT WHERE Email IN (SELECT Email FROM S_ATTEND WHERE Event_ID=$Event_ID_num)" );
      my_trusted_mysql_query( "DELETE FROM C_ATTEND WHERE Event_ID = $Event_ID_num" );
      my_trusted_mysql_query( "DELETE FROM S_ATTEND WHERE Event_ID = $Event_ID_num" );
      
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
?>
          </div>

          <div class="style35">
            <ul>
              <strong>Instructions for entering data:</strong><br />
              <li>When inserting a new event:
                <ul>
                  <li>You need to supply as much information as possible about the event.</li>
                  <li>You need to know the e-mail of the company sponsoring the event.</li>
                  <li>You do not need to supply the Event ID. One will be generated for you.</li>
                </ul>
              </li>
              <li>When updating an event's information:
                <ul>
                  <li>Make sure the event IDs match</li>
                  <li>Leave any fields you do not want to change blank.</li>
                </ul>
              </li>
               <li>When deleting an event, you need only supply the event's ID number.</li>
            </ul>
          </div>

<!-- The HTML for receiving user input from text boxes and such -->
<!-- For proper HTML rendering, the php scripts must be left completely left-aligned! -->
<form action="event_manip.php" method="POST">
<fieldset>
<legend>Select query type</legend>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="insert" checked="checked" />Insert a new event's information.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="update" />Update an already inserted event's information.<br />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<input type="radio" name="query_type" value="delete" />Delete an already inserted event's information.<br />
</fieldset>
<br />
<br />
          <table class="style26" align="center">
            <tr>
              <td class="style28">Company's E-Mail:</td>
              <td class="style27">
<input type="text" name="Email" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Email']; 
  }
?>
" /> (xyz@abc.com) 
              </td>
            </tr>
            <tr>
              <td class="style28">Event ID:</td>
              <td class="style27">
<input type="text" name="Event_ID" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Event_ID']; 
  }
?>
" /> (Only valid for update/delete)
              </td>
            </tr>
            <tr>
              <td class="style28">Event Name:</td>
              <td class="style27">
<input type="text" name="Event_Name" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Event_Name']; 
  }
?>
" />
              </td>
            </tr>
            <tr>
              <td class="style28">Location Name:</td>
              <td class="style27">
<input type="text" name="Location_Name" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Location_Name']; 
  }
?>
" />
              </td>
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
" />
              </td>
            </tr>
            <tr>
              <td class="style28">City:</td>
              <td class="style27">
<input type="text" name="City" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['City']; 
  }
?>
" />
              </td>
            </tr>
            <tr>
              <td class="style28">State:</td>
              <td class="style27">
                <select name="State">
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
                </select>  
              </td>
            </tr>
            <tr>
              <td class="style28">Zip:</td>
              <td class="style27">
<input type="text" name="Zip" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Zip']; 
  }
?>
" />
              </td>
            </tr>
            <tr>
              <td class="style36">Event Days:</td>
              <td class="style36">
                <fieldset>
                  <table border="0">
                    <tr>
                      <!--<input type="hidden" name="Class_Days[]" value="Instantiation" />-->
                      <td>
                        <input type="checkbox" name="Class_Days[]" value="Monday" />Monday
                      </td>
                      <td>
                        <input type="checkbox" name="Class_Days[]" value="Tuesday" />Tuesday 
                      </td>
                    </tr>
                    <tr>
                      <td>
                        <input type="checkbox" name="Class_Days[]" value="Wednesday" />Wednesday
                      </td>
                      <td>
                        <input type="checkbox" name="Class_Days[]" value="Thursday" />Thursday 
                      </td>
                    </tr>
                    <tr>
                      <td>
                        <input type="checkbox" name="Class_Days[]" value="Friday" />Friday
                      </td>
                      <td>
                        <input type="checkbox" name="Class_Days[]" value="Saturday" />Saturday 
                      </td>
                      <td>
                        <input type="checkbox" name="Class_Days[]" value="Sunday" />Sunday
                      </td>
                    </tr>
                  </table>
                </fieldset>
              </td>
            </tr>
            <tr>
              <td class="style28">Start Date:</td>
              <td class="style27">
<input type="text" name="Start_Date" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true')
  {
    echo $_POST['Start_Date']; 
  }
?>
" /> (MM/DD/YYYY)
              </td>
            </tr>
            <tr>
              <td class="style28">Start Time:</td>
              <td class="style27">
<input type="text" name="Start_Time" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true')
  {
    echo $_POST['Start_Time']; 
  }
?>
" /> (HH:MM [AM/PM])
              </td>
            </tr>
            <tr>
              <td class="style28">End Date:</td>
              <td class="style27"> 
<input type="text" name="End_Date" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['End_Date'];
  }
?>
" /> (MM/DD/YYYY)
              </td>
            </tr>
            <tr>
              <td class="style28">End Time:</td>
              <td class="style27"> 
<input type="text" name="End_Time" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['End_Time'];
  }
?>
" /> (HH:MM [AM/PM])
              </td>
            </tr>
            <tr>
              <td class="style28">Max. Occupants:</td>
              <td class="style27"> 
<input type="text" name="Occupants" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Occupants'];
  }
?>
" /> 
              </td>
            </tr>
            <tr>
              <td class="style36">Screening Type:</td>
              <td class="style36">
<input type="text" name="S_Type" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['S_Type'];
  }
?>
" /> (Screening only)
              </td>
            </tr>
            <tr>
              <td class="style36">Screening<br />
                  Session Length:</td>
              <td class="style36">
<input type="text" name="Session_Length" value="
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Session_Length'];
  }
?>
" /> (Minutes, screening only)
              </td>
            </tr>
            <tr>
              <td class="style36">Comments:</td>
              <td class="style36">
<textarea type="text" rows="3" cols="40" name="Comments">
<?php 
  if (isset($_POST['submit']) && $_POST['Fill'] == 'true') 
  {
    echo $_POST['Comments'];
  }
?></textarea>
              </td>
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