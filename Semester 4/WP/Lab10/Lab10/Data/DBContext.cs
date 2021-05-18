using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

using Microsoft.EntityFrameworkCore;
using MySQL.Data.EntityFrameworkCore;
using AspCoreMVCEF;
using AspCoreMVCEF.Models;

namespace AspCoreMVCEF.Data
{
	public class DBContext : DbContext
	{
		public DBContext(DbContextOptions options) : base(options)
		{
		}

		public DbSet<User> Users { get; set; }
		public DbSet<News> News { get; set; }
	}
}
