using System;
using System.Windows.Forms;
using Libraries.Service;
using Libraries.Exceptions;

namespace Libraries
{
    public partial class Libraries : Form
    {
        public OneToManyService MyService { get; set; }
        private string ParentTable, ChildTable;

        public Libraries(string parentTable, string childTable)
        {
            InitializeComponent();
            ParentTable = parentTable;
            ChildTable = childTable;
        }

        private void Libraries_Load(object sender, EventArgs e)
        {
            parentGridVIew.DataSource = MyService.getParentDataSource();
            childGridView.DataSource = MyService.getChildDataSource();

            parentLabel.Text = ParentTable;
            childLabel.Text = ChildTable;

            updateParentButton.Text = "Update " + ParentTable;
            updateChildButton.Text = "Update " + ChildTable;
        }

        private void updateParentButton_Click(object sender, EventArgs e)
        {
            try
            {
                MyService.updateParent();

                MessageBox.Show("DB updated", "Success");
            }
            catch (MyException exc)
            {
                MessageBox.Show(exc.Message, "Could not update table");
            }
        }

        private void updateChildButton_Click(object sender, EventArgs e)
        {
            try
            {
                MyService.updateChild();

                MessageBox.Show("DB updated", "Success");
            }
            catch (MyException exc)
            {
                MessageBox.Show(exc.Message, "Could not update table");
            }
        }
    }
}