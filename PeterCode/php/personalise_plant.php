<?php


$mac = $_POST["mac"];
$plant_name = $_POST["name"];
$plant_profile = $_POST["profile"];

echo $mac;
echo "   ";
echo $plant_profile;
echo "   ";
echo $plant_name;
echo "   ";

$database = new mysqli("localhost", "plant_connect", "teamholly", "BioBloom");

if ($database->connect_error) {
    die("Connection failed: " . $database->connect_error);
}
echo "\n";
echo "Connected successfully		";


	$database->query("UPDATE pot_details SET plant_name = '{$plant_name}', plant_profile = '{$plant_profile}' WHERE mac = '{$mac}'");


mysqli_close($database);

?>
