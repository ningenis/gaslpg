<?php
    // Connect to MySQL
    include("dbconnect.php");
    $sensorapi = $_GET["sensorapi"];          //Variabel Sensor Api
    $sensorgas = $_GET["sensorgas"];          //Variabel Sensor Gas 
	$SQL = "INSERT INTO detektor (nilai_sensor_api, nilai_sensor_gas) VALUES ('$sensorapi', '$sensorgas')"; // SQL Query    
    // Execute SQL
	mysqli_query($dbh, $SQL);
    // To review_data.php
    header("Location: data_review.php");
?>