#pragma once
#include <iostream>
#include <vector>

class Fruct
{
public:
	virtual bool eCuSamburi()
	{
		return false;
	}
	virtual void tipareste() = 0;

	virtual ~Fruct(){}
};

class Pepene : public Fruct
{
private:
	float kg;
public:
	Pepene(float kg):kg{kg}{}

	virtual void tipareste()override {
		std::cout << kg << ' ' << "pepene";
	}
};

class PepeneRosu : public Pepene
{
public:
	PepeneRosu(float kg):Pepene{kg}{}
	
	void tipareste()override {
		Pepene::tipareste();
		std::cout << " rosu";
	}
};

class PepeneGalben : public Pepene
{
public:
	PepeneGalben(float kg) :Pepene{ kg } {}

	void tipareste()override {
		Pepene::tipareste();
		std::cout << " galben";
	}
};

class CuSamburi : public Fruct
{
private:
	Fruct* fruct;
public:
	CuSamburi(Fruct* f):fruct{f}{}
	
	void tipareste() override{
		this->fruct->tipareste();
		std::cout << " cu samburi";
	}

	bool eCuSamburi()override {
		return true;
	}
	~CuSamburi() {
		delete fruct;
	}
};

class Cos
{
private:
	std::vector<Fruct*> fructe;

public:
	void add(Fruct* f) {
		this->fructe.push_back(f);
	}

	std::vector<Fruct*> getAll(bool cuSamburi) {
		std::vector<Fruct*> v;
		for (Fruct* f : this->fructe)
			if (f->eCuSamburi() == cuSamburi)
				v.push_back(f);
		return v;
	}
	~Cos() {
		for (Fruct* f : this->fructe)
			delete f;
	}
};

void tipareste()
{
	Cos c;

	Fruct* pepeneRosuFaraSamburi = new PepeneRosu{ 3.3 };
	Fruct* pepeneGalben = new PepeneGalben{ 2.3 };
	Fruct* pepeneGalbenCuSamburi = new CuSamburi{ pepeneGalben };
	Fruct* pepeneGalbenFaraSamburi = new PepeneGalben(5.1);
	Fruct* pepeneRosuCuSamburi = new CuSamburi{ new PepeneRosu{ 4.5 } };

	c.add(pepeneRosuFaraSamburi);
	c.add(pepeneGalbenCuSamburi);
	c.add(pepeneGalbenFaraSamburi);
	c.add(pepeneRosuCuSamburi);

	std::cout << "Cu samburi:\n";
	for (Fruct* f : c.getAll(true))
	{
		f->tipareste();
		std::cout << '\n';
	}

	std::cout << "\nFara samburi:\n";
	for (Fruct* f : c.getAll(false))
	{
		f->tipareste();
		std::cout << '\n';
	}
}