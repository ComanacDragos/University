using System.Data;
using Libraries.Domain;
using System.Data.SqlClient;

namespace Libraries.Repository
{
    public class TitlesDBRepository : DBRepository<int, Title>
    {
        public TitlesDBRepository(string dbServer, string db): base(dbServer, db, "Titles") {}
        protected override Title ExtractEntity(DataRow dataRow)
        {
            return new Title((int)dataRow["TitleId"], (string)dataRow["Title"]);
        }

        protected override DataRow CreateDataRow(Title entity)
        {
            DataRow dataRow = DataSet.Tables[Table].NewRow();
            dataRow["TitleId"] = entity.Id;
            dataRow["Title"] = entity.Name;

            return dataRow;
        }
    }
}
