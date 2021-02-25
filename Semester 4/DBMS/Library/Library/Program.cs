using System;
using Library.Repository;
using Library.Domain;

namespace Library
{
    class Program
    {
        static void Main(string[] args)
        {
            TitlesDBRepository repoTitles = new TitlesDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");
            CharactersDBRepository repoCharacters = new CharactersDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");


            foreach (Title title in repoTitles.FindAll())
                Console.WriteLine(title);

            Console.WriteLine();

            foreach (Character character in repoCharacters.FindAll())
                Console.WriteLine(character);

        }
    }
}
