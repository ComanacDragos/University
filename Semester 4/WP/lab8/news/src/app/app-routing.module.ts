import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import {ManageNewsComponent} from './manage-news/manage-news.component';
import {ChangePasswordComponent} from './manage-news/change-password/change-password.component';
import {UserNewsComponent} from './manage-news/user-news/user-news.component';
import {ViewNewsComponent} from './view-news/view-news.component';

const routes: Routes = [
  {path: 'manage-news', component: ManageNewsComponent},
  {path: 'manage-news/change-password', component: ChangePasswordComponent},
  {path: 'manage-news/user-news', component: UserNewsComponent},
  {path: 'view-news', component: ViewNewsComponent}
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
