// MockupTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;


#include <deque>
#include <string>


class E {
public:
    E() { cout << "E{}"; }
    virtual ~E() { cout << "~E()"; }
};

class DE :public E {
public:
    static int n;
    DE() { n++; }
};
int DE::n = 0;
int fct2(int x)
{
    if (x < 0) {
        throw E{};
        cout << "NR LESS";
    }
    else if (x == 0) {
        throw DE{};
        cout << "number equal to 0";
    }
    return x % 10;
}

int main()
{
    try {
        int res = 0;
        res = fct2(0); cout << DE::n;
        res = fct2(25); cout << DE::n;

    }
    catch (E&)
    {
        cout << DE::n;
    }
    return 0;
}


















/*
int main()
{
    deque<string> d;
    d.push_back("A");
    d.push_front("B");
    d.push_back("C");
    d.push_front("D");
    auto itBegin = d.begin();
    auto itEnd = d.end();
    itBegin++;
    itEnd--;
    while (itBegin != itEnd)
    {
        std::cout << *itBegin << " ";
        itBegin++;
    }
    return 0;
}




*/






/*
class B
{
public:
    B() { std::cout << "B{}"; }
    virtual void print() { std::cout << "B"; }
    virtual~B() { std::cout << "~B()"; }
};

class D :public B
{
public:
    D() { std::cout << "D{}"; }
    void print() { std::cout << "D"; }
    virtual ~D() { std::cout << "~D()"; }

};

int main()
{
    B* b[] = { new B{}, new D{} };
    b[0]->print();
    b[1]->print();
    delete b[0];
    delete b[1];
    return 0;
}*/
