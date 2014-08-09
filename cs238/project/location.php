//Start of copied code from company_insert.php
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
                  <script language="JavaScript" img="" src="includes/functions.js"></script>

                  <body>

                    <style type="text/css">
                      <!--
    .style21
    {
        color: #000000;
        width: 756px;
        }
    .style25
    {
        font: Arial;
    }
    .style26
    {
        width: 100%;
    }
    .style27
    {
        height: 23px;
    }
    .style28
    {
        height: 23px;
        width: 238px;
        text-align: right;
    }
    .style29
    {
        width: 238px;
    }
    .style30
    {
        width: 238px;
        text-align: right;
    }
    .style31
    {
        color: #000000;
    }
    .style33
    {
        color: #808080;
        font-family: Sylfaen;
    }
-->
                    </style>
                    <table width="100%" height="100%"  border="0" cellpadding="0" cellspacing="0">
                      <tr>
                        <td background="back.gif">
                          <table width="800" border="0" align="center" cellpadding="0" cellspacing="0" bgcolor="#CCCCCC" style="border:1 solid #790000;">
                            <tr>
                              <td colspan="2">
                                <div align="left" style="background-color: #1195F0">
                                  <img src="header-1.jpg" width="760" height="136">
                                </div>
                              </td>
                            </tr>
                            <tr>
                              <td align="left" valign="top"
                                    style="background-color: #FFFFFF" class="style25">
                                <table align="left" border="0" cellpadding="0" cellspacing="0" width="152">
                                  <tr>
                                    <td width="152">
                                      <table width="152" border="0" align="left" cellpadding="0" cellspacing="0" bgcolor="#999999">
                                        <tr>
                                          <td width="152">
                                            <div align="left">
                                              <img src="left_bar-1.jpg" width="152" height="436">
                                            </div>
                                          </td>
                                        </tr>
                                      </table>
                                    </td>
                                  </tr>

                                </table>
                              </td>
                              <td align="center" style="background-color: #FFFFFF; font-family: Sylfaen;"
                                    class="style21">

                                <span class="style31">
                                  Company added:
                                </span>
                                
                                <?php
                                //End of copied code from company_insert.php
/**
 * file: location.php
 * brief: contains functionality for inserting, deleting, and modifing a location
 */                                
 
include "includes/functions.php";
include "includes/config.php";

//Connect to the data base
$con =my_mysql_connect();
if(!$con)
{
  die('Could not connect: ', . mysql_error());
}
//Preform the given action (Modify, Insert, or Delete) depending on $_POST[Action]
switch ($_POST[Action])
{
  case Modify:
    //Modify the existing data by first removing the tuple with the given Event_ID, Address, City, State, and Zip then inserting a new one with the same Primay keys
    //This means that inorder to update the user must enter in all data, not just the modified data
    my_trusted_mysql_query( "DELETE FROM LOCATION WHERE Event_ID ='$_POST[Event_ID] AND Address='$_POST[Address] AND City='$_POST[City] AND State='$_POST[State] AND Zip='$_POST[Zip]");
    
    //No break it continues into insert
  case Insert:
    //Create the insert into Location query (Entity)
    $query_location= "INSERT INTO LOCATION (Event_ID, Address, City, State, Zip, Occupants, Location_Name)
    VALUES ('$_POST[Event_ID]', '$_POST[Address]', '$_POST[City]' ,'$_POST[State]', '$_POST[Zip]', '$_POST[Occupants]', '$_POST[Location_Name]'";
    
    //Create the insert into Held_in query (Relation)
    $query_held_in = "INSERT INTO HOSTS (Event_ID, Address)
    VALUES ('$_POST[Event_ID]', '$_POST[Address]')";
                                  
    //Perform the insertions
    my_trusted_mysql_query( $query_location );
    my_trusted_mysql_query( $query_held_in );
    
    break;
  case Delete:
    // Deletes the tuple in EVENT with the given Event_ID
    // The data base should be set up to delete on cascade of foreign key in the database itself
    my_trusted_mysql_query( "DELETE FROM LOCATION WHERE Event_ID ='$_POST[Event_ID] AND Address = '$_POST[Address]");
    
    break;
}

//Display current items in database in a table
echo "<table border='1'>
<tr>
<th>Event ID</th>
<th>Address</th>
<th>City</th>
<th>State</th>
<th>Zip</th>
<th>Occupants</th>
<th>Location Name</th>
<th></th>
</tr>";

$result = my_trusted_mysql_query( "SELECT * FROM EVENT");
while($row = mysql_fetch_arry($result))
{
  echo "<tr>";
  echo "<td>"; . $row['Event_ID'] . "</td>";
  echo "<td>"; . $row['Address'] . "</td>";
  echo "<td>"; . $row['City'] . "</td>";
  echo "<td>"; . $row['State'] . "</td>";
  echo "<td>"; . $row['Zip'] . "</td>";
  echo "<td>"; . $row['Occupants'] . "</td>";
  echo "<td>"; . $row['Location_Name'] . "</td>";
}
echo "</table>";

//close connection
mysql_close(&con);


                                   
                               //Start of copied code from company_insert.php
                                ?> 
                                
                              </td>
                            </tr>
                            <tr>
                              <td colspan="2">
                                <table align="left" border="1" cellpadding="0" cellspacing="0" width="100%">
                                  <tr>
                                    <td height="38" background="/images/index_r17_c9.jpg" class="style21">
                                      <div align="center">
                                        <span class="style33">
                                          Patents and Copyrights owned by Maelstrom,
                                          Not for use by others.
                                        </span>
                                        <br>
        
                                      </div>
                                    </td>
                                  </tr>
                                </table>
                              </td>
                            </tr>
                          </table>
                        </td>
                      </tr>
                    </table>
