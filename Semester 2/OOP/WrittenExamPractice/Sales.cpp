#include <vector>

class SaleItem
{
private:
	int code;
	double price;
public:
	SaleItem(int code, double price):code{code}, price{price}{}

	int getCode() { return this->code; }
	double getPrice() { return this->price; }
};

class Sale
{
public:
	std::vector<SaleItem> items;
	Sale(std::vector<SaleItem> items):items{items}{}

};

class Discount
{
public:
	virtual double calc(Sale& s) = 0;
};

class ItemDiscount :public Discount
{
private:
	int code;
	int percentage;
public:
	ItemDiscount(int code, int percentage) :code{ code }, percentage{ percentage } {}

	double calc(Sale& s) override{
		for (SaleItem& it : s.items)
		{
			if (it.getCode() == code)
			{
				double p =(double)this->percentage / 100;
				return p * it.getPrice();
			}
		}
	}
};

class SumDiscount :public Discount
{
private:
	std::vector<Discount*> discounts;
public:
	void add(Discount* d) {
		this->discounts.push_back(d);
	}

	double calc(Sale& s) override {
		double sum=0;
		for (Discount* it : this->discounts)
			sum += it->calc(s);
		return sum;
	}
	~SumDiscount()
	{
		for (Discount* d : this->discounts)
			delete d;
	}

};


int main()
{
	{
		SaleItem it1{ 1, 1500 };
		SaleItem it2{ 2, 2500 };
		SaleItem it3{ 3, 3500 };

		Sale s{ {it1,it2,it3} };

		Discount* d1 = new ItemDiscount{ 1,10 };
		Discount* d2 = new ItemDiscount{ 2,10 };
		Discount* d3 = new ItemDiscount{ 3,15 };

		SumDiscount sum;
		sum.add(d1);
		sum.add(d2);
		sum.add(d3);

		std::cout << sum.calc(s);
	}

	_CrtDumpMemoryLeaks();
	return 0;
}