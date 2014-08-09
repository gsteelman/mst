<form name="login" action="login.php" method="post" >
  <tr align="right" height="39">
    <td background="loginbanner.jpg" >
      <form action="login.php" method="post" >
        <span class="style2">
          <?php 
          if (isset($_SESSION['username']))
          {
          echo "Welcome, $_SESSION[username]. <a href=\"/gamewarp/logout.php\">Log Out</a> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
          }
          else
          {
          echo "
          Name: <input type=\"text\" name=\"userName\" />
          Password: <input type=\"password\" name=\"password\" />
          <a href=\"#\" onclick=\"document.login.submit()\"> Login </a> / <a href=\"/gamewarp/newaccount.php\"> New </a>&nbsp;&nbsp;&nbsp;&nbsp;";
          }
          ?>
        </td>
  </tr>
  </span>
</form>
                <tr align="center"><td><a href=""><img src="gwbanner.jpg" border="0"/></a></td></tr>
                <tr align="center"><td>
                <table border="0" cellpadding="0" cellspacing="0">
                    <tr>
                    <td><img src="mainmenu1.jpg" border="0"/></td><td><a href="/gamewarp/index.php"><img src="mainmenu2.jpg" border="0"/></a></td><td>
<ul id="nav">
	<li class="item1"><a><img src="mainmenu3.jpg" border="0"/></a>
		<ul>
			<li><a href="/gamewarp/findnewgames.php"><span class="style3">Find New Games</span></a></li>
      <li>
        <a href="/gamewarp/rateagame.php">
          <span class="style3">Rate A Game</span>
        </a>
      </li>
			<li><a href="/gamewarp/questionnaire.php">
        <span class="style3">Questionnaires</span>
      </a></li>
      <?php 
      if ($_SESSION['adminLvl'] == 1) 
      {
      echo "<li><a href=\"/gamewarp/databaseadmin.php\">
            <span class=\"style3\">DB Admin</span>
            </a></li>";
      }      
      ?>
		</ul>
	</li>
	<li class="item2"><a><img src="mainmenu4.jpg" border="0"/></a>
		<ul>
			<li><a href="/gamewarp/myratings.php">
        <span class="style3">My Ratings</span>
      </a></li>
			<li><a href="/gamewarp/previous.php">
        <span class="style3">Previous Recommendations</span>
      </a></li>
		</ul>
	</li>
</ul>
</td><td><a href="/gamewarp/aboutus.php"><img src="mainmenu5.jpg" border="0"/></a></td><td><a href="/gamewarp/contactus.php"><img src="mainmenu6.jpg" border="0"/></a></td><td><a href="/gamewarp/help.php"><img src="mainmenu7.jpg" border="0"/></a></td><td><img src="mainmenu8.jpg" border="0"/></td></tr>
                </table>
                </td></tr>