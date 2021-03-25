using Libraries.Repository;
using System.Data;
using System.Windows.Forms;

namespace Libraries.Service
{
    public class OneToManyService
    {
        DBRepository parentRepository;
        DBRepository childRepository;
        
        BindingSource bsParent, bsChild;

        public OneToManyService(DBRepository parentRepository, DBRepository childRepository, string parentPrimaryKey)
        {
            this.parentRepository = parentRepository;
            this.childRepository = childRepository;

            DataSet dataSet = new DataSet();
            childRepository.DataSet = dataSet;
            parentRepository.DataSet = dataSet;

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

        public void updateParent()
        {
            parentRepository.updateDataBase();
        }
    }
}
