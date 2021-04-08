<?php
 header('Access-Control-Allow-Origin: *');
   
require_once 'service/NewsService.php';
require_once 'service/UserService.php';
require_once 'view.php';

class Controller
{
    private $view;
    private $userService;
    private $newsService;	

    public function __construct(){
        $this->view = new View();
        $this->userService = new UserService();
        $this->newsService = new NewsService();
    }

    public function service() {
	   if (isset($_GET['action']) && !empty($_GET['action'])) {
           switch($_GET['action']){
               case "getUser":
                    $this->{$_GET['action']}($_GET['username'], $_GET['password']);
                    break;
                case "addNews":
                    $this->{$_GET['action']}(
                        $_GET['title'], 
                        $_GET['username'], 
                        $_GET['category'],
                        $_GET['date'],
                        $_GET['text']
                    );
                    break;
                case "getUserNews":
                    $this->{$_GET['action']}($_GET['username']);
                    break;
                case "getNewsWithTitle":
                    $this->{$_GET['action']}($_GET['title']);
                    break;
                case "getFilteredNews":
                    $this->{$_GET['action']}($_GET['category'], $_GET['startDate'], $_GET['endDate']);
                    break;
                default:
                $this->{$_GET['action']}();
           } 
	   }
    }

    public function getUser($username, $password) {
	    $this->view->output($this->userService->login($_GET['username'], $_GET['password']));
    }

    public function getNews(){       
        $this->view->output($this->newsService->getAllNews());
    }

    public function addNews($title, $producer, $category, $date, $text){
        $this->view->output($this->newsService->addNews($title, $producer, $category, $date, $text));
    }

    public function getUserNews($user){
        $this->view->output($this->newsService->getUserNews($user));
    }

    public function getNewsWithTitle($title){
        $this->view->output($this->newsService->getNewsWithTitle($title));
    }

    public function getFilteredNews($category, $startDate, $endDate){
        $this->view->output($this->newsService->getFilteredNews($category, $startDate, $endDate));
    }
}

$controller = new Controller();
$controller->service();
?>
