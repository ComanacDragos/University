<?php 
    require_once 'DBUtils.php';

    class UserDB extends DBUtils{
		public function select($user, $password) {
			$stmt = $this->pdo->query("SELECT * FROM users WHERE username='$user' AND password='$password'");
			return $stmt->fetchAll(PDO::FETCH_ASSOC);
		}	

		public function insert($username, $password) {
			$affected_rows = $this->pdo->exec("INSERT into users values('" . $username . "','" . $password ."');");
			return $affected_rows;
		}

		/*
		public function delete ($id) {
			$affected_rows = $this->pdo->exec("DELETE from table where id=" . $id);
			return $affected_rows;
		}
		*/

		public function update ($username, $password, $oldPassword) {
			return $this->pdo->exec("UPDATE users SET password='$password' WHERE username='$username' and password='$oldPassword'");
		}
	}
?>