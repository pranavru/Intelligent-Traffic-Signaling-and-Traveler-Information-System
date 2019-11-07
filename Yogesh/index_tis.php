<?php
	ob_start();
	session_start();
	$rootDir = realpath($_SERVER["DOCUMENT_ROOT"]);
	include "$rootDir/connect_tis.php";
?>
<!DOCTYPE html>
<html lang="en">
<head>
	<title> Home | Traveler Information System </title>
	<meta charset="utf-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
	<link rel="stylesheet" href="/css/header_tis.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
	<style>
		.box {
			background-color: powderblue;
			margin-left: 3%;
			margin-right: 3%;
			border-radius:5px;
		}
		.box > h3 {
			padding: 1% 0% 0% 1%;
			color: blue;
		}
		.view_all {
			float: right;
			margin-right:2%;
			font-size:15px;
		}
		.panel-body {
			padding: 0px;
		}
		.box .col-sm-3 img {
			width: 75%;
			max-height: 105px;
			max-width: 190px;
		}
		.box .col-sm-4 img {
			width: 75%;
			max-height: 160px;
			max-width: 270px;
		}
		.panel-footer > a {
			margin-left: 40%;
		}
		footer {
			background-color: #f2f2f2;
			padding: 25px;
		}
	</style>
</head>
<body>
<?php
	require "$rootDir/header_tis.php";
?>
<br><br>
<div class="box categories">
    <h3> Categories </h3>
    <div class="container">
        <div class="row">
			<div class='col-sm-12'>
				<div class='panel panel-primary'>
					<div class='panel-heading'> Current Traffic </div>
					<div class='panel-body' align='center'><img src='/images/pngImages/.png' class='img-responsive' alt='Image 1'></div>
					<div class='panel-footer'>
						<a href='/shop.php?'> View All </a>
					</div>
				</div>
			</div>
        </div>
    </div>
</div>
<div class="box categories">
    <h3> Categories </h3>
    <div class="container">
        <div class="row">
			<div class='col-sm-12'>
				<div class='panel panel-primary'>
					<div class='panel-heading'> Current Traffic </div>
					<div class='panel-body' align='center'><img src='/images/pngImages/.png' class='img-responsive' alt='Image 1'></div>
					<div class='panel-footer'>
						<a href='/shop.php?'> View All </a>
					</div>
				</div>
			</div>
        </div>
    </div>
</div>
<!--div class="box hot_picks">
    <h3> Favourites <a href='/shop.php'><span class="view_all"> View All </span></a></h3>
    <div class="container">
        <div class="row">
            <?php
				$sql = "SELECT ProdID, ProdName, ProdImage
						FROM Product p
						ORDER BY p.ProdPopularity DESC
						LIMIT 4";
				$catRes = mysqli_query($conn,$sql);
				if (mysqli_num_rows($catRes) > 0) {
					while($row = mysqli_fetch_assoc($catRes)) {
						echo "<div class='col-sm-3'>" .
								"<div class='panel panel-primary'>" .
									"<div class='panel-heading'> Product Name </div>" .
									"<div class='panel-body' align='center'><img src='/images/pngImages/" .$row['ProdImage']. ".png' class='img-responsive' alt='Product Name'></div>" .
									"<div class='panel-footer'><a href='/product.php?ProdID=" .$row['ProdID']. "'> View </a></div>" .
								"</div>" .
							"</div>";
					}
				}
			?>
        </div>
    </div>
</div-->
<br><br><br>
<?php
	include "$rootDir/footer_tis.php";
?>
</body>
</html>