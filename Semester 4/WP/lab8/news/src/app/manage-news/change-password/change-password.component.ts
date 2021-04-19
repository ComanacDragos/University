import {Component, OnInit, Output} from '@angular/core';
import {NewsService} from '../../news.service';

@Component({
  selector: 'app-change-password',
  templateUrl: './change-password.component.html',
  styleUrls: ['./change-password.component.scss']
})
export class ChangePasswordComponent implements OnInit {
  changePasswordStatus: string;
  constructor(private newsService: NewsService) { }

  ngOnInit(): void {
  }

  changePassword(password: string, confirmPassword: string, oldPassword: string): void{
    this.newsService.changePassword(password, confirmPassword, oldPassword)
      .subscribe(result => {
          if (result[0]){
            sessionStorage.setItem('userToken', result[1]);
            this.changePasswordStatus = 'Password updated!';
          }else{
            this.changePasswordStatus = result[1];
          }
      });
  }
}
