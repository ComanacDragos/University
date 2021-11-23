<?php
    require_once 'database/UserDB.php';
            
    class UserService{
        private $userDB;
        private $user="";
        private $ciphering = "AES-128-CTR";
        private $options = 0;
        private $encryption_iv = '1234567891011121';
        private $encryption_key = "PHPLab";

        public function __construct (){
            $this->userDB = new UserDB();
        }

        private function encrypt($string){
            return openssl_encrypt($string, $this->ciphering,
            $this->encryption_key, $this->options, $this->encryption_iv);
        }

        private function decrypt($string){
            return $decryption=openssl_decrypt ($string, $this->ciphering, 
            $this->encryption_key, $this->options, $this->encryption_iv);
        }

        public function getUser($encryption){
            if($encryption == "")
                return "";
            $tokens = explode(";", $this->decrypt($encryption));
            $username = $tokens[0];
            $password = $tokens[1];
            $resultset = $this->userDB->select($username, $password);
            if(count($resultset) == 1){
                return $username;
            }
            else 
                return FALSE;
        }

        public function login($username, $password){
            $resultset = $this->userDB->select($username, $password);
            if(count($resultset) == 1){
                return $this->encrypt($username . ";" . $password);
            }
            else 
                return FALSE;
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
                return array(FALSE, "Username must not be empty");
            if($password == '')
                return array(FALSE, "Password must not be empty");
            if($password != $confirmPassword)
                return array(FALSE, "Password and confirm password must be the same");
                
            try{
                if($this->userDB->update($username, $password, $oldPassword) == 1)
                    return array(TRUE, $this->encrypt($username . ";" . $password));
                return array(FALSE, "Old password is wrong");
            }
            catch(Exception $e){
                return array(FALSE, "Could not update password: $e");
            }
        }
    }
?>