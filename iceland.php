<html>
<head>
</head>
	<body>
	<?php
		$server = "localhost";
		$user = "root";
		$password = "";
		$db = "cw2";
		$conn = mysql_connect($server, $user, $password);
		$db_select_success = mysql_select_db($db,$conn);

		if(!$conn){ 
			die("Error connecting to MySQL: ". mysql_error());	
		}
		if(!$db_select_success){
			die("Error selecting database: ". mysql_error());
		}else{
			echo "MySQL database: " . $db ." selected.";
		}
	?>
	</body>
</html>
