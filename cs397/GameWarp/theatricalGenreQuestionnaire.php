<?php include 'sessionHandler.php'; ?>

<head>
  <title>Theatrical Genre Questionnaire</title>
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
                      &nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Theatrical Genre Questionnaire</span>
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
                      <form name="Q1" method="post" action="theatricalGenreQuestionnaireSubmit.php">
                      <table width="85%" border="1" bgcolor="White" align="center">
                        <tr>
                          <td colspan="2"><b>For the following questions, please indicate how much you like games of the genre. A '1' indicates disdain; a '10' indicates undying love.</b></td>
                        </tr>
                          <tr>
                          <td>
                           Action
                          </td>
                          <td>
                           <input type="radio" name="Action" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Action" value="2"> 2 <br />
                           <input type="radio" name="Action" value="3"> 3 <br />
                           <input type="radio" name="Action" value="4"> 4 <br />
                           <input type="radio" name="Action" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Action" value="6"> 6 <br />
                           <input type="radio" name="Action" value="7"> 7 <br />
                           <input type="radio" name="Action" value="8"> 8 <br />
                           <input type="radio" name="Action" value="9"> 9 <br />
                           <input type="radio" name="Action" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Adventure
                          </td>
                          <td>
                           <input type="radio" name="Adventure" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Adventure" value="2"> 2 <br />
                           <input type="radio" name="Adventure" value="3"> 3 <br />
                           <input type="radio" name="Adventure" value="4"> 4 <br />
                           <input type="radio" name="Adventure" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Adventure" value="6"> 6 <br />
                           <input type="radio" name="Adventure" value="7"> 7 <br />
                           <input type="radio" name="Adventure" value="8"> 8 <br />
                           <input type="radio" name="Adventure" value="9"> 9 <br />
                           <input type="radio" name="Adventure" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Comedy
                          </td>
                          <td>
                           <input type="radio" name="Comedy" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Comedy" value="2"> 2 <br />
                           <input type="radio" name="Comedy" value="3"> 3 <br />
                           <input type="radio" name="Comedy" value="4"> 4 <br />
                           <input type="radio" name="Comedy" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Comedy" value="6"> 6 <br />
                           <input type="radio" name="Comedy" value="7"> 7 <br />
                           <input type="radio" name="Comedy" value="8"> 8 <br />
                           <input type="radio" name="Comedy" value="9"> 9 <br />
                           <input type="radio" name="Comedy" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Crime / Gangsters
                          </td>
                          <td>
                           <input type="radio" name="CrimeAndGangster" value="1"> 1 - Hate them <br />
                           <input type="radio" name="CrimeAndGangster" value="2"> 2 <br />
                           <input type="radio" name="CrimeAndGangster" value="3"> 3 <br />
                           <input type="radio" name="CrimeAndGangster" value="4"> 4 <br />
                           <input type="radio" name="CrimeAndGangster" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="CrimeAndGangster" value="6"> 6 <br />
                           <input type="radio" name="CrimeAndGangster" value="7"> 7 <br />
                           <input type="radio" name="CrimeAndGangster" value="8"> 8 <br />
                           <input type="radio" name="CrimeAndGangster" value="9"> 9 <br />
                           <input type="radio" name="CrimeAndGangster" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Drama
                          </td>
                          <td>
                           <input type="radio" name="Drama" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Drama" value="2"> 2 <br />
                           <input type="radio" name="Drama" value="3"> 3 <br />
                           <input type="radio" name="Drama" value="4"> 4 <br />
                           <input type="radio" name="Drama" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Drama" value="6"> 6 <br />
                           <input type="radio" name="Drama" value="7"> 7 <br />
                           <input type="radio" name="Drama" value="8"> 8 <br />
                           <input type="radio" name="Drama" value="9"> 9 <br />
                           <input type="radio" name="Drama" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Epics / Historical
                          </td>
                          <td>
                           <input type="radio" name="EpicsAndHistorical" value="1"> 1 - Hate them <br />
                           <input type="radio" name="EpicsAndHistorical" value="2"> 2 <br />
                           <input type="radio" name="EpicsAndHistorical" value="3"> 3 <br />
                           <input type="radio" name="EpicsAndHistorical" value="4"> 4 <br />
                           <input type="radio" name="EpicsAndHistorical" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="EpicsAndHistorical" value="6"> 6 <br />
                           <input type="radio" name="EpicsAndHistorical" value="7"> 7 <br />
                           <input type="radio" name="EpicsAndHistorical" value="8"> 8 <br />
                           <input type="radio" name="EpicsAndHistorical" value="9"> 9 <br />
                           <input type="radio" name="EpicsAndHistorical" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Fantasy
                          </td>
                          <td>
                           <input type="radio" name="Fantasy" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Fantasy" value="2"> 2 <br />
                           <input type="radio" name="Fantasy" value="3"> 3 <br />
                           <input type="radio" name="Fantasy" value="4"> 4 <br />
                           <input type="radio" name="Fantasy" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Fantasy" value="6"> 6 <br />
                           <input type="radio" name="Fantasy" value="7"> 7 <br />
                           <input type="radio" name="Fantasy" value="8"> 8 <br />
                           <input type="radio" name="Fantasy" value="9"> 9 <br />
                           <input type="radio" name="Fantasy" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Horror
                          </td>
                          <td>
                           <input type="radio" name="Horror" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Horror" value="2"> 2 <br />
                           <input type="radio" name="Horror" value="3"> 3 <br />
                           <input type="radio" name="Horror" value="4"> 4 <br />
                           <input type="radio" name="Horror" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Horror" value="6"> 6 <br />
                           <input type="radio" name="Horror" value="7"> 7 <br />
                           <input type="radio" name="Horror" value="8"> 8 <br />
                           <input type="radio" name="Horror" value="9"> 9 <br />
                           <input type="radio" name="Horror" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Musicials / Dancing
                          </td>
                          <td>
                           <input type="radio" name="MusicAndDancing" value="1"> 1 - Hate them <br />
                           <input type="radio" name="MusicAndDancing" value="2"> 2 <br />
                           <input type="radio" name="MusicAndDancing" value="3"> 3 <br />
                           <input type="radio" name="MusicAndDancing" value="4"> 4 <br />
                           <input type="radio" name="MusicAndDancing" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="MusicAndDancing" value="6"> 6 <br />
                           <input type="radio" name="MusicAndDancing" value="7"> 7 <br />
                           <input type="radio" name="MusicAndDancing" value="8"> 8 <br />
                           <input type="radio" name="MusicAndDancing" value="9"> 9 <br />
                           <input type="radio" name="MusicAndDancing" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Mystery
                          </td>
                          <td>
                           <input type="radio" name="Mystery" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Mystery" value="2"> 2 <br />
                           <input type="radio" name="Mystery" value="3"> 3 <br />
                           <input type="radio" name="Mystery" value="4"> 4 <br />
                           <input type="radio" name="Mystery" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Mystery" value="6"> 6 <br />
                           <input type="radio" name="Mystery" value="7"> 7 <br />
                           <input type="radio" name="Mystery" value="8"> 8 <br />
                           <input type="radio" name="Mystery" value="9"> 9 <br />
                           <input type="radio" name="Mystery" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Science Fiction
                          </td>
                          <td>
                           <input type="radio" name="ScienceFiction" value="1"> 1 - Hate them <br />
                           <input type="radio" name="ScienceFiction" value="2"> 2 <br />
                           <input type="radio" name="ScienceFiction" value="3"> 3 <br />
                           <input type="radio" name="ScienceFiction" value="4"> 4 <br />
                           <input type="radio" name="ScienceFiction" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="ScienceFiction" value="6"> 6 <br />
                           <input type="radio" name="ScienceFiction" value="7"> 7 <br />
                           <input type="radio" name="ScienceFiction" value="8"> 8 <br />
                           <input type="radio" name="ScienceFiction" value="9"> 9 <br />
                           <input type="radio" name="ScienceFiction" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            War
                          </td>
                          <td>
                           <input type="radio" name="War" value="1"> 1 - Hate them <br />
                           <input type="radio" name="War" value="2"> 2 <br />
                           <input type="radio" name="War" value="3"> 3 <br />
                           <input type="radio" name="War" value="4"> 4 <br />
                           <input type="radio" name="War" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="War" value="6"> 6 <br />
                           <input type="radio" name="War" value="7"> 7 <br />
                           <input type="radio" name="War" value="8"> 8 <br />
                           <input type="radio" name="War" value="9"> 9 <br />
                           <input type="radio" name="War" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Western
                          </td>
                          <td>
                           <input type="radio" name="Western" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Western" value="2"> 2 <br />
                           <input type="radio" name="Western" value="3"> 3 <br />
                           <input type="radio" name="Western" value="4"> 4 <br />
                           <input type="radio" name="Western" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Western" value="6"> 6 <br />
                           <input type="radio" name="Western" value="7"> 7 <br />
                           <input type="radio" name="Western" value="8"> 8 <br />
                           <input type="radio" name="Western" value="9"> 9 <br />
                           <input type="radio" name="Western" value="10"> 10 - Love 'em! <br />
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