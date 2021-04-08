<?php
	session_start();
    $_SESSION[$_POST["username"]] = 1;
	header("Location: ../news.php?username=".$_POST["username"]);
?>