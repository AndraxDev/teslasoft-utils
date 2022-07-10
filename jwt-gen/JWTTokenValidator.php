<?php

require_once 'jwt_rs384.php';
$jwt = $_GET['auth_token'];

if (is_jwt_valid($jwt) == TRUE) {
    echo("Token is valid");
} else {
    echo("Invalid token");
}

?>