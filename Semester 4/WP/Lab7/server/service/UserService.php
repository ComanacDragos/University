<?php
    require_once 'database/UserDB.php';
            
    class UserService{
        private $userDB;
        private $user="";

        public function __construct (){
            $this->userDB = new UserDB();
        }

        public function login($username, $password){
            $resultset = $this->userDB->select($username, $password);
            if(count($resultset) == 1){
                $_SESSION["username"] = $username;
                return TRUE;
            }
            else 
                return FALSE;
        }

        public function getUser(){
            return $this->user;
        }
        
        public function setUser($user){
            return $this->user = $user;
        }
    }
?>