import { Component, OnInit } from '@angular/core';
import {NewsService} from '../news.service';

@Component({
  selector: 'app-create-account',
  templateUrl: './create-account.component.html',
  styleUrls: ['./create-account.component.scss']
})
export class CreateAccountComponent implements OnInit {
  createAccountState = '';

  constructor(private newsService: NewsService) { }

  ngOnInit(): void {
  }

  registerUser(username: string, password: string, confirmPassword: string): void{
      this.newsService.registerUser(username, password, confirmPassword)
        .subscribe(result => this.createAccountState = result);
  }
}
