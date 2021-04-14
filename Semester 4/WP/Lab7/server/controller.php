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
               case "login":
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
                case "updateNews":
                    $this->{$_GET['action']}(
                        $_GET['title'], 
                        $_GET['username'], 
                        $_GET['category'],
                        $_GET['date'],
                        $_GET['text']
                    );
                    break;
                case "deleteNews":
                    $this->{$_GET['action']}(
                        $_GET['title'], 
                        $_GET['username']
                    );
                    break;
                case "getUserNews":
                    $this->{$_GET['action']}($_GET['username']);
                    break;
                case "getLoggedUser":
                    $this->{$_GET['action']}($_GET['username']);
                    break;
                case "getNewsWithTitle":
                    $this->{$_GET['action']}($_GET['title']);
                    break;
                case "updateNews":
                    $this->{$_GET['action']}($_GET['title'], $_GET['username']);
                    break;
                case "getFilteredNews":
                    $this->{$_GET['action']}($_GET['category'], $_GET['startDate'], $_GET['endDate']);
                    break;
                case "registerUser":
                    $this->{$_GET['action']}($_GET['username'], $_GET['password'], $_GET['confirmPassword']);
                    break;
                case "changePassword":
                    $this->{$_GET['action']}($_GET['username'], $_GET['password'], $_GET['confirmPassword'], $_GET['oldPassword']);
                    break;
                default:
                $this->{$_GET['action']}();
           } 
	   }
    }

    public function login($username, $password) {
	    $this->view->output($this->userService->login($username, $password));
    }

    public function getNews(){       
        $this->view->output($this->newsService->getAllNews());
    }

    public function addNews($title, $producer, $category, $date, $text){
        $username = $this->userService->getUser($producer);
        if($username)
            $this->view->output($this->newsService->addNews($title, $username, $category, $date, $text));
    }

    public function getUserNews($user){
        $username = $this->userService->getUser($user);
        if($username)
            $this->view->output($this->newsService->getUserNews($username));
    }

    public function getNewsWithTitle($title){
        $this->view->output($this->newsService->getNewsWithTitle($title));
    }

    public function getFilteredNews($category, $startDate, $endDate){
        $this->view->output($this->newsService->getFilteredNews($category, $startDate, $endDate));
    }

    public function registerUser($username, $password, $confirmPassword){
        $this->view->output($this->userService->registerUser($username, $password, $confirmPassword));
    }

    public function deleteNews($title, $username){
        $user = $this->userService->getUser($username);
        if($user)
            $this->view->output($this->newsService->deleteNews($title, $user));
    }

    public function updateNews($title, $producer, $category, $date, $text){
        $user = $this->userService->getUser($producer);
        if($user)
            $this->view->output($this->newsService->updateNews($title, $user, $category, $date, $text));
    }

    public function changePassword($username, $password, $confirmPassword, $oldPassword){
        $user = $this->userService->getUser($username);
        if($user)
            $this->view->output($this->userService->changePassword($user, $password, $confirmPassword, $oldPassword));
    }

    public function getLoggedUser($username){
        $this->view->output($this->userService->getUser($username));
    }
}

$controller = new Controller();
$controller->service();
?>
