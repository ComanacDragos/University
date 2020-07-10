#pragma once
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>

class Icecream
{
public:
	virtual ~Icecream(){}

	virtual std::string getDescription() = 0;
	virtual double computePrice() = 0;
};

class SimpleIcecream : public Icecream
{
private:
	std::string description;
	double price;

public:
	SimpleIcecream(const std::string& description, double price):description{description}, price{price}{}

	virtual std::string getDescription()override
	{
		return "simple ice cream with " + this->description;
	}

	virtual double computePrice()override
	{
		return this->price;
	}
};

class IcecreamWithTopping :public Icecream
{
protected:
	std::unique_ptr<Icecream> icecream;

public:
	IcecreamWithTopping(std::unique_ptr<Icecream>& icecream) :icecream{ std::move(icecream) }{}

	virtual std::string addTopping() = 0;

	virtual std::string getDescription()override
	{
		return icecream->getDescription() + this->addTopping();
	}
	virtual ~IcecreamWithTopping(){}
};

class IcecreamWithChocolateTopping : public IcecreamWithTopping
{
public:
	IcecreamWithChocolateTopping(std::unique_ptr<Icecream>& icecream):IcecreamWithTopping{icecream}{}

	virtual std::string addTopping()override
	{
		return " with chocolate topping";
	}

	virtual double computePrice() override
	{
		return IcecreamWithTopping::icecream->computePrice() + 3;
	}
};

class IcecreamWithCaramelTopping : public IcecreamWithTopping
{
public:
	IcecreamWithCaramelTopping(std::unique_ptr<Icecream>& icecream) :IcecreamWithTopping{ icecream } {}

	virtual std::string addTopping()override
	{
		return " with caramel topping";
	}

	virtual double computePrice() override
	{
		return IcecreamWithTopping::icecream->computePrice() + 2;
	}
};

class Order
{
private:
	std::vector<std::unique_ptr<Icecream>> icecreams;

public:
	void addIcecream(std::unique_ptr<Icecream>& icecream)
	{
		this->icecreams.push_back(std::move(icecream));
	}

	void printOrder()
	{
		std::sort(this->icecreams.begin(), this->icecreams.end(), [](std::unique_ptr<Icecream>& i1, std::unique_ptr<Icecream>& i2) {return i1->computePrice() > i2->computePrice(); });
		for (auto& i : this->icecreams)
			std::cout << i->getDescription() << '\n';
	}

};


void create()
{
	Order order;
	
	std::unique_ptr<Icecream> vanilla = std::make_unique<SimpleIcecream>("vanilla", 5);

	std::unique_ptr<Icecream> pistachio = std::make_unique<SimpleIcecream>("pistacho", 7);
	std::unique_ptr<Icecream> pistachioChoco = std::make_unique<IcecreamWithChocolateTopping>(pistachio);
	std::unique_ptr<Icecream> pistachioChocoCaramel = std::make_unique<IcecreamWithCaramelTopping>(pistachioChoco);
	
	std::unique_ptr<Icecream> hazelnuts = std::make_unique<SimpleIcecream>("hazelnuts", 10);

	std::unique_ptr<Icecream> choco = std::make_unique<SimpleIcecream>("chocolate", 6);
	std::unique_ptr<Icecream> chocoCaramel = std::make_unique<IcecreamWithCaramelTopping>(choco);



	order.addIcecream(vanilla);
	order.addIcecream(pistachioChocoCaramel);
	order.addIcecream(chocoCaramel);
	order.addIcecream(hazelnuts);

	order.printOrder();
}

