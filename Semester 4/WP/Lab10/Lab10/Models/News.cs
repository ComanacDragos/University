using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace AspCoreMVCEF.Models
{
	public class News
	{
		[Key]
		public string Title { get; set; }
		public string Producer { get; set; }
		public string Text { get; set; }
		public string Category { get; set; }
		public DateTime Date { get; set; }
	}
}