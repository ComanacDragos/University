using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Libraries.Service;
using Libraries.Domain;

namespace Libraries
{
    public partial class Libraries : Form
    {
        public OneToManyService<int, Title, int, Character> MyService { get; set; }

        public Libraries()
        {
            InitializeComponent();
        }

        private void Libraries_Load(object sender, EventArgs e)
        {
            titlesTable.DataSource = MyService.getParentTable();
            titlesTable.Columns[0].AutoSizeMode = DataGridViewAutoSizeColumnMode.AllCells;
            titlesTable.Columns[1].AutoSizeMode = DataGridViewAutoSizeColumnMode.Fill;
        }

        private void addCharacterHandle(object sender, EventArgs e)
        {
          
        }

        private void deleteCharacterHandle(object sender, EventArgs e)
        {

        }
    }
}
