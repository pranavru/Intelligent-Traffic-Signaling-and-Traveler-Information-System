<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "itsatis";

$conn = mysqli_connect($servername, $username, $password, $dbname);
if (!$conn) {
	die('Could not connect: ' . mysqli_connect_error());
}

$laneId = 11;
$density = 2;

if (isset($_GET['laneId'])) {
	$laneId = $_GET['laneId'];
	$density = $_GET['density'];
}

$sql = "INSERT INTO `Density`(`LaneId`, `Density`) VALUES ($laneId, $density)";
if (!mysqli_query($conn, $sql)) {
	die('Invalid query: ' . mysqli_error($conn));
}

echo "<h1>THE DATA HAS BEEN SENT!!</h1>";
mysqli_close($conn);
?>