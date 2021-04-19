import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { CreateAccountComponent } from './create-account/create-account.component';
import { ViewNewsComponent } from './view-news/view-news.component';
import {NewsService} from './news.service';
import {HttpClientModule} from '@angular/common/http';
import {FormsModule} from '@angular/forms';
import { ManageNewsComponent } from './manage-news/manage-news.component';
import { ChangePasswordComponent } from './manage-news/change-password/change-password.component';
import { UserNewsComponent } from './manage-news/user-news/user-news.component';

@NgModule({
  declarations: [
    AppComponent,
    CreateAccountComponent,
    ViewNewsComponent,
    ManageNewsComponent,
    ChangePasswordComponent,
    UserNewsComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FormsModule
  ],
  providers: [NewsService],
  bootstrap: [AppComponent]
})
export class AppModule { }
