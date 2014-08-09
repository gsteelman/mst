<?php include 'sessionHandler.php'; ?>

<head>
  <title>Find New Games</title>
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
                      &nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Find New Games</span>
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
                        if ( isset($_SESSION["AcctNumber"]) )
                        {
                        
                          $headerarray = array();
	                        $headerarray[0] = "Popular Games You'll Love";
	                        $headerarray[1] = "Niche Games You'll Love";
	                        $headerarray[2] = "Games That Will Tell Us The Most About You";
                          
                          $cmd        = "";
                          $storageLoc = ".";
                          $username   = $_SESSION["username"];
                          $mystring   = "starFox64 | redFaction | bit.TripRunner || diablo2 | granTurismo4 || dukeNukem3D | doom";
  
                          // "0, <username>, <results storage location>"
                          
                          $cmd = "0 $username \"$storageLoc\" \"$mystring\"";

                          $output = shell_exec( "java -Xmx100M -Xms100M -jar GameWarp.jar $cmd" );

                          echo "<span class=\"subheader\">$username, your games await...</span><br /><br />";
                          echo $output;


                          $myFile = "$username.txt";
                          $fh = fopen($myFile, 'r');
                          $theData = fread($fh, filesize($myFile));
                          fclose($fh);
                         
                         $keywords = preg_split("/[|]{2,2}/", $theData);                        
                         
                         $i = 0;
                         foreach ($keywords as $value)
                         {
                          $keywords2 = preg_split("/[|]/", $value);
                          
                          echo "<table border = \"1\" align= \"center\" width = \"75%\" bgcolor = \"black\">
                          <tr><th  bgcolor=\"#AAAAAA\"><span class=\"subheader\">"; 
                          echo "$headerarray[$i]";
                          echo "</span></th></tr>";
                          foreach ($keywords2 as $value2)
                          {
                            echo "<tr align = \"center\">";
                            echo "<td><span class=\"flashresult\"><a TARGET = \"_blank\" href=\"http://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Dvideogames&field-keywords=$value2&x=0&y=0\">$value2</a></span></td>";
                            echo"</tr>";
                          }
                          echo "</table><br>";
                          $i++;
                         }
                         //echo "<br> Original: $theData <br>";
                         //print_r( $keywords );        
                        
                        }
                        else
                        {
                          echo "<span class=\"sysnotes\">You must log in to find new games!</span> <br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br /><br />";
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
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>