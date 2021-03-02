using System;
using System.Collections.Generic;
using System.Text;
using Libraries.Repository;
using Libraries.Domain;
using System.Linq;
using Libraries.Domain.Validator;
using System.Data;

namespace Libraries.Service
{
    public class OneToManyService<ParentId, Parent, ChildId, Child> where Parent: Entity<ParentId> where Child: ChildEntity<ChildId, ParentId>
    {
        IRepository<ParentId, Parent> parentRepository;
        IRepository<ChildId, Child> childRepository;
        IValidator<Child> childValidator;

        public OneToManyService(IRepository<ParentId, Parent> parentRepository, IRepository<ChildId, Child> childRepository, IValidator<Child> childValidator)
        {
            this.parentRepository = parentRepository;
            this.childRepository = childRepository;
            this.childValidator = childValidator;
        }

        public IEnumerable<Parent> GetParents()
        {
            return parentRepository.FindAll();
        }

        public IEnumerable<Child> GetRecordsForParentId(ParentId parentId)
        {
            return from child in childRepository.FindAll() where child.ParentId.Equals(parentId) select child;
        }

        public void Add(Child child)
        {
            childValidator.Validate(child);
            childRepository.Add(child);
        }

        public Child Remove(ChildId Id)
        {
            return childRepository.Remove(Id);
        }

        public void Update(Child child)
        {
            childValidator.Validate(child);
            childRepository.Update(child);
        }

        public DataTable getParentTable()
        {
            return parentRepository.getTable();
        }
    }
}
