<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>News</title>
</head>
<body>
    <p>
        Welcome <?php echo $_GET["username"]?>
    </p>

    <form action=<?php echo "login/destroySession.php?username=".$_GET["username"]?> method='GET'>
        <input type='submit' value='Logout' name='logout' />
    </form>
</body>
</html>
