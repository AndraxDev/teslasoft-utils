<?php

require_once 'jwt_rs384.php';
$headers = array('alg'=>'RS384','typ'=>'JWT'); // use relevant algorithm name
$payload = array('username'=>$_GET['username'],'exp'=>(time() + 60)); // Replace with your payload
$jwt = generate_jwt($headers, $payload);
echo($jwt);

?>