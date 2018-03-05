<?php
//FILE CANNOT HAVE ANY ECHO STATEMENTS EXCEPT EXPECTED DATA
//COMMENT OUT AFTER DEBUGGING IS COMPLETE

$mac = $_POST["mac"];



//echo $mac;
//echo "   ";


$database = new mysqli("localhost", "plant_connect", "teamholly", "BioBloom");

if ($database->connect_error) {
    die("Connection failed: " . $database->connect_error);
}
//echo "\n";
//echo "Connected successfully		";

//find id from details table
$info = $database->query("SELECT id, mac FROM pot_details WHERE mac ='{$mac}'");
$id_row = $info->fetch_assoc();
$id = $id_row[id];
//echo $id;

$result = $database->query("SELECT light_level, air_humidity, soil_moisture, temperature, water_level, battery_level FROM sensor_data WHERE id = '{$id}'");

if($result->num_rows > 0){
	
	while($row = $result->fetch_assoc()) {

			//echo "light_level" . "," . $row[light_level] . "," . "air_humidity" . "," . $row[air_humidity]. "," . "soil_moisture".  "," . $row[soil_moisture] . "," . "temperature" . "," . $row[temperature] . "," . "water_level" . "," . $row[water_level] . "," . "battery_level" . "," . $row[battery_level];	
			echo $row[light_level] . "," . $row[air_humidity]. "," . $row[soil_moisture] . "," . $row[temperature] . "," . $row[water_level] . "," . $row[battery_level] . ",";			
		}		
}


mysqli_close($database);

?>
