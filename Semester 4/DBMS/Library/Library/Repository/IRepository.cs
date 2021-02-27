using System;
using System.Collections.Generic;
using System.Text;
using Library.Domain;

namespace Library.Repository
{
    interface IRepository<ID, E> where E : Entity<ID>
    {
        E FindOne(ID id);
        IEnumerable<E> FindAll();
        void Add(E entity);
        E Remove(ID id);
        void Update(E entity);
    }
}
