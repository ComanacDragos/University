using System;
using System.Collections.Generic;
using System.Text;
using Libraries.Repository;
using Libraries.Domain;
using System.Linq;
using Libraries.Domain.Validator;
using System.Data;
using System.Windows.Forms;

namespace Libraries.Service
{
    public class OneToManyService<ParentId, Parent, ChildId, Child> where Parent: Entity<ParentId> where Child: ChildEntity<ChildId, ParentId>
    {
        DBRepository<ParentId, Parent> parentRepository;
        DBRepository<ChildId, Child> childRepository;
        IValidator<Child> childValidator;

        BindingSource bsParent, bsChild;

        public OneToManyService(DBRepository<ParentId, Parent> parentRepository, DBRepository<ChildId, Child> childRepository, IValidator<Child> childValidator)
        {
            this.parentRepository = parentRepository;
            this.childRepository = childRepository;
            this.childValidator = childValidator;

            DataSet dataSet = new DataSet();
            childRepository.DataSet = dataSet;
            parentRepository.DataSet = dataSet;

            string parentPrimaryKey = parentRepository.Table.Remove(parentRepository.Table.Length - 1) + "Id";

            DataRelation dataRelation = new DataRelation("FK_" + childRepository.Table + "_" + parentRepository.Table,
                dataSet.Tables[parentRepository.Table].Columns[parentPrimaryKey],
                dataSet.Tables[childRepository.Table].Columns[parentPrimaryKey]);
            dataSet.Relations.Add(dataRelation);

            bsParent = new BindingSource();
            bsParent.DataSource = dataSet;
            bsParent.DataMember = parentRepository.Table;

            bsChild = new BindingSource();
            bsChild.DataSource = bsParent;
            bsChild.DataMember = "FK_" + childRepository.Table + "_" + parentRepository.Table;
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

        public BindingSource getParentDataSource()
        {
            return bsParent;
        }

        public BindingSource getChildDataSource()
        {
            return bsChild;
        }

        public void updateChild()
        {
            childRepository.updateDataBase();
        }
    }
}
