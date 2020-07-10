#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//Theta(1)
int MultiMap::hash(TKey key)const
{
	return abs(key)%m;
}

//Theta(1)
MultiMap::MultiMap() {
	//TODO - Implementation
	this->m = 2;
	this->length = 0;
	this->elems = new Node*[this->m]();
}

//Theta(1) - amortized
void MultiMap::add(TKey c, TValue v) {
	//TODO - Implementation
	if ((float)this->length / this->m >= 1)
	{
		this->m *= 2;
		Node** newElems = new Node * [this->m]();

		for (int i = 0; i < this->m / 2; i++)
		{
			Node* current = this->elems[i];
			while (current != nullptr)
			{
				Node* next = current->next;

				int bucket = this->hash(current->info.first);

				if (newElems[bucket] == nullptr)
				{
					current->next = nullptr;
					newElems[bucket] = current;
				}
				else
				{
					current->next = newElems[bucket];
					newElems[bucket] = current;
				}
				current = next;
			}
		}
		delete[] this->elems;
		this->elems = newElems;
	}
	int bucket = this->hash(c);
	Node* newNode = new Node;
	newNode->info = TElem{ c,v };

	if (this->elems[bucket] == nullptr)
	{
		newNode->next = nullptr;
		this->elems[bucket] = newNode;

	}
	else
	{
		newNode->next = this->elems[bucket];
		this->elems[bucket] = newNode;
	}
	this->length += 1;
}

//O(n)
bool MultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int bucket = this->hash(c);
	TElem pair{ c,v };
	Node* previous = nullptr;
	Node* current = this->elems[bucket];
	if (current == nullptr)
		return false;

	while (current != nullptr && current->info != pair)
	{
		previous = current;
		current = current->next;
	}
	if (current == nullptr)
		return false;

	if (previous == nullptr)
	{
		this->elems[bucket] = current->next;
		delete current;
		this->length -= 1;
		return true;
	}
	previous->next = current->next;
	delete current;
	this->length -= 1;
	return true;

}


//O(n)
vector<TValue> MultiMap::search(TKey c) const {
	//TODO - Implementation
	vector<TValue> values;
	Node* current = this->elems[this->hash(c)];
	while (current != nullptr)
	{
		if (current->info.first == c)
			values.push_back(current->info.second);
		current = current->next;
	}
	return values;
}

//Theta(1)
int MultiMap::size() const {
	//TODO - Implementation
	return this->length;
}

//Theta(1)
bool MultiMap::isEmpty() const {
	//TODO - Implementation
	return this->length == 0;
}

MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


//Theta(m)
MultiMap::~MultiMap() {
	//TODO - Implementation
	for(int i=0;i<this->m;i++)
	{
		Node* current = this->elems[i];
		while (current != nullptr)
		{
			Node* next = current->next;
			delete current;
			current = next;
		}
	}
	delete[] this->elems;
}

