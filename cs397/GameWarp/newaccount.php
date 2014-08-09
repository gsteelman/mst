<?php include 'sessionHandler.php'; ?>

<head>
  <title>New Account</title>
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
                      &nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Sign up for a new account</span>
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
                      if ($_SESSION["LoginErr"] == 1)
                      {
                        echo "<span class=\"sysnotes\">Username/Password invalid. <br> Sign up by filling out the form below.</span>";
                        $_SESSION["LoginErr"] = 0;
                      }
                      ?>
                    </td><td width="5"></td></tr>
                  <tr>
                    <td width="5"></td>
                    <td>
                      <span class="subheader">Please fill out the form below. A copy of your account information will be e-mailed to you.</span>
                    </td>
                    <td width="5"></td>
                  </tr>
                    <tr><td width="5"></td><td>
                      <form name="form1" method="post" action="signup.php">
                        <tr>
                          <td width="5"></td>
                          <td>
                            <table width="50%" border="0" cellpadding="0" cellspacing="0" align="center">
                              <tr>
                                <td>Name:</td>
                                <td>
                                  <input type="text" name="name" size="35" />
                                </td>
                              </tr>
                              <tr>
                                <td>Password:</td>
                                <td>
                                  <input type="password" name="password" size="35" />
                                </td>
                              </tr>
                              <tr>
                                <td>E-Mail:</td>
                                <td>
                                  <input type="text" name="email" size="35" />
                                </td>
                              </tr>
                              <tr>
                                <td></td>
                                <td align="left">
                                  <input type="submit" value="Create New Account"/>
                                </td>
                              </tr>
                            </table>
                          </form>
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
                </table></td></tr>
            <tr><td><table width=900" border="0" cellpadding="0" cellspacing="0">
                <tr align="center"><img src="footer.jpg"/></tr>
            </table></td></tr>
        </table>
    </SPAN>    
</body>