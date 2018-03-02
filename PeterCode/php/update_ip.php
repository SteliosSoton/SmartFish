<?php


$local = $_POST["local"];
$vers = $_POST["vers"];
$mac = $_POST["mac"];


echo $mac;
echo "   ";
echo $local;
echo "   ";
echo $vers;
echo "   ";

$database = new mysqli("localhost", "plant_connect", "teamholly", "BioBloom");

if ($database->connect_error) {
    die("Connection failed: " . $database->connect_error);
}
echo "\n";
echo "Connected successfully		";

$result = $database->query("SELECT id, mac, plant_name, plant_profile, local_ip FROM pot_details WHERE mac = '{$mac}'");
if($result->num_rows > 1){
	echo "Duplicate pot	?!	";
} else if($result->num_rows < 1) {
	echo "New pot, adding to database		";
	$database->query("INSERT INTO pot_details (mac, local_ip, vers) VALUES ('{$mac}', '{$local}', '{$vers}')");
} else if($result->num_rows == 1){
	echo "Pot exists, updating info		";
	$database->query("UPDATE pot_details SET local_ip = '{$local}', vers = '{$vers}' WHERE mac = '{$mac}'");
}


mysqli_close($database);

?>
