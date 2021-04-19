import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Observable, of } from 'rxjs';
import { catchError, map, tap } from 'rxjs/operators';
import {News} from './news';
@Injectable({
  providedIn: 'root'
})
export class NewsService {
  private backendUrl = 'http://localhost:3000/lab8/server/controller.php';
  httpOptions = {
    headers: new HttpHeaders({
      'Content-Type': 'application/json'
    })
  };

  constructor(private http: HttpClient) { }

  fetchNews(): Observable<News[]> {
    return this.http.get<News[]>(this.backendUrl + '?action=getNews')
      .pipe(catchError(this.handleError<News[]>('fetchNews', []))
      );
  }

  fetchFilteredNews(category: string, startDate: string, endDate: string): Observable<News[]> {
    return this.http.get<News[]>(
      this.backendUrl +
      '?action=getFilteredNews' +
      '&category=' + category +
      '&startDate=' + startDate +
      '&endDate=' + endDate
    )
      .pipe(catchError(this.handleError<News[]>('fetchFilteredNews', []))
      );
  }

  registerUser(username: string, password: string, confirmPassword: string): Observable<string>{
    return this.http.get<string>(
      this.backendUrl +
      '?action=registerUser' +
      '&username=' + username +
      '&password=' + password +
      '&confirmPassword=' + confirmPassword
    )
      .pipe(catchError(this.handleError<string>('registerUser', 'error'))
      );
  }

  login(username: string, password: string): Observable<string>{
    return this.http.get<string>(
      this.backendUrl +
      '?action=login' +
      '&username=' + username +
      '&password=' + password
    )
      .pipe(catchError(this.handleError<string>('login', 'error'))
      );
  }

  getUsername(userToken: string): Observable<string>{
    return this.http.get<string>(
      this.backendUrl +
      '?action=getLoggedUser' +
      '&username=' + userToken
    )
      .pipe(catchError(this.handleError<string>('getUsername', 'error'))
      );
  }

  changePassword(password: string, confirmPassword: string, oldPassword: string): Observable<string>{
    return this.http.get<string>(
      this.backendUrl +
      '?action=changePassword' +
      '&username=' + sessionStorage.getItem('userToken') +
      '&password=' + password +
      '&confirmPassword=' + confirmPassword +
      '&oldPassword=' + oldPassword
    )
      .pipe(catchError(this.handleError<string>('changePassword', 'error'))
      );
  }

  getUserNews(): Observable<News[]>{
    return this.http.get<News[]>(
      this.backendUrl +
      '?action=getUserNews' +
      '&username=' + sessionStorage.getItem('userToken')
    )
      .pipe(catchError(this.handleError<News[]>('getUserNews', []))
      );
  }

  getNewsWithTitle(title: string): Observable<News>{
    return this.http.get<News>(
      this.backendUrl +
      '?action=getNewsWithTitle' +
      '&title=' + title
    )
      .pipe(catchError(this.handleError<News>('getNewsWithTitle', null))
      );
  }

  addNews(title: string, category: string, date: string, text: string): Observable<string>{
    return this.http.get<string>(
      this.backendUrl +
      '?action=addNews' +
      '&username=' + sessionStorage.getItem('userToken') +
      '&title=' + title +
      '&category=' + category +
      '&date=' + date +
      '&text=' + text
    )
      .pipe(catchError(this.handleError<string>('addNews', ''))
      );
  }

  deleteNews(title: string): Observable<string>{
    return this.http.get<string>(
      this.backendUrl +
      '?action=deleteNews' +
      '&username=' + sessionStorage.getItem('userToken') +
      '&title=' + title
    )
      .pipe(catchError(this.handleError<string>('deleteNews', ''))
      );
  }

  updateNews(title: string, category: string, date: string, text: string): Observable<string>{
    return this.http.get<string>(
      this.backendUrl +
      '?action=updateNews' +
      '&username=' + sessionStorage.getItem('userToken') +
      '&title=' + title +
      '&category=' + category +
      '&date=' + date +
      '&text=' + text
    )
      .pipe(catchError(this.handleError<string>('updateNews', ''))
      );
  }
  /**
   * Handle Http operation that failed.
   * Let the app continue.
   * @param operation - name of the operation that failed
   * @param result - optional value to return as the observable result
   */
  // tslint:disable-next-line:typedef
  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {

      // TODO: send the error to remote logging infrastructure
      console.error(error); // log to console instead

      // Let the app keep running by returning an empty result.
      return of(result as T);
    };
  }
}
