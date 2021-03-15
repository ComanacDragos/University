using Libraries.Domain;
using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SqlClient;
using System.Data;
using System.Linq;
using Libraries.Exceptions;

namespace Libraries.Repository
{
    public abstract class DBRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
    {
        protected SqlConnection dbConnection;
        protected string table;
        protected DataSet dataSet;
        protected SqlDataAdapter dataAdapter;
        SqlCommandBuilder builder;

        public DBRepository(string dbServer, string db, string table)
        {
            dbConnection = new SqlConnection();
            dbConnection.ConnectionString = "Data Source = " + dbServer + ";" +
                "Initial Catalog = " + db + "; Integrated Security = SSPI";
            this.table = table;

            dataSet = new DataSet();
            dataAdapter = new SqlDataAdapter("SELECT * FROM " + table, dbConnection);
            builder = new SqlCommandBuilder(dataAdapter);
            dataAdapter.Fill(dataSet, table);
        }

        public virtual DataTable getTable()
        {
            return dataSet.Tables[table];
        }

        public virtual IEnumerable<E> FindAll()
        {
            List<E> entities = new List<E>();
        
            return from dataRow in dataSet.Tables[table].AsEnumerable() select ExtractEntity(dataRow);
        }

        public virtual E FindOne(ID id)
        {
            return (from dataRow in dataSet.Tables[table].AsEnumerable() where dataRow[0].Equals(id) select ExtractEntity(dataRow)).First();
        }
        public virtual void Add(E entity)
        {
            dataSet.Tables[table].Rows.Add(CreateDataRow(entity));   
        }
        public virtual E Remove(ID id)
        {
            
            DataRow dataRow = dataSet.Tables[table].Select(dataSet.Tables[table].Columns[0] + " = " + id).FirstOrDefault();

            if(dataRow == null)
            {
                throw new MyException("Invalid id for remove");
            }

            E entity = ExtractEntity(dataRow);
            dataRow.Delete();
            return entity;
        }

        public virtual void Update(E entity)
        {
            DataRow dataRow = dataSet.Tables[table].Select(dataSet.Tables[table].Columns[0] + " = " + entity.Id).FirstOrDefault();

            if (dataRow == null)
            {
                throw new MyException("Invalid id for update");
            }

            dataRow.ItemArray = CreateDataRow(entity).ItemArray;
        }

       public void updateDataBase()
        {
            try
            {
                dataAdapter.Update(dataSet, table);
            }
            catch (SqlException exc)
            {
                throw new MyException(exc.Message);
            }
        }

        protected abstract E ExtractEntity(DataRow dataRow);

        protected abstract DataRow CreateDataRow(E entity);
    }
}
