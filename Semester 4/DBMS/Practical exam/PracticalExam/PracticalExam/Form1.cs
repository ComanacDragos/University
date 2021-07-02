using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace PracticalExam
{
    public partial class Form1 : Form
    {
        SqlDataAdapter coffeProductsDataAdapter;
        DataSet dataSet;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            SqlConnection dbConnection = new SqlConnection();
            dbConnection.ConnectionString = "Data Source = DESKTOP-E94DLUN\\SQLEXPRESS;" +
                "Initial Catalog = PracticalExam; Integrated Security = SSPI";

            coffeProductsDataAdapter = new SqlDataAdapter("SELECT * FROM CoffeProducts", dbConnection);
            SqlDataAdapter categoriesDataAdapter = new SqlDataAdapter("SELECT * FROM Categories", dbConnection);

            dataSet = new DataSet();
            SqlCommandBuilder builder = new SqlCommandBuilder(coffeProductsDataAdapter);

            coffeProductsDataAdapter.Fill(dataSet, "CoffeProducts");
            categoriesDataAdapter.Fill(dataSet, "Categories");

            DataRelation dataRelation = new DataRelation("FK_CoffeProductsCategories",
                   dataSet.Tables["Categories"].Columns["id"],
                   dataSet.Tables["CoffeProducts"].Columns["categoryId"]);
            dataSet.Relations.Add(dataRelation);

            BindingSource bsCategories = new BindingSource()
            {
                DataSource = dataSet,
                DataMember = "Categories"
            };

            BindingSource bsCoffeProducts = new BindingSource
            {
                DataSource = bsCategories,
                DataMember = "FK_CoffeProductsCategories"
            };

            dgvCategories.DataSource = bsCategories ;
            dgvProducts.DataSource = bsCoffeProducts;

            dgvCategories.Columns.Remove("id");
            dgvProducts.Columns.Remove("id");
            dgvProducts.Columns.Remove("categoryId");
        }

        private void updateDatabase_Click(object sender, EventArgs e)
        {
            try
            {
                coffeProductsDataAdapter.Update(dataSet, "CoffeProducts");
                MessageBox.Show("DB updated", "Success");
            }
            catch (SqlException exc)
            {
                (from dataRow in dataSet.Tables["CoffeProducts"].AsEnumerable()
                 where dataRow.HasErrors
                 select dataRow)
                .ToList().ForEach(row => dataSet.Tables["CoffeProducts"].Rows.Remove(row));
                MessageBox.Show(exc.Message, "Could not update table");
            }
        }
    }
}
