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
            String database = ConfigurationManager.AppSettings.Get("database");
            String server = ConfigurationManager.AppSettings.Get("server");
            String parentTable = ConfigurationManager.AppSettings.Get("parentTable");
            String childTable = ConfigurationManager.AppSettings.Get("childTable");

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Libraries libraries = new Libraries();
            TitlesDBRepository repoTitles = new TitlesDBRepository(server, database);
            CharactersDBRepository repoCharacters = new CharactersDBRepository(server, database);

            OneToManyService<int, Title, int, Character> service = new OneToManyService<int, Title, int, Character>(repoTitles, repoCharacters, new CharacterValidator());
            libraries.MyService = service;
 
            Application.Run(libraries);
        }
    }
}
