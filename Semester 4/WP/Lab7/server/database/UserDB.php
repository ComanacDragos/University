<?php 
    require_once 'DBUtils.php';

    class UserDB extends DBUtils{
		public function select($user, $password) {
			$stmt = $this->pdo->query("SELECT * FROM users WHERE username='$user' AND password='$password'");
			return $stmt->fetchAll(PDO::FETCH_ASSOC);
		}	

		/*
		public function insert($id, $value) {
			$affected_rows = $this->pdo->exec("INSERT into table values(" . $id . ",'" . $value ."');");
			return $affected_rows;
		}

		public function delete ($id) {
			$affected_rows = $this->pdo->exec("DELETE from table where id=" . $id);
			return $affected_rows;
		}

		public function update ($id, $value) {
			$affected_rows = $this->pdo->exec("UPDATE table SET field='" . $value ."' where id=" . $id);

		}*/
	}
?>