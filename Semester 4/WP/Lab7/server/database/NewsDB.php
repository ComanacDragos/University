<?php 
    require_once 'DBUtils.php';

    class NewsDB extends DBUtils{
		public function select() {
			$stmt = $this->pdo->query("SELECT * FROM news ORDER BY date DESC");
			return $stmt->fetchAll(PDO::FETCH_ASSOC);
		}	

		
		public function insert($title, $producer, $category, $date, $text) {
			try{
				$affected_rows = $this->pdo->exec("INSERT INTO news (title, producer, category, date, text) values('$title', '$producer', '$category', '$date', '$text');");
				return $affected_rows;
			}
			catch(Exception $e){
				return 0;
			}	
		}

		public function selectNewsWithProducer($producer){
			$stmt = $this->pdo->query("SELECT * FROM news WHERE producer='$producer' ORDER BY date DESC");
			return $stmt->fetchAll(PDO::FETCH_ASSOC);
		}

		public function selectNewsWithTitle($title){
			$stmt = $this->pdo->query("SELECT * FROM news WHERE title='$title' ORDER BY date DESC");
			return $stmt->fetchAll(PDO::FETCH_ASSOC);
		}

		public function filterNews($category, $startDate, $endDate){
			$condition = "";
			if($category != ""){
				$condition .= " category='$category'";
			}

			if($startDate != "" and $endDate != ""){
				if($condition != ""){
					$condition .= " AND";
				}
				$condition .= " date between '$startDate' AND '$endDate'" ;
			}
			if($condition == ""){
				return $this->select();
			}
			$stmt = $this->pdo->query("SELECT * FROM news WHERE $condition ORDER BY date DESC");
			return $stmt->fetchAll(PDO::FETCH_ASSOC);
		}
		/*
		public function delete ($id) {
			$affected_rows = $this->pdo->exec("DELETE from table where id=" . $id);
			return $affected_rows;
		}

		public function update ($id, $value) {
			$affected_rows = $this->pdo->exec("UPDATE table SET field='" . $value ."' where id=" . $id);

		}*/
	}
?>