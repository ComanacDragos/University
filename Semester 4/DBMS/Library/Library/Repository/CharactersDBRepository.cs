using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using Library.Domain;
using System.Data.SqlClient;

namespace Library.Repository
{
    class CharactersDBRepository : DBRepository<int, Character>
    {
        public CharactersDBRepository(string dbServer, string db) : base(dbServer, db, "Characters") { }
      
        protected override Character extractEntity(DataRow dataRow)
        {
            return new Character((int)dataRow["CharacterId"], (int)dataRow["TitleId"], (string)dataRow["FullName"], (string)dataRow["CharacterRole"]);
        }
        protected override DataRow createDataRow(Character entity)
        {
            DataSet dataSet = new DataSet();
            SqlDataAdapter dataAdapter = new SqlDataAdapter("SELECT * FROM " + table, dbConnection);
            DataRow dataRow = dataSet.Tables[table].NewRow();
            dataRow["CharacterId"] = entity.Id;
            dataRow["TitleId"] = entity.TitleId;
            dataRow["FullName"] = entity.FullName;
            dataRow["CharacterRole"] = entity.CharacterRole;

            return dataRow;
        }

    }
}
