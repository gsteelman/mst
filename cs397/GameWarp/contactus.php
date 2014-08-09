<?php include 'sessionHandler.php'; ?>

<html>
<head>
    <title>Contact Us</title>
    <?php include'style.html'; ?>
</head>
<body bgcolor="Black">
    <SPAN style="FONT-FAMILY: Arial">
        <table width="900" align="center" border="0" cellpadding="0" cellspacing="0">
            <?php include'menu.php'; ?>
                <tr><td><table width="100%" background="bg.jpg" background-attachment="fixed">
                    <tr><td width="5"></td><td>&nbsp;&nbsp;&nbsp;&nbsp;<span class="style1">Contact Us</span></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td><hr width="100%" /></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>
                    <?php ?>
                    </td><td width="5"></td></tr>
                    <tr><td width="5"></td><td><span class="subheader">To contact Team Game Warp please fill out the form below:</span></td><td width="5"></td></tr>
                    <tr><td width="5"></td><td>&nbsp;</td><td width="5"></td></tr>
                    <form name="form1" method="post" action="sendmail.php">
                    <tr><td width="5"></td><td>
                    <table width="50%" border="0" cellpadding="0" cellspacing="0" align="center">
                    <tr>
                    <td>Name:</td>
                    <td><input type="text" name="name" size="35" /></td>
                    </tr>
                    <tr>
                    <td>E-Mail:</td>
                    <td><input type="text" name="email" size="35" /></td>
                    </tr>
                    <tr>
                    <td>Phone:</td>
                    <td><input type="text" name="phone" size="35" /></td>
                    </tr>
                    <tr>
                    <td>Message:</td>
                    <td><textarea id=txtRequest name=message rows=5 cols=35></textarea></td>
                    </tr>
                    <tr>
                    <td></td>
                    <td align="left"><input type="submit" value="Send"/></td>
                    </tr>
                    </table>
					</form>
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
</html>