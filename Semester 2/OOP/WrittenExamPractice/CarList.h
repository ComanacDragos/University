#pragma once
#include <string>
#include <assert.h>
#include <utility>
#include <vector>
#include <iostream>
#include <algorithm>

class runtime_error : public std::exception
{
private:
    std::string message;

public:
    runtime_error(const std::string& s) : message{ s } {}

    const char* what() const throw() override {
        return this->message.c_str();
    }

};


class Car {
    friend std::ostream& operator<<(std::ostream& o, Car& car);
private:
    std::string name;
    int price;
public:
    Car(const std::string& name, int price):name{name}, price{price}{}


    bool operator==(Car& c) { return this->price == c.price; }
    bool operator<(const Car& c) { return this->price <= c.price; }
    //bool operator>(Car& c) { return this->price > c.price; }
};

template <typename T1, typename T2>
class List {
private:
    std::vector<std::pair<T1,T2>> pairs;
public:

    void add(const T1& firstComponent,const T2& secondComponent){
        std::pair<T1, T2> pair{ firstComponent, secondComponent };
        this->pairs.push_back(pair);
    }


    //Sorts the list by the first component(T1)
    //throws exeption if the list is empty
    void sortByFirstComponent() {
        if (this->pairs.size() == 0)
            throw runtime_error{ "List is empty!" };
        std::sort(this->pairs.begin(), this->pairs.end(), [](std::pair<T1, T2>& t1, std::pair<T1, T2>& t2) {return t1.first < t2.first; });

    }

    void sortBySecondComponent() {
        std::sort(this->pairs.begin(), this->pairs.end(), [](std::pair<T1, T2>& t1, std::pair<T1, T2>& t2) {return t1.second < t2.second; });
    }

    void printReverse(std::ostream& o){
        //for (auto it = this->pairs.end() - 1; it != this->pairs.begin(); it--)
        auto it = this->pairs.end();
        while(it!=this->pairs.begin())
           {
            it--;
            //std::pair<T1, T2> el = *it;
            o << (*it).first << " -> " << (*it).second<<"; ";
        }
        o << '\n';

    }
};

std::ostream& operator<<(std::ostream& o, Car& car) {
    o << car.name << ' ' << car.price;
    return o;
}


void function1() {
    List<Car, int> list1;
    try {
        list1.sortByFirstComponent();
        assert(false);
    }
    catch (runtime_error & e) { assert(strcmp(e.what(), "List is empty!") == 0); }

    list1.add(Car{ "Audi", 20 }, 8);
    list1.add(Car{ "Volkswagen", 10 }, 9);
    list1.add(Car{ "Bentley", 300 }, 10);

    list1.sortByFirstComponent();
    list1.printReverse(std::cout); // prints: Bentley 300 -> 10; Audi 20 -> 8; Volkswagen 10 -> 9 
    list1.sortBySecondComponent();
    list1.printReverse(std::cout); // prints: Bentley 300 -> 10; Volkswagen 10 -> 9; Audi 20 -> 8;
}