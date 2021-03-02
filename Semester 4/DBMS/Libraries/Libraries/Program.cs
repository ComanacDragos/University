using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using Libraries.Service;
using Libraries.Repository;
using Libraries.Domain;
using Libraries.Domain.Validator;

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
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Libraries libraries = new Libraries();
            TitlesDBRepository repoTitles = new TitlesDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");
            CharactersDBRepository repoCharacters = new CharactersDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");

            OneToManyService<int, Title, int, Character> service = new OneToManyService<int, Title, int, Character>(repoTitles, repoCharacters, new CharacterValidator());
            libraries.MyService = service;
            Application.Run(libraries);
        }
    }
}
