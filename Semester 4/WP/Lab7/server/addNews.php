<?php
    header('Access-Control-Allow-Origin: *');
    header('Cache-Control: no-cache, must-revalidate');
    header('Expires: Sat, 01 Jan 2022 00:00:00 GMT');
    header('Content-Type: application/json; charset=UTF-8');

    require 'service/NewsService.php';
    /*
    if($newsService->addNews($_GET['title'], $_GET['category'], $_GET['date'], $_GET['text'])){
        echo json_encode(array('true'));
    }
    else
        echo json_encode(array('false'));
    */
    echo json_encode($newsService->addNews($_GET['title'], $_GET['username'], $_GET['category'], $_GET['date'], $_GET['text']));
?>