<?php
	session_start();  
	if(isset($_SESSION[$_GET["username"]]))
	    unset($_SESSION[$_GET["username"]]); 
	session_destroy();
    header("Location: ../../../index.html")
?>
