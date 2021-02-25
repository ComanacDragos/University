using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Data.SqlClient;
using System.Data;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            SqlConnection dbConn = new SqlConnection();
            dbConn.ConnectionString = "Data Source = DESKTOP-E94DLUN\\SQLEXPRESS;" +
                "Initial Catalog = Lab1; Integrated Security = SSPI";

            DataSet ds = new DataSet();


            SqlDataAdapter da = new SqlDataAdapter("SELECT * FROM U", dbConn);
            SqlCommandBuilder cb = new SqlCommandBuilder(da);

          
            da.Fill(ds, "U");

            SqlCommand command = new SqlCommand("DELETE FROM U WHERE id = 50", dbConn);

            
            dbConn.Open();
            Console.WriteLine(command.ExecuteNonQuery());
            
            dbConn.Close();
            ds.Clear();
            da.Update(ds, "U");
            da.Fill(ds, "U");

            foreach (DataRow dr in ds.Tables["U"].Rows)
            {
                //Console.WriteLine($"{dr["id"]}. {dr["col1"]}​​");
                int id = (int)dr["id"];
                string col1 = (string)dr["col1"];
                Console.WriteLine($"{id}. {col1}");
            }
            
            DataRow drr = ds.Tables["U"].NewRow();
            drr["id"] = 50;
            drr["col1"] = "Lab1";
            ds.Tables["U"].Rows.Add(drr);

            da.Update(ds, "U");

            Console.WriteLine("\n After first add");
            foreach (DataRow dr in ds.Tables["U"].Rows)
                Console.WriteLine(dr["col1"].ToString());
           
        }
    }
}
