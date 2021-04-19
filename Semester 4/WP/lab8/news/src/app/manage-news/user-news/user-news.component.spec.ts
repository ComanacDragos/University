import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UserNewsComponent } from './user-news.component';

describe('UserNewsComponent', () => {
  let component: UserNewsComponent;
  let fixture: ComponentFixture<UserNewsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ UserNewsComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(UserNewsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
