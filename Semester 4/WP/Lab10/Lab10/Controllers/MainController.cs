using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using AspCoreMVCEF.Data;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Http;
using AspCoreMVCEF.Models;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;


namespace Lab10.Controllers
{
    public class MainController : Controller
    {
        private readonly DBContext _context;

        public MainController(DBContext context)
        {
            _context = context;
        }
        public IActionResult Index()
        {
            return View("Login");
        }

        public IActionResult Login(string username, string password)
        {
            List<User> users = _context.Users.Where(user =>
                user.Username.Equals(username) &&
                user.Password.Equals(password)).ToList();
            if (users.Count().Equals(0))
            {
                return View("FailLogin");
            }
         
            HttpContext.Session.SetString("user", JsonSerializer.Serialize(users[0]));
            return Redirect("/Main/News");
        }

        public IActionResult News()
        {
            string userStr = HttpContext.Session.GetString("user");
            if (userStr == null)
                return Redirect("/Main");
            return View("News");
        }

        public IActionResult Logout()
        {
            HttpContext.Session.Remove("user");
            return Redirect("/Main");
        }

        public IActionResult ManageNews()
        {
            string userStr = HttpContext.Session.GetString("user");
            if (userStr == null)
                return Redirect("/Main");
            return View("ManageNews");
        }

        public IActionResult ViewNews()
        {
            return View("ViewNews");
        }
        public IActionResult ChangePassword()
        {
            return View("ChangePassword");
        }

        public string UpdatePassword(string newPassword, string confirmPassword, string oldPassword)
        {
            User user = JsonSerializer.Deserialize<User>(HttpContext.Session.GetString("user"));

            if (newPassword == null)
                return "New passsword must not be empty";
            if (confirmPassword == null)
                return "Confirm password must not be empty";
            if (oldPassword == null)
                return "Old Password must not be empty";

            if (newPassword.Equals(confirmPassword))
            {
                if (oldPassword.Equals(user.Password))
                {
                    try
                    {
                        User updatedUser = new User() { Username = user.Username, Password = newPassword };
                        _context.Users.Update(updatedUser);
                        _context.SaveChanges();
                        HttpContext.Session.SetString("user", JsonSerializer.Serialize(updatedUser));
                        return "Password updated";
                    }
                    catch (Exception exc)
                    {
                        return "Password was not updated";
                    }
                }
                else
                {
                    return "Old password is not correct";
                }
               
            }
            else
            {
                return "Password and confirm password must be equal";
            }
        }

        public List<News> GetNews(string category, DateTime startDate, DateTime endDate)
        {
            DateTime defaultDate = new DateTime();
            List<News> news = _context.News.ToList();
            if (category != null)
                news = news.Where(news => news.Category.Equals(category)).ToList();

            if (!endDate.Equals(defaultDate) && !startDate.Equals(defaultDate))
                news = news.Where(news => 
                news.Date.CompareTo(startDate) > 0
                && news.Date.CompareTo(endDate) < 0).ToList();

            return news.OrderByDescending(news => news.Date).ToList();
        }

        public List<string> GetTitlesOfUser()
        {
            string userStr = HttpContext.Session.GetString("user");
            if (userStr == null)
                return new List<String>();
            User user = JsonSerializer.Deserialize<User>(userStr);
            
            return _context.News
                .Where(news => news.Producer.Equals(user.Username))
                .Select(news => news.Title)
                .ToList();
        }

        public News GetNewsWithTitle(string title)
        {
            string userStr = HttpContext.Session.GetString("user");
            if (userStr == null)
                return new News();
            User user = JsonSerializer.Deserialize<User>(userStr);

            return _context.News
                .Where(news => news.Producer.Equals(user.Username) && news.Title.Equals(title))
                .First();
        }

        public IActionResult CreateAccount()
        {
            return View("CreateAccount");
        }

        public string SaveAccount(string username, string password, string confirmPassword)
        {
            if (username == null)
                return "Username must not be empty";
            if (password == null)
                return "Password must not be empty";
            if (confirmPassword == null)
                return "Confirm Password must not be empty";

            if (password.Equals(confirmPassword))
            {
                try
                {
                    _context.Users.Add(new User() { Username = username, Password = password });
                    _context.SaveChanges();
                    return "Account created";
                }
                catch(Exception exc)
                {
                    return "Username is taken";
                }
            }
            else
            {
                return "Password and confirm password must be equal";
            }
        }

        public string AddNews(string title, string category, DateTime date, string text)
        {
            User user = JsonSerializer.Deserialize<User>(HttpContext.Session.GetString("user"));
            News news = new News()
            {
                Title = title,
                Producer = user.Username,
                Category = category,
                Date = date,
                Text = text
            };

            try
            {
                _context.News.Add(news);
                _context.SaveChanges();
                return "Added news";
            }
            catch(Exception exc)
            {
                return "Bad title";
            }
        }

        public string DeleteNews(string title)
        {
            User user = JsonSerializer.Deserialize<User>(HttpContext.Session.GetString("user"));
            News news = new News()
            {
                Title = title,
                Producer = user.Username,
            };
            try
            {
                _context.Remove(
                   _context.News.Single(news => news.Title.Equals(title) && news.Producer.Equals(user.Username))
                ); 
                _context.SaveChanges();
                return "Deleted news";
            }
            catch (Exception exc)
            {
                return "Bad title";
            }
        }

        public string UpdateNews(string title, string category, DateTime date, string text)
        {
            User user = JsonSerializer.Deserialize<User>(HttpContext.Session.GetString("user"));
            News news = new News()
            {
                Title = title,
                Producer = user.Username,
                Category = category,
                Date = date,
                Text = text
            };

            try
            {
                _context.News.Update(news);
                _context.SaveChanges();
                return "Updated news";
            }
            catch (Exception exc)
            {
                return "Bad title";
            }
        }
    }
}