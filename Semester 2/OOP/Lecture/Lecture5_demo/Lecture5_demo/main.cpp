#include "Penguin.h"
#include "Dog.h"
#include <Windows.h>
#include <iostream>
#include <crtdbg.h>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

void showAnimal(Animal a)
{
	cout << a.toString() << endl;
}

void showDog(Dog d)
{
	cout << d.toString() << endl;
}

void substitutionPrinciple()
{
	Penguin penguin{ "black and white", 10, "Magellanic" };
	Dog dog{ "brown", 20, "Labrador Retriever", 2.5 };

	Animal animal{ "green", 0.2 };
	showAnimal(animal);

	animal = penguin;		// implicit upcast
	showAnimal(penguin);	// implicit upcast
	showAnimal(dog);		// implicit upcast
	cout << endl;

	//dog = animal;	// error!
	//showDog(animal); // error !
}

void pointersAndInheritance()
{
	Animal* animal = new Animal{ "black", 65 };
	cout << animal->toString() << endl;

	Penguin* penguin = new Penguin{ "black and white", 12, "Imperial" };
	animal = penguin;	// this is allowed;
						// In this particular case, is it correct, or can you identify an error? Hint: look at the deallocation at the end of the function.

	cout << animal->toString() << endl;
	//penguin = animal; //error!

	delete penguin;
	delete animal; // !!! memory error
}

void methodOverriding()
{
	Penguin penguin{ "black and white", 10, "Magellanic" };
	Dog dog{ "brown", 20, "Labrador Retriever", 2.5 };

	cout << penguin.toString() << endl;
	cout << dog.toString() << endl;
}

int bla()
{
	system("color f4");

	Penguin penguin{ "black and white", 10, "Magellanic" };
	// penguin is an animal => we can use any method from the Animal class
	cout << penguin.toString() << endl;
	system("cls");

	// constructing and destructing objects of derived classes
	{
		Penguin penguin{ "black and white", 10, "Magellanic" };
		Dog dog{ "brown", 20, "Labrador Retriever", 2.5 };
		cout << dog.toString();
	}
	system("cls");

	// ---------------------------------------------------------------------------------------------------
	//Substitution principle
	substitutionPrinciple();
	system("cls");
	
	// ---------------------------------------------------------------------------------------------------
	// Pointers and inheritance
	pointersAndInheritance();
	system("cls");

	// ---------------------------------------------------------------------------------------------------
	// Method orverriding
	methodOverriding();
	system("cls");

	system("pause");
	return 0;
}


std::vector<std::string> tokenize(std::string string, const char delimiter)
{
	std::vector<std::string> result;

	std::stringstream stringStream{ string };
	std::string token;

	while (std::getline(stringStream, token, delimiter))
		if (token.size() != 0)
		{
			std::stringstream tokenStringStream{ token };
			while (std::getline(tokenStringStream, token, ' '))
				if (token.size() != 0)
					result.push_back(token);
		}

	return result;
}


std::istream& operator>>(std::istream& istream, Animal& animal)
{
	std::string line;
	std::getline(istream, line);
	std::vector<std::string> tokens = tokenize(line, ',');

	if (tokens.size() != 2) // bad data
		return istream;

	std::string color{ tokens[0] };
	std::string weight{ tokens[1] };
	
	Animal newAnimal { color, stod(weight) };
	animal = newAnimal;

	return istream;
}

std::ostream& operator<<(std::ostream& ostream, const Animal& animal)
{
	ostream << "Animal \n\t weight: " << animal.getWeight() << " kg" << endl << "\t colour: " << animal.getColour() << endl;
	return ostream;
}

std::ostream& operator<<(std::ostream& ostream, const AnimalToCSV& animal)
{
	ostream << animal.getWeight() << ", " << ", " << animal.getColour() << endl;
	return ostream;
}


std::ostream& operator<<(std::ostream& ostream, const Penguin& animal)
{
	ostream << "SDGSGSRGERGERG";
	ostream << "Animal \n\t weight: " << animal.getWeight() << " kg" << endl << "\t colour: " << animal.getColour() <<"\t type: "<<animal.getType()<< endl;
	return ostream;
}


int main()
{
	{
		Animal* animal;
		animal = new Penguin{ "color", 4, "type" };
		std::cout << *(static_cast<Penguin*>(animal));

		Penguin* penguin = new Penguin{ "colr", 5,"asf" };

		std::cout << *(static_cast<Animal*>(penguin));


		Animal animalasd{ "colrasd", 54 };
		std::cout << animalasd;

		std::cout << *(static_cast<AnimalToCSV*>(&animalasd));


		delete animal;
	}


}