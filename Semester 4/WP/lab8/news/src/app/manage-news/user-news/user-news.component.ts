import {Component, ElementRef, OnInit, ViewChild} from '@angular/core';
import {NewsService} from '../../news.service';
import {News} from '../../news';

@Component({
  selector: 'app-user-news',
  templateUrl: './user-news.component.html',
  styleUrls: ['./user-news.component.scss']
})
export class UserNewsComponent implements OnInit {
  userNews: News[];
  selectedNews: News = {title: '', category: '', date: null, text: '', producer: ''};

  constructor(private newsService: NewsService) { }

  ngOnInit(): void {
    this.getUserNews();
  }

  getUserNews(): void{
    this.newsService.getUserNews()
      .subscribe(result => this.userNews = result);
  }

  clickNewsHandle(title: string): void{
    this.newsService.getNewsWithTitle(title)
      .subscribe(news => this.selectedNews = news[0]);
  }

  addHandle(title: string, category: string, date: string, text: string): void{
    this.newsService.addNews(title, category, date, text)
      .subscribe(result => {
        if (result){
          this.getUserNews();
        }
      });
  }

  deleteHandle(title: string): void{
    this.newsService.deleteNews(title)
      .subscribe(result => {
        if (result[0]){
          this.getUserNews();
        }else{
          alert([result[1]]);
        }
      });
  }

  updateHandle(title: string, category: string, date: string, text: string): void{
    this.newsService.updateNews(title, category, date, text)
      .subscribe(result => alert(result[1]));
  }
}
