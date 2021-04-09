<?php
    require_once 'database/NewsDB.php';
            
    class NewsService{
        private $newsDB;

        public function __construct (){
            $this->newsDB = new NewsDB();
        }

        public function getAllNews(){
            return $this->newsDB->select();
        }

        public function addNews($title, $producer, $category, $date, $text){
            if($title == "")
                return FALSE;
            if($this->newsDB->insert($title, $producer, $category, $date, $text) == 0)
                return FALSE;
            return TRUE;
        }

        public function getUserNews($producer){
            return $this->newsDB->selectNewsWithProducer($producer);
        }

        public function getNewsWithTitle($title){
            return $this->newsDB->selectNewsWithTitle($title);
        }

        public function getFilteredNews($category, $startDate, $endDate){
            return $this->newsDB->filterNews($category, $startDate, $endDate);
        }

        public function deleteNews($title, $username){
            if($this->newsDB->delete($title, $username) == 0)
                return array(FALSE, "Could not delete news");
            return array(TRUE, "News deleted");
        }

        public function updateNews($title, $producer, $category, $date, $text){
            if($this->newsDB->update($title, $producer, $category, $date, $text) == 0)
                return array(FALSE, "Could not update news");
            return array(TRUE, "News updated");
        }
    }
?>