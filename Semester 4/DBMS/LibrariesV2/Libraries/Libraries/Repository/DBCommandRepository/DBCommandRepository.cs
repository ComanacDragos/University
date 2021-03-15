using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Libraries.Domain;
using Libraries.Repository;
using System.Data.SqlClient;

namespace Libraries.Repository.DBCommandRepository
{
    public abstract class DBCommandRepository<ID, E> : IRepository<ID, E> where E : Entity<ID>
    {
        string css;
        string table;
        public DBCommandRepository(string dbServer, string db, string table){
            css = "Data Source = " + dbServer + ";" +
                "Initial Catalog = " + db + "; Integrated Security = SSPI";
            this.table = table;
        }

        public IEnumerable<E> FindAll()
        {
            throw new NotImplementedException();
        }

        public E FindOne(ID id)
        {
            throw new NotImplementedException();
        }

        public DataTable getTable()
        {
            throw new NotImplementedException();
        }
        public void Add(E entity)
        {
            throw new NotImplementedException();
        }

        public E Remove(ID id)
        {
            throw new NotImplementedException();
        }

        public void Update(E entity)
        {
            throw new NotImplementedException();
        }

        public void updateDataBase()
        {
            throw new NotImplementedException();
        }
    }
}
