<?php
//This returns the mac addresses of plants without names or profiles attached to them
//mac addresses are returned as comma seperated values
//as values are echoed nothing else should be echoed once file is finalised

$database = new mysqli("localhost", "plant_connect", "teamholly", "BioBloom");

if ($database->connect_error) {
    die("Connection failed: " . $database->connect_error);
}
//echo "\n";
//echo "Connected successfully		";

$result = $database->query("SELECT mac FROM pot_details WHERE plant_profile IS NULL");
if ($result->num_rows > 0) {
		while($row = $result->fetch_assoc()) {
			echo $row["mac"] . ",";			
		}
	}		

mysqli_close($database);

?>
