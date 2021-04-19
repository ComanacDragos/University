import { Component } from '@angular/core';
import {NewsService} from './news.service';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.scss']
})
export class AppComponent {
  title = 'Welcome';
  showCreateAccount = false;
  showViewNews = false;
  userToken = '';
  constructor(private newsService: NewsService) { }

  OnClickShowCreateAccount(): void {
    this.showCreateAccount = !this.showCreateAccount;
    if (this.showCreateAccount){
      this.showViewNews = false;
    }
  }

  OnClickShowViewNews(): void {
    this.showViewNews = !this.showViewNews;
    if (this.showViewNews){
      this.showCreateAccount = false;
    }
  }

  login(username: string, password: string): void{
    this.newsService.login(username, password)
      .subscribe(result => {
        if (result) {
          sessionStorage.setItem('userToken', result);
          this.userToken = result;
        }
        else {
          sessionStorage.setItem('userToken', '');
          this.userToken = '';
          alert('Invalid credentials');
        }
      });
  }
}
