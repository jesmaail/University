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
		}
	?>
	<div id="content" style="width: 900px; margin:auto">
		<div id="header">
			<h1> Order Acknowledgement </h1>
			<!-- <img src = "logo.svg" style="float:right"/> -->
		</div>

		<hr/>

		<div id="top">
			<?php
				$id = 11;
				$query = mysql_query("SELECT name, email, address, city, totalpay, cardtype, cardnum, date FROM cust, orderpay WHERE cust.custid = orderpay.custid AND orderid =".$id);
				$details =mysql_fetch_array($query);
			?>

			<table style="width: 900px"> 
				<tr>
					<td><b>Delivery</b></td>
					<td><b>Details</b></td>
					<td width = "63%"></td>
					<td><b>Payment</b></td>
					<td><b>Details</b></td>

				<tr>
					<td>Order #: </td>
					<td><?php echo $id ?></td>
					<td></td>
					<td>Total:</td>
					<td>&pound;<?php echo $details["totalpay"] ?> </td>
				</tr>
				<tr>
					<td>Name: </td>
					<td><?php echo $details["name"] ?></td>
					<td></td>
					<td>Method:</td>
					<td><?php echo $details["cardtype"] ?></td>
				</tr>
				<tr>
					<td>Email: </td>
					<td><?php echo $details["email"] ?></td>
					<td></td>
					<td>Card:</td>
					<td><?php echo $details["cardnum"] ?></td>
				</tr>
				<tr>
					<td>Address: </td>
					<td><?php echo $details["address"] ?></td>
					<td></td>
					<td>Date:</td>
					<td><?php echo $details["date"] ?></td>
				</tr>
				<tr>
					<td></td>
					<td><?php echo $details["city"] ?></td>
					<td></td>
					<td></td>
					<td></td>
				</tr>
			</table>
		</div>

		<hr/>		

		<div id="orderdetails">
			<table style="width: 900px">
				<tr>
					<td><b>Order Details</b>
				</tr>
				<tr>
					<td>Product Details</td>
					<td>Ordered</td>
					<td>Price</td>
					<td>Total</td>
				</tr>
				<tr>
					<td><b>chilled</b>
				</tr>
				<?php 
				$query = mysql_query("SELECT name, quantity, unitprice, (quantity * unitprice) as total FROM item, tran WHERE item.itemid = tran.itemid AND orderid =".$id." AND cat = 'chilled' ORDER BY tran.itemid");	
				while($items =mysql_fetch_array($query)){ ?>
					<tr>
						<td><?php echo $items["name"];?></td>
						<td><?php echo $items["quantity"];?></td>
						<td>&pound;<?php echo $items["unitprice"];?></td>
						<td>&pound;<?php echo $items["total"];?></td>
					</tr>
				<?php
				}?>
				<tr>
					<td><b>drinks</b>
				</tr>
				<?php 
				$query = mysql_query("SELECT name, quantity, unitprice, (quantity * unitprice) as total FROM item, tran WHERE item.itemid = tran.itemid AND orderid =".$id." AND cat = 'drinks' ORDER BY tran.itemid");	
				while($items =mysql_fetch_array($query)){ ?>
					<tr>
						<td><?php echo $items["name"];?></td>
						<td><?php echo $items["quantity"];?></td>
						<td>&pound;<?php echo $items["unitprice"];?></td>
						<td>&pound;<?php echo $items["total"];?></td>
					</tr>
				<?php
				}?>
				<tr>
					<td><b>foodcupboard</b>
				</tr>
				<?php 
				$query = mysql_query("SELECT name, quantity, unitprice, (quantity * unitprice) as total FROM item, tran WHERE item.itemid = tran.itemid AND orderid =".$id." AND cat = 'foodcupboard' ORDER BY tran.itemid");	
				while($items =mysql_fetch_array($query)){ ?>
					<tr>
						<td><?php echo $items["name"];?></td>
						<td><?php echo $items["quantity"];?></td>
						<td>&pound;<?php echo $items["unitprice"];?></td>
						<td>&pound;<?php echo $items["total"];?></td>
					</tr>
				<?php
				}?>
				<tr>
					<td><b>fresh</b>
				</tr>
				<?php 
				$query = mysql_query("SELECT name, quantity, unitprice, (quantity * unitprice) as total FROM item, tran WHERE item.itemid = tran.itemid AND orderid =".$id." AND cat = 'fresh' ORDER BY tran.itemid");	
				while($items =mysql_fetch_array($query)){ ?>
					<tr>
						<td><?php echo $items["name"];?></td>
						<td><?php echo $items["quantity"];?></td>
						<td>&pound;<?php echo $items["unitprice"];?></td>
						<td>&pound;<?php echo $items["total"];?></td>
					</tr>
				<?php
				}?>
				<tr>
					<td><b>frozen</b>
				</tr>
				<?php 
				$query = mysql_query("SELECT name, quantity, unitprice, (quantity * unitprice) as total FROM item, tran WHERE item.itemid = tran.itemid AND orderid =".$id." AND cat = 'frozen' ORDER BY tran.itemid");	
				while($items =mysql_fetch_array($query)){ ?>
					<tr>
						<td><?php echo $items["name"];?></td>
						<td><?php echo $items["quantity"];?></td>
						<td>&pound;<?php echo $items["unitprice"];?></td>
						<td>&pound;<?php echo $items["total"];?></td>
					</tr>
				<?php
				}?>
				<tr>
					<td><b>nonfood</b>
				</tr>
				<?php 
				$query = mysql_query("SELECT name, quantity, unitprice, (quantity * unitprice) as total FROM item, tran WHERE item.itemid = tran.itemid AND orderid =".$id." AND cat = 'nonfood' ORDER BY tran.itemid");	
				while($items =mysql_fetch_array($query)){ ?>
					<tr>
						<td><?php echo $items["name"];?></td>
						<td><?php echo $items["quantity"];?></td>
						<td>&pound;<?php echo $items["unitprice"];?></td>
						<td>&pound;<?php echo $items["total"];?></td>
					</tr>
				<?php
				}?>
		</div>
	</div>

	</body>
</html>