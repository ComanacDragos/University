import { Component, OnInit } from '@angular/core';
import {News} from '../news';
import {NewsService} from '../news.service';

@Component({
  selector: 'app-view-news',
  templateUrl: './view-news.component.html',
  styleUrls: ['./view-news.component.scss']
})
export class ViewNewsComponent implements OnInit {
  news: News[] = [];
  prevCategory = '';
  prevStartDate = '';
  prevEndDate = '';
  currentCategory = '';
  currentStartDate = '';
  currentEndDate = '';
  constructor(private newsService: NewsService) { }

  ngOnInit(): void {
    this.getNews();
  }

  getNews(): void{
    this.newsService.fetchNews()
      .subscribe(news => this.news = news);
  }

  filterHandle(category: string, startDate: string, endDate: string): void{
    this.prevCategory = this.currentCategory;
    this.prevStartDate = this.currentStartDate;
    this.prevEndDate = this.currentEndDate;
    this.currentCategory = category;
    this.currentStartDate = startDate;
    this.currentEndDate = endDate;
    this.newsService.fetchFilteredNews(category, startDate, endDate)
      .subscribe(filteredNews => {
        this.news = filteredNews;
      });
  }


}
