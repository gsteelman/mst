<?php include 'sessionHandler.php'; ?>

<head>
  <title>Game Subgenre Questionnaire</title>
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
                      &nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Game Subgenre Questionnaire</span>
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
                      <form name="Q1" method="post" action="gameSubgenreQuestionnaireSubmit.php">
                      <table width="85%" border="1" bgcolor="White" align="center">
                        <tr>
                          <td colspan="2"><b>For the following questions, please indicate how much you like games of the subgenre indicated. A '1' indicates disdain; a '10' indicates undying love.</b></td>
                        </tr>
                          <tr>
                          <td>
                           Fighting
                          </td>
                          <td>
                           <input type="radio" name="Fighting" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Fighting" value="2"> 2 <br />
                           <input type="radio" name="Fighting" value="3"> 3 <br />
                           <input type="radio" name="Fighting" value="4"> 4 <br />
                           <input type="radio" name="Fighting" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Fighting" value="6"> 6 <br />
                           <input type="radio" name="Fighting" value="7"> 7 <br />
                           <input type="radio" name="Fighting" value="8"> 8 <br />
                           <input type="radio" name="Fighting" value="9"> 9 <br />
                           <input type="radio" name="Fighting" value="10"> 10 - Love 'em! <br />
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
                            Western RPGs
                          </td>
                          <td>
                           <input type="radio" name="WRPG" value="1"> 1 - Hate them <br />
                           <input type="radio" name="WRPG" value="2"> 2 <br />
                           <input type="radio" name="WRPG" value="3"> 3 <br />
                           <input type="radio" name="WRPG" value="4"> 4 <br />
                           <input type="radio" name="WRPG" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="WRPG" value="6"> 6 <br />
                           <input type="radio" name="WRPG" value="7"> 7 <br />
                           <input type="radio" name="WRPG" value="8"> 8 <br />
                           <input type="radio" name="WRPG" value="9"> 9 <br />
                           <input type="radio" name="WRPG" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Japanese RPG
                          </td>
                          <td>
                           <input type="radio" name="JRPG" value="1"> 1 - Hate them <br />
                           <input type="radio" name="JRPG" value="2"> 2 <br />
                           <input type="radio" name="JRPG" value="3"> 3 <br />
                           <input type="radio" name="JRPG" value="4"> 4 <br />
                           <input type="radio" name="JRPG" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="JRPG" value="6"> 6 <br />
                           <input type="radio" name="JRPG" value="7"> 7 <br />
                           <input type="radio" name="JRPG" value="8"> 8 <br />
                           <input type="radio" name="JRPG" value="9"> 9 <br />
                           <input type="radio" name="JRPG" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Baseball
                          </td>
                          <td>
                           <input type="radio" name="Baseball" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Baseball" value="2"> 2 <br />
                           <input type="radio" name="Baseball" value="3"> 3 <br />
                           <input type="radio" name="Baseball" value="4"> 4 <br />
                           <input type="radio" name="Baseball" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Baseball" value="6"> 6 <br />
                           <input type="radio" name="Baseball" value="7"> 7 <br />
                           <input type="radio" name="Baseball" value="8"> 8 <br />
                           <input type="radio" name="Baseball" value="9"> 9 <br />
                           <input type="radio" name="Baseball" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Basketball
                          </td>
                          <td>
                           <input type="radio" name="Basketball" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Basketball" value="2"> 2 <br />
                           <input type="radio" name="Basketball" value="3"> 3 <br />
                           <input type="radio" name="Basketball" value="4"> 4 <br />
                           <input type="radio" name="Basketball" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Basketball" value="6"> 6 <br />
                           <input type="radio" name="Basketball" value="7"> 7 <br />
                           <input type="radio" name="Basketball" value="8"> 8 <br />
                           <input type="radio" name="Basketball" value="9"> 9 <br />
                           <input type="radio" name="Basketball" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Golf
                          </td>
                          <td>
                           <input type="radio" name="Golf" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Golf" value="2"> 2 <br />
                           <input type="radio" name="Golf" value="3"> 3 <br />
                           <input type="radio" name="Golf" value="4"> 4 <br />
                           <input type="radio" name="Golf" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Golf" value="6"> 6 <br />
                           <input type="radio" name="Golf" value="7"> 7 <br />
                           <input type="radio" name="Golf" value="8"> 8 <br />
                           <input type="radio" name="Golf" value="9"> 9 <br />
                           <input type="radio" name="Golf" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Boxing
                          </td>
                          <td>
                           <input type="radio" name="Boxing" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Boxing" value="2"> 2 <br />
                           <input type="radio" name="Boxing" value="3"> 3 <br />
                           <input type="radio" name="Boxing" value="4"> 4 <br />
                           <input type="radio" name="Boxing" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Boxing" value="6"> 6 <br />
                           <input type="radio" name="Boxing" value="7"> 7 <br />
                           <input type="radio" name="Boxing" value="8"> 8 <br />
                           <input type="radio" name="Boxing" value="9"> 9 <br />
                           <input type="radio" name="Boxing" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            MMA
                          </td>
                          <td>
                           <input type="radio" name="MMA" value="1"> 1 - Hate them <br />
                           <input type="radio" name="MMA" value="2"> 2 <br />
                           <input type="radio" name="MMA" value="3"> 3 <br />
                           <input type="radio" name="MMA" value="4"> 4 <br />
                           <input type="radio" name="MMA" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="MMA" value="6"> 6 <br />
                           <input type="radio" name="MMA" value="7"> 7 <br />
                           <input type="radio" name="MMA" value="8"> 8 <br />
                           <input type="radio" name="MMA" value="9"> 9 <br />
                           <input type="radio" name="MMA" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Wrestling
                          </td>
                          <td>
                           <input type="radio" name="Wrestling" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Wrestling" value="2"> 2 <br />
                           <input type="radio" name="Wrestling" value="3"> 3 <br />
                           <input type="radio" name="Wrestling" value="4"> 4 <br />
                           <input type="radio" name="Wrestling" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Wrestling" value="6"> 6 <br />
                           <input type="radio" name="Wrestling" value="7"> 7 <br />
                           <input type="radio" name="Wrestling" value="8"> 8 <br />
                           <input type="radio" name="Wrestling" value="9"> 9 <br />
                           <input type="radio" name="Wrestling" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Football
                          </td>
                          <td>
                           <input type="radio" name="Football" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Football" value="2"> 2 <br />
                           <input type="radio" name="Football" value="3"> 3 <br />
                           <input type="radio" name="Football" value="4"> 4 <br />
                           <input type="radio" name="Football" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Football" value="6"> 6 <br />
                           <input type="radio" name="Football" value="7"> 7 <br />
                           <input type="radio" name="Football" value="8"> 8 <br />
                           <input type="radio" name="Football" value="9"> 9 <br />
                           <input type="radio" name="Football" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Hockey
                          </td>
                          <td>
                           <input type="radio" name="Hockey" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Hockey" value="2"> 2 <br />
                           <input type="radio" name="Hockey" value="3"> 3 <br />
                           <input type="radio" name="Hockey" value="4"> 4 <br />
                           <input type="radio" name="Hockey" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Hockey" value="6"> 6 <br />
                           <input type="radio" name="Hockey" value="7"> 7 <br />
                           <input type="radio" name="Hockey" value="8"> 8 <br />
                           <input type="radio" name="Hockey" value="9"> 9 <br />
                           <input type="radio" name="Hockey" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Miscellaneous
                          </td>
                          <td>
                           <input type="radio" name="Miscellaneous" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Miscellaneous" value="2"> 2 <br />
                           <input type="radio" name="Miscellaneous" value="3"> 3 <br />
                           <input type="radio" name="Miscellaneous" value="4"> 4 <br />
                           <input type="radio" name="Miscellaneous" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Miscellaneous" value="6"> 6 <br />
                           <input type="radio" name="Miscellaneous" value="7"> 7 <br />
                           <input type="radio" name="Miscellaneous" value="8"> 8 <br />
                           <input type="radio" name="Miscellaneous" value="9"> 9 <br />
                           <input type="radio" name="Miscellaneous" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Real-Time Games
                          </td>
                          <td>
                           <input type="radio" name="RealTime" value="1"> 1 - Hate them <br />
                           <input type="radio" name="RealTime" value="2"> 2 <br />
                           <input type="radio" name="RealTime" value="3"> 3 <br />
                           <input type="radio" name="RealTime" value="4"> 4 <br />
                           <input type="radio" name="RealTime" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="RealTime" value="6"> 6 <br />
                           <input type="radio" name="RealTime" value="7"> 7 <br />
                           <input type="radio" name="RealTime" value="8"> 8 <br />
                           <input type="radio" name="RealTime" value="9"> 9 <br />
                           <input type="radio" name="RealTime" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Turn-Based Games
                          </td>
                          <td>
                           <input type="radio" name="TurnBased" value="1"> 1 - Hate them <br />
                           <input type="radio" name="TurnBased" value="2"> 2 <br />
                           <input type="radio" name="TurnBased" value="3"> 3 <br />
                           <input type="radio" name="TurnBased" value="4"> 4 <br />
                           <input type="radio" name="TurnBased" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="TurnBased" value="6"> 6 <br />
                           <input type="radio" name="TurnBased" value="7"> 7 <br />
                           <input type="radio" name="TurnBased" value="8"> 8 <br />
                           <input type="radio" name="TurnBased" value="9"> 9 <br />
                           <input type="radio" name="TurnBased" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Dancing
                          </td>
                          <td>
                           <input type="radio" name="Dancing" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Dancing" value="2"> 2 <br />
                           <input type="radio" name="Dancing" value="3"> 3 <br />
                           <input type="radio" name="Dancing" value="4"> 4 <br />
                           <input type="radio" name="Dancing" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Dancing" value="6"> 6 <br />
                           <input type="radio" name="Dancing" value="7"> 7 <br />
                           <input type="radio" name="Dancing" value="8"> 8 <br />
                           <input type="radio" name="Dancing" value="9"> 9 <br />
                           <input type="radio" name="Dancing" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Singing
                          </td>
                          <td>
                           <input type="radio" name="Singing" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Singing" value="2"> 2 <br />
                           <input type="radio" name="Singing" value="3"> 3 <br />
                           <input type="radio" name="Singing" value="4"> 4 <br />
                           <input type="radio" name="Singing" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Singing" value="6"> 6 <br />
                           <input type="radio" name="Singing" value="7"> 7 <br />
                           <input type="radio" name="Singing" value="8"> 8 <br />
                           <input type="radio" name="Singing" value="9"> 9 <br />
                           <input type="radio" name="Singing" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Instruments
                          </td>
                          <td>
                           <input type="radio" name="Instruments" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Instruments" value="2"> 2 <br />
                           <input type="radio" name="Instruments" value="3"> 3 <br />
                           <input type="radio" name="Instruments" value="4"> 4 <br />
                           <input type="radio" name="Instruments" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Instruments" value="6"> 6 <br />
                           <input type="radio" name="Instruments" value="7"> 7 <br />
                           <input type="radio" name="Instruments" value="8"> 8 <br />
                           <input type="radio" name="Instruments" value="9"> 9 <br />
                           <input type="radio" name="Instruments" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            First Person Games
                          </td>
                          <td>
                           <input type="radio" name="FirstPerson" value="1"> 1 - Hate them <br />
                           <input type="radio" name="FirstPerson" value="2"> 2 <br />
                           <input type="radio" name="FirstPerson" value="3"> 3 <br />
                           <input type="radio" name="FirstPerson" value="4"> 4 <br />
                           <input type="radio" name="FirstPerson" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="FirstPerson" value="6"> 6 <br />
                           <input type="radio" name="FirstPerson" value="7"> 7 <br />
                           <input type="radio" name="FirstPerson" value="8"> 8 <br />
                           <input type="radio" name="FirstPerson" value="9"> 9 <br />
                           <input type="radio" name="FirstPerson" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Third Person Games
                          </td>
                          <td>
                           <input type="radio" name="ThirdPerson" value="1"> 1 - Hate them <br />
                           <input type="radio" name="ThirdPerson" value="2"> 2 <br />
                           <input type="radio" name="ThirdPerson" value="3"> 3 <br />
                           <input type="radio" name="ThirdPerson" value="4"> 4 <br />
                           <input type="radio" name="ThirdPerson" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="ThirdPerson" value="6"> 6 <br />
                           <input type="radio" name="ThirdPerson" value="7"> 7 <br />
                           <input type="radio" name="ThirdPerson" value="8"> 8 <br />
                           <input type="radio" name="ThirdPerson" value="9"> 9 <br />
                           <input type="radio" name="ThirdPerson" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Shoot 'Em Up
                          </td>
                          <td>
                           <input type="radio" name="ShootEmUp" value="1"> 1 - Hate them <br />
                           <input type="radio" name="ShootEmUp" value="2"> 2 <br />
                           <input type="radio" name="ShootEmUp" value="3"> 3 <br />
                           <input type="radio" name="ShootEmUp" value="4"> 4 <br />
                           <input type="radio" name="ShootEmUp" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="ShootEmUp" value="6"> 6 <br />
                           <input type="radio" name="ShootEmUp" value="7"> 7 <br />
                           <input type="radio" name="ShootEmUp" value="8"> 8 <br />
                           <input type="radio" name="ShootEmUp" value="9"> 9 <br />
                           <input type="radio" name="ShootEmUp" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Rail Shooters
                          </td>
                          <td>
                           <input type="radio" name="RailShooter" value="1"> 1 - Hate them <br />
                           <input type="radio" name="RailShooter" value="2"> 2 <br />
                           <input type="radio" name="RailShooter" value="3"> 3 <br />
                           <input type="radio" name="RailShooter" value="4"> 4 <br />
                           <input type="radio" name="RailShooter" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="RailShooter" value="6"> 6 <br />
                           <input type="radio" name="RailShooter" value="7"> 7 <br />
                           <input type="radio" name="RailShooter" value="8"> 8 <br />
                           <input type="radio" name="RailShooter" value="9"> 9 <br />
                           <input type="radio" name="RailShooter" value="10"> 10 - Love 'em! <br />
                          </td>
                        </tr>
                        <tr>
                          <td>
                            Trivia
                          </td>
                          <td>
                           <input type="radio" name="Trivia" value="1"> 1 - Hate them <br />
                           <input type="radio" name="Trivia" value="2"> 2 <br />
                           <input type="radio" name="Trivia" value="3"> 3 <br />
                           <input type="radio" name="Trivia" value="4"> 4 <br />
                           <input type="radio" name="Trivia" value="5" checked> 5 - They're okay <br />
                           <input type="radio" name="Trivia" value="6"> 6 <br />
                           <input type="radio" name="Trivia" value="7"> 7 <br />
                           <input type="radio" name="Trivia" value="8"> 8 <br />
                           <input type="radio" name="Trivia" value="9"> 9 <br />
                           <input type="radio" name="Trivia" value="10"> 10 - Love 'em! <br />
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