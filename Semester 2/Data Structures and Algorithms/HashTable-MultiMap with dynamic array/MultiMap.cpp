#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//Theta(1)
int MultiMap::hash(TKey key)const
{
	return abs(key) % m;
}

//Theta(1) amortized
void MultiMap::increaseSize(Node* node)
{
	if (node->capacity == node->length)
	{
		node->capacity *= 2;
		TValue* newElems = new TValue[node->capacity];
		for (int i = 0; i < node->length; i++)
			newElems[i] = node->values[i];
		delete[] node->values;
		node->values = newElems;
	}
} 

//Theta(1) amortized
void MultiMap::decreaseSize(Node* node)
{
	if (node->capacity / 2 == node->length)
	{
		node->capacity /= 2;
		TValue* newElems = new TValue[node->capacity];
		for (int i = 0; i < node->length; i++)
			newElems[i] = node->values[i];
		delete[] node->values;
		node->values = newElems;
	}
}

//Theta(1)
MultiMap::MultiMap() {
	//TODO - Implementation
	this->m = 2;
	this->length = 0;
	this->elems = new Node * [this->m]();
}

//Theta(1) -amortized
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

				int bucket = this->hash(current->key);

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
	Node* current = this->elems[bucket];
	while (current != nullptr && current->key != c)
		current = current->next;
	
	if (current != nullptr)
	{
		this->increaseSize(current);
		current->values[current->length] = v;
		current->length += 1;
		this->length += 1;
		return;
	}

	Node* newNode = new Node;
	newNode->key = c;
	newNode->next = this->elems[bucket];
	newNode->values[0] = v;
	newNode->length = 1;
	this->elems[bucket] = newNode;
	this->length += 1;
}

//O(n) - n is the number of elements
bool MultiMap::remove(TKey c, TValue v) {
	//TODO - Implementation
	int bucket = this->hash(c);
	Node* previous = nullptr;
	Node* current = this->elems[bucket];
	if (current == nullptr)
		return false;

	while(current != nullptr && current->key != c)
	{
		previous = current;
		current = current->next;
	}
	if (current == nullptr)
		return false;
	
	for(int i=0;i<current->length;i++)
		if (current->values[i] == v)
		{
			for (int j = i; j < current->length - 1; j++)
				current->values[j] = current->values[j + 1];
			current->length -= 1;

			if (current->length == 0)
			{
				if (previous == nullptr)
				{
					this->elems[bucket] = current->next;
					delete[] current->values;
					delete current;
					this->length -= 1;
					return true;
				}
				previous->next = current->next;
				delete[] current->values;
				delete current;
				this->length -= 1;
				return true;
			}
			this->decreaseSize(current);
			this->length -= 1;
			return true;
		}
	return false;
}

//O(n) - n is the number of elements
vector<TValue> MultiMap::search(TKey c) const {
	//TODO - Implementation
	int bucket = this->hash(c);
	vector<TValue> values;
	Node* current = this->elems[bucket];

	while (current != nullptr)
	{
		if (current->key == c)
		{
			for (int i = 0; i < current->length; i++)
				values.push_back(current->values[i]);
			break;
		}
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

//O(m)
MultiMapIterator MultiMap::iterator() const {
	return MultiMapIterator(*this);
}


//Best case: Theta(1) - key has 1 value
//Worst case: Theta(n) - key has all values
//Ovarall: O(n) 
vector<TValue> MultiMap::removeKey(TKey key)
{
	std::vector<TValue> values;
	int bucket = this->hash(key);
	Node* previous = nullptr;
	Node* current = this->elems[bucket];
	if (current == nullptr)
		return values;

	while (current != nullptr && current->key != key)
	{
		previous = current;
		current = current->next;
	}
	if (current == nullptr)
		return values;

	for (int i = 0; i < current->length; i++)
		values.push_back(current->values[i]);

	if (previous == nullptr)
	{
		this->elems[bucket] = current->next;
		this->length -= current->length;
		delete[] current->values;
		delete current;
		return values;
	}
	previous->next = current->next;
	this->length -= current->length;
	delete[] current->values;
	delete current;
	return values;

}

//O(m+nr_keys)
MultiMap::~MultiMap() {
	//TODO - Implementation
	for (int i = 0; i < this->m; i++)
	{
		Node* current = this->elems[i];
		while (current != nullptr)
		{
			Node* next = current->next;
			delete[] current->values;
			delete current;
			current = next;
		}
	}
	delete[] this->elems;
}

