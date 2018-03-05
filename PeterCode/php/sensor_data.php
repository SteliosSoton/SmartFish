<?php

$mac = $_GET["mac"];
$light_level = $_GET["light_level"];
$air_humidity = $_GET["air_humidity"];
$soil_moisture = $_GET["soil_moisture"];
$temperature = $_GET["temperature"];
$water_level = $_GET["water_level"];
$battery_level = $_GET["battery_level"];



echo $mac;
echo "   ";


$database = new mysqli("localhost", "plant_connect", "teamholly", "BioBloom");

if ($database->connect_error) {
    die("Connection failed: " . $database->connect_error);
}
//echo "\n";
echo "Connected successfully		";

//find id from details table
$info = $database->query("SELECT id, mac FROM pot_details WHERE mac ='{$mac}'");
$id_row = $info->fetch_assoc();
$id = $id_row[id];
echo $id;


$result = $database->query("SELECT data_number FROM sensor_data WHERE id = '{$id}'");
$size = $result->num_rows;
echo $size;

if($result->num_rows > 0){
	echo "Adding next row of data";
	
	//find largest existing data_number
	$rowSQL = $database->query( "SELECT MAX( data_number ) AS max FROM sensor_data WHERE id = '{$id}'" );
	$row = $rowSQL->fetch_assoc();
	$largest_number = $row['max'];
	echo $largest_number;
	$data_number = $largest_number + 1;
	echo $data_number;
	//insert new row into table

}

else if($result->num_rows < 1) {
	echo "Adding first data point		";

//start data numbers at 1
$data_number =1;

}

//insert new row into table
$database->query("INSERT INTO sensor_data (data_number, id, light_level, air_humidity, soil_moisture, temperature, water_level, battery_level) VALUES ('{$data_number}', '{$id}', '{$light_level}', '{$air_humidity}', '{$soil_moisture}', '{$temperature}', '{$water_level}', '{$battery_level}')");	


mysqli_close($database);

?>
