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
    }
?>