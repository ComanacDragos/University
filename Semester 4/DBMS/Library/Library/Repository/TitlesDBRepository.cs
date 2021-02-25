using System.Data;
using Library.Domain;
using System.Data.SqlClient;

namespace Library.Repository
{
    class TitlesDBRepository : DBRepository<int, Title>
    {
        public TitlesDBRepository(string dbServer, string db): base(dbServer, db, "Titles") {}
        protected override Title extractEntity(DataRow dataRow)
        {
            return new Title((int)dataRow["TitleId"], (string)dataRow["Title"]);
        }

        protected override DataRow createDataRow(Title entity)
        {
            DataSet dataSet = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter("SELECT * FROM " + table, dbConnection);
            DataRow dataRow = dataSet.Tables[table].NewRow();
            dataRow["TitleId"] = entity.Id;
            dataRow["Title"] = entity.Name;

            return dataRow;
        }
    }
}
