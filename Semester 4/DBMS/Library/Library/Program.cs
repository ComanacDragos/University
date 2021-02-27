using System;
using Library.Repository;
using Library.Domain;
using Library.Service;
using Library.Domain.Validator;

namespace Library
{
    class Program
    {
        static void Main(string[] args)
        {
            //testRepo();
            testService();
        }   

        static void testService()
        {
            TitlesDBRepository repoTitles = new TitlesDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");
            CharactersDBRepository repoCharacters = new CharactersDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");

            OneToManyService<int, Title, int, Character> service = new OneToManyService<int, Title, int, Character>(repoTitles, repoCharacters, new CharacterValidator());

            foreach (Title title in service.GetParents())
                Console.WriteLine(title);
            Console.WriteLine();

            foreach (Character character in service.GetRecordsForParentId(1))
                Console.WriteLine(character);
            Console.WriteLine();

            service.Add(new Character(4, 2, "char1", "Primary"));

            foreach (Character character in service.GetRecordsForParentId(2))
                Console.WriteLine(character);
            Console.WriteLine();

            service.Update(new Character(4, 2, "char1 updated", "Secondary"));

            foreach (Character character in service.GetRecordsForParentId(2))
                Console.WriteLine(character);
            Console.WriteLine();

            service.Remove(4);

            foreach (Character character in service.GetRecordsForParentId(2))
                Console.WriteLine(character);
            Console.WriteLine();
        }

        static void testRepo()
        {
            TitlesDBRepository repoTitles = new TitlesDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");
            CharactersDBRepository repoCharacters = new CharactersDBRepository("DESKTOP-E94DLUN\\SQLEXPRESS", "Libraries");


            foreach (Title title in repoTitles.FindAll())
                Console.WriteLine(title);

            Console.WriteLine();

            foreach (Character character in repoCharacters.FindAll())
                Console.WriteLine(character);

            Console.WriteLine("\n" + repoTitles.FindOne(2) + "\n");

            repoTitles.Add(new Title(7, "newTitle7"));

            foreach (Title title in repoTitles.FindAll())
                Console.WriteLine(title);

            Console.WriteLine("\n" + repoTitles.Remove(7) + "\n");

            foreach (Title title in repoTitles.FindAll())
                Console.WriteLine(title);

            try
            {
                //repoTitles.Add(new Title(1, "newTitle7"));
                repoTitles.Remove(-1);
            }
            catch(Exception exc)
            {
                Console.WriteLine("Exception caught: " + exc.Message);
            }

            repoTitles.Update(new Title(6, "newTitle6 updated2"));

            foreach (Title title in repoTitles.FindAll())
                Console.WriteLine(title);
        }
    }
}
