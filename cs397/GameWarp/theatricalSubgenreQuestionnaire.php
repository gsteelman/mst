<?php include 'sessionHandler.php'; ?>

<head>
  <title>Theatrical Subgenre Questionnaire</title>
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
                      &nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Theatrical Subgenre Questionnaire</span>
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
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>
                      <form name="Q1" method="post" action="theatricalSubgenreQuestionnaireSubmit.php">
                      <table width="85%" border="1" bgcolor="White" align="center">
                        <tr>
                          <td colspan="2"><b>For the following questions, please indicate how much you like games of the genre. A '1' indicates disdain; a '10' indicates undying love.</b></td>
                        </tr>
                          <tr>
                          <td>
                           World War Two
                          </td>
                          <td>
                           <input type="radio" name="WorldWarTwo" value="1"> 1 - Hate them <br />
                           <input type="radio" name="WorldWarTwo" value="2"> 2 <br />
                           <input type="radio" name="WorldWarTwo" value="3"> 3 <br />
                           <input type="radio" name="WorldWarTwo" value="4"> 4 <br />
                           <input type="radio" name="WorldWarTwo" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="WorldWarTwo" value="6"> 6 <br />
                           <input type="radio" name="WorldWarTwo" value="7"> 7 <br />
                           <input type="radio" name="WorldWarTwo" value="8"> 8 <br />
                           <input type="radio" name="WorldWarTwo" value="9"> 9 <br />
                           <input type="radio" name="WorldWarTwo" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Post-Apocalyptic
                          </td>
                          <td>
                           <input type="radio" name="PostApocalyptic" value="1"> 1 - Hate them <br />
                           <input type="radio" name="PostApocalyptic" value="2"> 2 <br />
                           <input type="radio" name="PostApocalyptic" value="3"> 3 <br />
                           <input type="radio" name="PostApocalyptic" value="4"> 4 <br />
                           <input type="radio" name="PostApocalyptic" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="PostApocalyptic" value="6"> 6 <br />
                           <input type="radio" name="PostApocalyptic" value="7"> 7 <br />
                           <input type="radio" name="PostApocalyptic" value="8"> 8 <br />
                           <input type="radio" name="PostApocalyptic" value="9"> 9 <br />
                           <input type="radio" name="PostApocalyptic" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td colspan="2"><input type="submit" value="Submit"/></td>
                        </tr>
                      </table>
                      </form>
                    </td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>