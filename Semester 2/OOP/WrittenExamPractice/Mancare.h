#pragma once
#include <iostream>
#include <string>
#include <vector>

class Mancare
{
private:
	int pret;
public:
	Mancare() :pret{ 0 } {}
	Mancare(int pret):pret{pret}{}

	virtual std::string descriere() = 0;

	virtual int getPret()
	{
		return this->pret;
	}

	virtual ~Mancare(){}
};

class CuCartof:public Mancare
{
private:
	Mancare* mancare;
public:

	CuCartof(Mancare* mancare):mancare{mancare}{}
	std::string descriere()override
	{
		return this->mancare->descriere() + " cu cartof";
	}

	int getPret()
	{
		return this->mancare->getPret() + 3;
	}
	virtual ~CuCartof()
	{
		delete this->mancare;
	}
};

class CuSos :public Mancare
{
private:
	Mancare* mancare;
public:

	CuSos(Mancare* mancare) :mancare{ mancare } {}
	std::string descriere()override
	{
		return this->mancare->descriere() + " cu sos";
	}

	int getPret()
	{
		return this->mancare->getPret() + 2;
	}
	virtual ~CuSos()
	{
		delete this->mancare;
	}
};

class Burger: public Mancare
{
private:
	std::string nume;
public:
	Burger(int pret, const std::string& nume):Mancare(pret), nume{nume}{}

	std::string descriere()override
	{
		return this->nume;
	}
};


std::vector<Mancare*> mancare()
{
	std::vector<Mancare*> lista;

	Mancare* BigMac = new Burger{ 10, "BigMac" };
	lista.push_back(BigMac);

	Mancare* BurgerBigMac2 = new Burger{ 10, "BigMac" };
	Mancare* BigMacCartof = new CuCartof{ BurgerBigMac2 };
	Mancare* BigMacCartofSos = new CuSos{ BigMacCartof };
	lista.push_back(BigMacCartofSos);

	Mancare* burgerZinger = new Burger{ 8, "Zinger" };
	Mancare* burgerZinger2 = new Burger{ 8, "Zinger" };
	
	Mancare* burgerZingerCartof = new CuCartof{ burgerZinger };
	Mancare* burgerZingerSos = new CuSos{ burgerZinger2 };

	lista.push_back(burgerZingerCartof);
	lista.push_back(burgerZingerSos);

	return lista;
}

/*

		std::vector<Mancare*> lista = mancare();

		std::sort(lista.begin(), lista.end(), [](Mancare* m1, Mancare* m2) {return m1->getPret() > m2->getPret(); });
		for (auto& m : lista)
		{
			std::cout << m->descriere()+' '<<m->getPret() << '\n';
			delete m;
		}*/