using Library.Domain;
using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;
using System.Data;
using System.Linq;

namespace Library.Repository
{
    abstract class DBRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
    {
        protected SqlConnection dbConnection;
        protected string table;

        public DBRepository(string dbServer, string db, string table)
        {
            dbConnection = new SqlConnection();
            dbConnection.ConnectionString = "Data Source = " + dbServer + ";" +
                "Initial Catalog = " + db + "; Integrated Security = SSPI";
            this.table = table;

        }

        public IEnumerable<E> FindAll()
        {
            List<E> entities = new List<E>();
            DataSet dataSet = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter("SELECT * FROM " + table, dbConnection);
    
            dataAdapter.Fill(dataSet, table);
        
            return from dataRow in dataSet.Tables[table].AsEnumerable() select extractEntity(dataRow);
        }

        public E FindOne(ID id)
        {
            DataSet dataSet = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter("SELECT * FROM " + table, dbConnection);

            dataAdapter.Fill(dataSet, table);
           
            return (from dataRow in dataSet.Tables[table].AsEnumerable() where dataRow[0].Equals(id) select extractEntity(dataRow)).First();
        }
        public E Add(E entity)
        {
            throw new NotImplementedException();
        }
        public E Remove(ID id)
        {
            throw new NotImplementedException();
        }

        public E Update(E entity)
        {
            throw new NotImplementedException();
        }

        protected abstract E extractEntity(DataRow dataRow);

        protected abstract DataRow createDataRow(E entity);
    }
}
