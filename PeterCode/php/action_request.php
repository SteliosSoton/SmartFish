<?php

$mac = $_POST["mac"];
$id = $_POST["id"];


echo $mac;
echo "   ";
echo $id;
echo "   ";
$database = new mysqli("localhost", "plant_connect", "teamholly", "BioBloom");

if ($database->connect_error) {
    die("Connection failed: " . $database->connect_error);
} 

echo "\n";
echo "Connected successfully		";


$result = $database->query("SELECT local_ip FROM pot_details WHERE mac = '{$mac}'");

$ip = $result->fetch_object()->local_ip;
echo $ip;
$url = 'http://' . $ip . ':4132/action_request';
$data = array('id' => $id);

$options = array(
    'http' => array(
        'header'  => "Content-type: application/x-www-form-urlencoded\r\n",
        'method'  => 'POST',
        'content' => http_build_query($data)
    )
);
$context  = stream_context_create($options);
$go = file_get_contents($url, false, $context);

mysqli_close($database);

?>