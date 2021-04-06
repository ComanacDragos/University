<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <body>
        <form action="#" method="get">
        Nameeee: <input type="text" name="fname" />
        Age: <input type="text" name="age" />
        <input type="submit" />
        </form>
        
        <p><?php echo "hi"; ?></p>
        Welcomeee <?php 
        if(isset($_GET["fname"]))
            echo $_GET["fname"];
        else
            echo "Nobody" 
        ?>.
        <br />
        You are <?php 
        echo $_GET["age"]; 
        ?> years old! 
        
        </body>
</body>
</html>

<!--
Write a web application for a news service. 

Some users add or update news and others just view news. 
News are saved on a database and they have the following characteristics: 
text of the news, title, producer, date, category (politics, society, health etc.). 
The user who adds or updates news must log in using a username and password 
before doing this. The other type of users can see all the news from a range of 
dates and all news from a specific category (use AJAX for these filters). 
Also, on the news browsing page, the filter used for the previous browsing action 
(i.e. date range, category), should be displayed (do this in javascript).
-->