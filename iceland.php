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
			<table>
				<tr>
					<td width="80%"><h1> Order Acknowledgement </h1></td>
					<td><img src="logo.svg" height="50" width="200"/></td>
				</tr>
			</table>
		</div>

		<hr/>

		<div id="top">
			<?php
				if (isset($_POST['id'])){
					$id = $_POST['id'];
				}else{
					$id = 11;
				}

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

		<div id="orderdetails" style="width: 900px">
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
				<?php 
				$query = mysql_query("SELECT sum(quantity * unitprice) as grand, sum(quantity) as totalQ FROM item, tran WHERE item.itemid = tran.itemid AND orderid =".$id." ORDER BY tran.itemid");	
				while($items =mysql_fetch_array($query)){ ?>
					<tr>
						<td><b>Grand Total</b></td>
						<td><?php echo $items["totalQ"];?></td>
						<td></td>
						<td><b>&pound;<?php echo $items["grand"];?></b></td>
					</tr>
				<?php
				}?>
				<?php
				$query = mysql_query("	SELECT (sum(quantity * unitprice) - totalpay) as discount
										FROM orderpay, item, tran
										WHERE item.itemid = tran.itemid
										AND orderpay.orderid =".$id."
										AND tran.orderid =".$id."
										ORDER BY tran.itemid
									");

				// while($items =mysql_fetch_array($query)){ 
				$items = mysql_fetch_array($query);
				if($items["discount"] > 0){
					?>
					<tr>
						<td><b>Discount</b></td>
						<td></td>
						<td></td>
						<td><b>&pound;<?php echo $items["discount"];?></b></td>
					</tr>
				<?php
				}?>
			</table>
		</div>

		<div id="btmImages" style="width:900px; background-color:#E7E7E7">
			<p style="text-align:center"> †Lines are open Monday to Saturday 6am-10pm and Sunday 8am-10pm. </p>
			<table style="width:900px">
				<tr>
					<td width="30%"></td>
					<td><img src = "ppLogo.jpg" height="50" width="100"/></td>
					<td><img src = "mc-logo.png" height="25" width="75"/></td>
					<td><img src = "v-logo.jpg" height="50" width="100"/></td>
					<td width="30%"></td>
				</tr>
			</table>
		</div>
		<hr/>
		<br/>
		<form method="post">
			<table style="width:900px">
				<tr>
					<td><b>Query</b></td>
					<td>Order #:</td>
					<td> <input type="Text" value=<?php echo $id?> name="id"/> </td>
					<td width="50%"></td>
					<td><input type="submit"></td>
				</tr>
			</table>
		</form>
	</div>

	</body>
</html>
