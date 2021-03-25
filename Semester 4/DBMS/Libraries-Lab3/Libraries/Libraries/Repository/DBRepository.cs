using System.Data.SqlClient;
using System.Data;
using System.Linq;
using Libraries.Exceptions;

namespace Libraries.Repository
{
    public class DBRepository
    {
        protected SqlConnection dbConnection;
        public string Table { get; }

        private DataSet dataSet;
        public DataSet DataSet { 
            get
            {
                return dataSet;
            }
            set
            {
                dataSet = value;
                dataAdapter.Fill(dataSet, Table);
            } 
        }

        protected SqlDataAdapter dataAdapter;

        public DBRepository(string dbServer, string db, string table)
        {
            dbConnection = new SqlConnection();
            dbConnection.ConnectionString = "Data Source = " + dbServer + ";" +
                "Initial Catalog = " + db + "; Integrated Security = SSPI";
            this.Table = table;


            dataAdapter = new SqlDataAdapter("SELECT * FROM " + table, dbConnection);
            DataSet = new DataSet();
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapter);
        }
       public void updateDataBase()
        {
            try
            {
                dataAdapter.Update(DataSet, Table);
            }
            catch (SqlException exc)
            {
                (from dataRow in dataSet.Tables[Table].AsEnumerable()
                 where dataRow.HasErrors
                 select dataRow)
                .ToList().ForEach(row => dataSet.Tables[Table].Rows.Remove(row));
                throw new MyException(exc.Message);
            }
        }
    }
}
