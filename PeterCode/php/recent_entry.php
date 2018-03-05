<?php
//FILE CANNOT HAVE ANY ECHO STATEMENTS EXCEPT EXPECTED DATA
//COMMENT OUT AFTER DEBUGGING IS COMPLETE

$mac = $_POST["mac"];



// $mac;
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

$result = $database->query("SELECT data_number FROM sensor_data WHERE id = '{$id}'");

if($result->num_rows > 0){
	
	//find largest existing data_number
	$rowSQL = $database->query( "SELECT MAX( data_number ) AS max FROM sensor_data WHERE id = '{$id}'" );
	$row = $rowSQL->fetch_assoc();
	$largest_number = $row['max'];
	//echo $largest_number;
	
$recent = $database->query("SELECT light_level, air_humidity, soil_moisture, temperature, water_level, battery_level FROM sensor_data WHERE id = '{$id}' AND data_number = '{$largest_number}'");
		while($recent_row = $recent->fetch_assoc()) {
			//echo "light_level" . "," . $recent_row[light_level] . "," . "air_humidity" . "," . $recent_row[air_humidity]. "," . "soil_moisture".  "," . $recent_row[soil_moisture] . "," . "temperature" . "," . $recent_row[temperature] . "," . "water_level" . "," . $recent_row[water_level] . "," . "battery_level" . "," . $recent_row[battery_level];	
			echo $recent_row[light_level] . "," . $recent_row[air_humidity]. "," . $recent_row[soil_moisture] . "," . $recent_row[temperature] . "," . $recent_row[water_level] . "," . $recent_row[battery_level];			
		}		


}


mysqli_close($database);

?>
