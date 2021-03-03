using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using Libraries.Domain;
using System.Data.SqlClient;

namespace Libraries.Repository
{
    public class CharactersDBRepository : DBRepository<int, Character>
    {
        public CharactersDBRepository(string dbServer, string db) : base(dbServer, db, "Characters") { }
      
        protected override Character ExtractEntity(DataRow dataRow)
        {
            return new Character((int)dataRow["CharacterId"], (int)dataRow["TitleId"], (string)dataRow["FullName"], Character.StringToRole((string)dataRow["CharacterRole"]));
        }
        protected override DataRow CreateDataRow(Character entity)
        {
            DataRow dataRow = dataSet.Tables[table].NewRow();
            dataRow["CharacterId"] = entity.Id;
            dataRow["TitleId"] = entity.TitleId;
            dataRow["FullName"] = entity.FullName;
            dataRow["CharacterRole"] = entity.CharacterRole;

            return dataRow;
        }

    }
}
