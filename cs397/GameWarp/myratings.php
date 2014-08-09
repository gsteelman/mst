<?php include 'sessionHandler.php'; ?>

<head>
  <title>My Ratings</title>
  <?php include'style.html'; ?>
</head>
<body bgcolor="Black">
    <SPAN style="FONT-FAMILY: Arial">
        <table width="900" align="center" border="0" cellpadding="0" cellspacing="0">
            <?php include'menu.php'; ?>
                <tr><td><table width="100%" background="bg.jpg" background-attachment="fixed">
                  <tr>
                    <td width="5"></td>
                    <td>
                      &nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">My Ratings</span>
                    </td>
                    <td width="5"></td>
                  </tr>
                  <tr>
                    <td width="5"></td>
                    <td>
                      <hr width="100%" />
                    </td>
                    <td width="5"></td>
                  </tr>
                    <tr><td width="5"></td><td>
                      <?php
                        include "includes/functions.php";
                        
                        if ( isset($_SESSION["AcctNumber"]) )
                        {
                          
                          // connect to the database
                          my_mysql_connect();
                          
                          $accntnum = $_SESSION["AcctNumber"];
                          
                          $result = mysql_query("SELECT GameURI, Rating, Comment FROM UserGameRatings WHERE AccountNumber = '$accntnum'");
                                                    
                          echo "<table border = \"1\" align= \"center\" width = \"90%\" bgcolor = \"White\">
                          <tr>
                            <th>Game</th>
                            <th>Your Rating</th>
                            <th>Your Comment</th>
                          </tr>
                          ";
                          while($row = mysql_fetch_array($result))
                          {
                          echo "<tr>";
                          echo "<td>" . $row["GameURI"] . "</td>";
                          echo "<td>" . $row["Rating"] . "</td>";
                          echo "<td>" . $row["Comment"] . "</td>";
                          echo "</tr>";
                          }
                          echo "</table>";
                          
                          my_mysql_close();
                          
                        }
                        else
                        {
                          echo "<span class=\"sysnotes\">You must log in to see your previous ratings!</span> <br /><br /><br /><br /><br /><br /><br /><br /><br />";
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
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>