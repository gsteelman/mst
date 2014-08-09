<?php include 'sessionHandler.php'; ?>

<head>
  <title>Rate A Game</title>
  <?php include'style.html'; ?>
</head>
<body bgcolor="Black">
    <SPAN style="FONT-FAMILY: Arial">
        <table width="900" align="center" border="0" cellpadding="0" cellspacing="0">
            <?php include'menu.php'; ?>
                <tr><td><table width="100%" background="bg.jpg" background-attachment="fixed">
                    <tr><td width="5"></td><td>&nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Rate A Game</span></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td><hr width="100%" /></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>
                      <?php
                      include "includes/functions.php";
                      
                        if ( isset($_SESSION["AcctNumber"]) )
                        {
                          
                          //Query the database for a list of games in the system that they can rate.
                          $sql = "SELECT GameURI FROM GameList";
                          
                          // connect to the database
                          my_mysql_connect();
                          
                          $result = mysql_query($sql);
                                                  
                          echo "
                          <span class=\"subheader\">Fill in the three fields below to rate a game:</span> <br /><br />
                          <form name=\"form1\" method=\"post\" action=\"rate.php\">
                          <table width=\"50%\" border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
                          <tr>
                          <td>GameURI:</td>
                          <td>
                          <SELECT id=txtGameURI size=1 name=gameuri>
                            <OPTION value=\"\"></OPTION>
                          ";
                                                    
                              while($row = mysql_fetch_array($result))
                              {
                                $val = $row["GameURI"];
                              
                              echo "<OPTION value=$val>$val</OPTION>";
                              }
                          echo "
                          </SELECT>
                          </td>
                          </tr>
                          <tr>
                          <td>Score:</td>
                          <td>
                          <SELECT id=txtScore size=1 name=score>
                              <OPTION value=\"\"></OPTION>
                              <OPTION value=1>1</OPTION>
                              <OPTION value=2>2</OPTION>
                              <OPTION value=3>3</OPTION>
                              <OPTION value=4>4</OPTION>
                              <OPTION value=5>5</OPTION>
                              <OPTION value=6>6</OPTION>
                              <OPTION value=7>7</OPTION>
                              <OPTION value=8>8</OPTION>
                              <OPTION value=9>9</OPTION>
                              <OPTION value=10>10</OPTION>
                          </SELECT>
                          </td>
                          </tr>
                          <tr>
                          <td>Comment:</td>
                          <td><textarea id=txtRequest name=\"comment\" rows=5 cols=35></textarea></td>
                          </tr>
                          <tr>
                          <td></td>
                          <td align=\"left\"><input type=\"submit\" value=\"Rate Game\"/></td>
                          </tr>
                          </table>
					                </form>
                          ";
                          
                          my_mysql_close();
                          
                        }
                        else
                        {
                          echo "<span class=\"sysnotes\">You must log in to rate games!</span> <br />";
                        }
                      ?>
                    </td><td width="5"></td></tr>
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
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>