using System;
using System.Collections.Generic;
using System.Data;
using System.Text;
using Libraries.Domain;

namespace Libraries.Repository
{
    public interface IRepository<ID, E> where E : Entity<ID>
    {
        E FindOne(ID id);
        IEnumerable<E> FindAll();
        void Add(E entity);
        E Remove(ID id);
        void Update(E entity);
        DataTable getTable();
    }
}
