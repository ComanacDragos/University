using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using Libraries.Service;
using Libraries.Repository;
using Libraries.Domain;
using Libraries.Domain.Validator;
using System.Configuration;
using System.Collections.Specialized;

namespace Libraries
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            string database = ConfigurationManager.AppSettings.Get("database");
            string server = ConfigurationManager.AppSettings.Get("server");
            string parentTable = ConfigurationManager.AppSettings.Get("parentTable");
            string childTable = ConfigurationManager.AppSettings.Get("childTable");
            string parentPrimaryKey = ConfigurationManager.AppSettings.Get("parentPrimaryKey");

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Libraries libraries = new Libraries(parentTable, childTable);

            DBRepository parentRepo = new DBRepository(server, database, parentTable);
            DBRepository childRepo = new DBRepository(server, database, childTable);

            OneToManyService service = new OneToManyService(parentRepo, childRepo, parentPrimaryKey);
            libraries.MyService = service;
 
            Application.Run(libraries);
        }
    }
}
