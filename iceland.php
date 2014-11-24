<html>
<head>
</head>
	<body>
	<?php
		$server = "localhost";
		$user = "root";
		$password = "password";
		$db = "cw2";
		$conn = mysql_connect($server, $user, $password);
		$db_select_success = mysql_select_db($db,$conn);

		if(!$conn){ 
			die("Error connecting to MySQL: ". mysql_error());	
		}
		if(!$db_select_success){
			die("Error selecting database: ". mysql_error());
		}else{
			// echo "MySQL database: " . $db ." selected.";
		}
	?>

	<div id="header">
		<h1> Order Acknowledgement </h1>
		<img src = "logo.svg" style="float:right"/>
	</div>

	<hr/>

	<div id="top">
		<?php
			$id = 11;
			$query = mysql_query("SELECT name, email, address FROM cust, orderpay WHERE cust.custid = orderpay.custid AND orderid =".$id);
			$customer =mysql_fetch_array($query);
		?>
		<div id="deliverydetails" style="float:left">			
			<table> 
				<b>Delivery Details</b>
				<tr>
					<td>Order #: </td>
					<td><?php echo $id	?></td>
				</tr>
				<tr>
					<td>Name: </td>
					<td><?php echo $customer["name"] ?></td>
				</tr>
				<tr>
					<td>Email: </td>
					<td><?php 	?></td>
				</tr>
				<tr>
					<td>Address: </td>
					<td><?php 	?></td>
				</tr>
			</table>
		</div>

		<div id="paymentdetails" style="float:right">
			<table >
				<b>Payment Details</b>
				<tr>
					<td>Total #: </td>
					<td><?php 	?></td>
				</tr>
				<tr>
					<td>Method: </td>
					<td><?php 	?></td>
				</tr>
				<tr>
					<td>Card: </td>
					<td><?php 	?></td>
				</tr>
				<tr>
					<td>Date: </td>
					<td><?php 	?></td>
				</tr>
			</table>

		</div>

	</div>

	</body>
</html>
