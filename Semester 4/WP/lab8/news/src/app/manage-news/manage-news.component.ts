import {Component, Input, OnInit} from '@angular/core';
import {NewsService} from '../news.service';
import {Router} from '@angular/router';

@Component({
  selector: 'app-manage-news',
  templateUrl: './manage-news.component.html',
  styleUrls: ['./manage-news.component.scss']
})
export class ManageNewsComponent implements OnInit {
  username: string;

  constructor(private newsService: NewsService, router: Router) {
    router.navigate(['/view-news']).then();
  }

  ngOnInit(): void {
    this.newsService.getUsername(sessionStorage.getItem('userToken'))
      .subscribe(result => this.username = result);
  }

}
