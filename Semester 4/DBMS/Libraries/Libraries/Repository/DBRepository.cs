﻿using Libraries.Domain;
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
        public DBRepository(string dbServer, string db, string table)
        {
            dbConnection = new SqlConnection();
            dbConnection.ConnectionString = "Data Source = " + dbServer + ";" +
                "Initial Catalog = " + db + "; Integrated Security = SSPI";
            this.table = table;
        }

        private void SetupData()
        {
            dataSet = new DataSet();
            dataAdapter = new SqlDataAdapter("SELECT * FROM " + table, dbConnection);
            dataAdapter.Fill(dataSet, table);
        }

        public virtual DataTable getTable()
        {
            SetupData();
            return dataSet.Tables[table];
        }

        public virtual IEnumerable<E> FindAll()
        {
            List<E> entities = new List<E>();
            SetupData();
        
            return from dataRow in dataSet.Tables[table].AsEnumerable() select ExtractEntity(dataRow);
        }

        public virtual E FindOne(ID id)
        {
            SetupData();
            return (from dataRow in dataSet.Tables[table].AsEnumerable() where dataRow[0].Equals(id) select ExtractEntity(dataRow)).First();
        }
        public virtual void Add(E entity)
        {
            SetupData();
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapter);

            dataSet.Tables[table].Rows.Add(CreateDataRow(entity));

            builder.GetInsertCommand();
            try
            {
                dataAdapter.Update(dataSet, table);
            }
            catch (SqlException exc)
            {
                throw new MyException(exc.Message);
            }
            
        }
        public virtual E Remove(ID id)
        {
            SetupData();
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapter);
          
            DataRow dataRow = dataSet.Tables[table].Select(dataSet.Tables[table].Columns[0] + " = " + id).FirstOrDefault();

            if(dataRow == null)
            {
                throw new MyException("Invalid id for remove");
            }

            E entity = ExtractEntity(dataRow);
            dataRow.Delete();

            builder.GetDeleteCommand();
            try
            {
                dataAdapter.Update(dataSet, table);
            }
            catch (SqlException exc)
            {
                throw new MyException(exc.Message);
            }
            return entity;
        }

        public virtual void Update(E entity)
        {
            SetupData();
            SqlCommandBuilder builder = new SqlCommandBuilder(dataAdapter);

            DataRow dataRow = dataSet.Tables[table].Select(dataSet.Tables[table].Columns[0] + " = " + entity.Id).FirstOrDefault();

            if (dataRow == null)
            {
                throw new MyException("Invalid id for update");
            }

            dataRow.ItemArray = CreateDataRow(entity).ItemArray;

            builder.GetUpdateCommand();
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