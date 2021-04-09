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

        public function registerUser($username, $password, $confirmPassword){
            if($username == '')
                return "Username must not be empty";
            if($password == '')
                return "Password must not be empty";
            if($password != $confirmPassword)
                return "Password and confirm password must be the same";
            try{
                $this->userDB->insert($username, $password);
                return "User registered successfuly";
            }
            catch(Exception $e){
                return "Username is taken";
            }
        }

        public function changePassword($username, $password, $confirmPassword, $oldPassword){
            if($username == '')
            return "Username must not be empty";
            if($password == '')
                return "Password must not be empty";
            if($password != $confirmPassword)
                return "Password and confirm password must be the same";
                
            try{
                $this->userDB->update($username, $password, $oldPassword);
                return "Password updated successfuly";
            }
            catch(Exception $e){
                return "Could not update password: $e";
            }
        }
    }
?>