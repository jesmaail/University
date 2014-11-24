<html>
<head>
</head>
	<body>
	<?php
		$server = "localhost";
		$user = "root";
		$password = "sabih93";
		$db = "cs250";

		$conn = mysql_connect($server, $user, $password);
		$db_select_success = mysql_select_db($db,$conn);

		if(!$conn)
		{
			die("Error connecting to MySQL: ");
		}

		if(!$db_select_success)
		{
			die("Error selecting database: ");
		}
		else
		{
			echo "MySQL database: " . $db ." selected.";
		}
	?>
	</body>
</html>
