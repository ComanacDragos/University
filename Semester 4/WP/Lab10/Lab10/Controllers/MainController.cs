using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using AspCoreMVCEF.Data;
using Microsoft.AspNetCore.Mvc;
using AspCoreMVCEF.Models;

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
            ViewData["newsList"] = _context.News.ToList();
            return View("FilterNews");
        }

        public string FilterNews(string category, DateTime startDate, DateTime endDate)
        {
            return "blas";
        }

    }
}