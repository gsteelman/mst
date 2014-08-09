<?php include 'sessionHandler.php'; ?>

<head>
  <title>Game Genre Questionnaire</title>
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
                      &nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Game Genre Questionnaire</span>
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
                      <form name="Q1" method="post" action="gameGenreQuestionnaireSubmit.php">
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
                            Action-Adventure
                          </td>
                          <td>
                           <input type="radio" name="ActionAdventure" value="1"> 1 - Hate them <br />
                           <input type="radio" name="ActionAdventure" value="2"> 2 <br />
                           <input type="radio" name="ActionAdventure" value="3"> 3 <br />
                           <input type="radio" name="ActionAdventure" value="4"> 4 <br />
                           <input type="radio" name="ActionAdventure" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="ActionAdventure" value="6"> 6 <br />
                           <input type="radio" name="ActionAdventure" value="7"> 7 <br />
                           <input type="radio" name="ActionAdventure" value="8"> 8 <br />
                           <input type="radio" name="ActionAdventure" value="9"> 9 <br />
                           <input type="radio" name="ActionAdventure" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Driving
                          </td>
                          <td>
                           <input type="radio" name="Driving" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Driving" value="2"> 2 <br />
                           <input type="radio" name="Driving" value="3"> 3 <br />
                           <input type="radio" name="Driving" value="4"> 4 <br />
                           <input type="radio" name="Driving" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Driving" value="6"> 6 <br />
                           <input type="radio" name="Driving" value="7"> 7 <br />
                           <input type="radio" name="Driving" value="8"> 8 <br />
                           <input type="radio" name="Driving" value="9"> 9 <br />
                           <input type="radio" name="Driving" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Role Playing Games
                          </td>
                          <td>
                           <input type="radio" name="RolePlaying" value="1"> 1 - Hate them <br />
                           <input type="radio" name="RolePlaying" value="2"> 2 <br />
                           <input type="radio" name="RolePlaying" value="3"> 3 <br />
                           <input type="radio" name="RolePlaying" value="4"> 4 <br />
                           <input type="radio" name="RolePlaying" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="RolePlaying" value="6"> 6 <br />
                           <input type="radio" name="RolePlaying" value="7"> 7 <br />
                           <input type="radio" name="RolePlaying" value="8"> 8 <br />
                           <input type="radio" name="RolePlaying" value="9"> 9 <br />
                           <input type="radio" name="RolePlaying" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Simulation
                          </td>
                          <td>
                           <input type="radio" name="Simulation" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Simulation" value="2"> 2 <br />
                           <input type="radio" name="Simulation" value="3"> 3 <br />
                           <input type="radio" name="Simulation" value="4"> 4 <br />
                           <input type="radio" name="Simulation" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Simulation" value="6"> 6 <br />
                           <input type="radio" name="Simulation" value="7"> 7 <br />
                           <input type="radio" name="Simulation" value="8"> 8 <br />
                           <input type="radio" name="Simulation" value="9"> 9 <br />
                           <input type="radio" name="Simulation" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Sports
                          </td>
                          <td>
                           <input type="radio" name="Sport" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Sport" value="2"> 2 <br />
                           <input type="radio" name="Sport" value="3"> 3 <br />
                           <input type="radio" name="Sport" value="4"> 4 <br />
                           <input type="radio" name="Sport" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Sport" value="6"> 6 <br />
                           <input type="radio" name="Sport" value="7"> 7 <br />
                           <input type="radio" name="Sport" value="8"> 8 <br />
                           <input type="radio" name="Sport" value="9"> 9 <br />
                           <input type="radio" name="Sport" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Strategy
                          </td>
                          <td>
                           <input type="radio" name="Strategy" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Strategy" value="2"> 2 <br />
                           <input type="radio" name="Strategy" value="3"> 3 <br />
                           <input type="radio" name="Strategy" value="4"> 4 <br />
                           <input type="radio" name="Strategy" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Strategy" value="6"> 6 <br />
                           <input type="radio" name="Strategy" value="7"> 7 <br />
                           <input type="radio" name="Strategy" value="8"> 8 <br />
                           <input type="radio" name="Strategy" value="9"> 9 <br />
                           <input type="radio" name="Strategy" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Puzzle
                          </td>
                          <td>
                           <input type="radio" name="Puzzle" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Puzzle" value="2"> 2 <br />
                           <input type="radio" name="Puzzle" value="3"> 3 <br />
                           <input type="radio" name="Puzzle" value="4"> 4 <br />
                           <input type="radio" name="Puzzle" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Puzzle" value="6"> 6 <br />
                           <input type="radio" name="Puzzle" value="7"> 7 <br />
                           <input type="radio" name="Puzzle" value="8"> 8 <br />
                           <input type="radio" name="Puzzle" value="9"> 9 <br />
                           <input type="radio" name="Puzzle" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Shooter
                          </td>
                          <td>
                           <input type="radio" name="Shooter" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Shooter" value="2"> 2 <br />
                           <input type="radio" name="Shooter" value="3"> 3 <br />
                           <input type="radio" name="Shooter" value="4"> 4 <br />
                           <input type="radio" name="Shooter" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Shooter" value="6"> 6 <br />
                           <input type="radio" name="Shooter" value="7"> 7 <br />
                           <input type="radio" name="Shooter" value="8"> 8 <br />
                           <input type="radio" name="Shooter" value="9"> 9 <br />
                           <input type="radio" name="Shooter" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Rhythm
                          </td>
                          <td>
                           <input type="radio" name="Rhythm" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Rhythm" value="2"> 2 <br />
                           <input type="radio" name="Rhythm" value="3"> 3 <br />
                           <input type="radio" name="Rhythm" value="4"> 4 <br />
                           <input type="radio" name="Rhythm" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Rhythm" value="6"> 6 <br />
                           <input type="radio" name="Rhythm" value="7"> 7 <br />
                           <input type="radio" name="Rhythm" value="8"> 8 <br />
                           <input type="radio" name="Rhythm" value="9"> 9 <br />
                           <input type="radio" name="Rhythm" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Party
                          </td>
                          <td>
                           <input type="radio" name="Party" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Party" value="2"> 2 <br />
                           <input type="radio" name="Party" value="3"> 3 <br />
                           <input type="radio" name="Party" value="4"> 4 <br />
                           <input type="radio" name="Party" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Party" value="6"> 6 <br />
                           <input type="radio" name="Party" value="7"> 7 <br />
                           <input type="radio" name="Party" value="8"> 8 <br />
                           <input type="radio" name="Party" value="9"> 9 <br />
                           <input type="radio" name="Party" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Platformer
                          </td>
                          <td>
                           <input type="radio" name="Platformer" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Platformer" value="2"> 2 <br />
                           <input type="radio" name="Platformer" value="3"> 3 <br />
                           <input type="radio" name="Platformer" value="4"> 4 <br />
                           <input type="radio" name="Platformer" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Platformer" value="6"> 6 <br />
                           <input type="radio" name="Platformer" value="7"> 7 <br />
                           <input type="radio" name="Platformer" value="8"> 8 <br />
                           <input type="radio" name="Platformer" value="9"> 9 <br />
                           <input type="radio" name="Platformer" value="10"> 10 - Love 'em! <br />
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