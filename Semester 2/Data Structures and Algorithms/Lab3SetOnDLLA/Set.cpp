#include "Set.h"
#include "SetITerator.h"
#include <iostream>

//Theta(1)
Set::Set() {
	//TODO - Implementation
	this->capacity = 2;
	this->length = 0;
	this->nodes = new DLLANode[this->capacity];

	this->head = -1;
	this->tail = -1;
	this->firstEmpty = 0;
	
	this->nodes[0].next = 1;
	this->nodes[1].next = -1;

	this->nodes[0].prev = -1;
	this->nodes[1].prev = 0;
}

//O(n) - n is the number of elements in the set
bool Set::add(TElem elem) {
	//TODO - Implementation
	if (this->head == -1)//empty list case
	{
		this->head = this->firstEmpty;
		this->tail = this->firstEmpty;
		
		this->firstEmpty = this->nodes[firstEmpty].next;

		this->nodes[this->head].next = -1;
		this->nodes[this->head].prev = -1;
		this->nodes[this->head].info = elem;
		this->length += 1;
		
		return true;
	}

	if (this->search(elem) == true)
		return false;

	if (this->length == this->capacity)
	{
		this->capacity *= 2;
		DLLANode* largerNodes = new DLLANode[this->capacity];

		for (int i = 0; i < this->length; i++)
			largerNodes[i] = this->nodes[i];

		delete[] this->nodes;
		this->nodes = largerNodes;
		
		this->firstEmpty = this->length;

		this->nodes[this->length].next = this->length + 1;
		this->nodes[this->length].prev = tail;
		
		for (int i = this->length + 1; i < this->capacity - 1; i++)
		{
			this->nodes[i].next = i + 1;
			this->nodes[i].prev = i - 1;
		}
		this->nodes[this->capacity - 1].next = -1;
		this->nodes[this->capacity - 1].prev = this->capacity - 2;

	}


	//add to the end
	int aux = this->nodes[firstEmpty].next;
	this->nodes[tail].next = this->firstEmpty;

	this->nodes[this->firstEmpty].info = elem;
	this->nodes[this->firstEmpty].next = -1;
	this->nodes[this->firstEmpty].prev = tail;

	tail = firstEmpty;
	firstEmpty = aux;

	this->length += 1;

	return true;
}

//O(n) - n is the number of elements in the set
bool Set::remove(TElem elem) {
	//TODO - Implementation

	if (this->length == 1)//case when the list has 1 element
	{
		if (this->nodes[this->head].info != elem)
			return false;

		this->nodes[this->head].next = this->firstEmpty;
		this->firstEmpty = this->head;

		this->head = -1;
		this->tail = -1;

		this->length -= 1;

		this->shrink();
		return true;
	}

	int current = this->head;
	while (current != -1)
	{
		if (this->nodes[current].info == elem)
		{
			if (current == this->head)//removes the head
			{
				this->head = this->nodes[this->head].next;
				this->nodes[this->head].prev = -1;

				this->nodes[current].next = this->firstEmpty;
				this->firstEmpty = current;
				this->nodes[this->firstEmpty].prev = this->tail;

				this->length -= 1;

				this->shrink();
				return true;
			}

			if (current == this->tail)//removes the tail
			{
				this->tail = this->nodes[this->tail].prev;
				this->nodes[this->tail].next = -1;

				this->nodes[current].next = this->firstEmpty;
				this->firstEmpty = current;
				this->nodes[this->firstEmpty].prev = this->tail;

				this->length -= 1;

				this->shrink();
				return true;
			}

			//removes an element between the head and tail
			int previous = this->nodes[current].prev;
			int next = this->nodes[current].next;

			this->nodes[current].next = this->firstEmpty;
			this->firstEmpty = current;

			this->nodes[previous].next = next;
			this->nodes[next].prev = previous;

			this->length -= 1;

			this->shrink();
			return true;
		}
		current = this->nodes[current].next;
	}

	return false;
}

//O(n) - number of elements in set
bool Set::search(TElem elem) const {
	//TODO - Implementation
	int current = this->head;

	while (current != -1)
	{
		if (this->nodes[current].info == elem)
			return true;
		current = this->nodes[current].next;
	}

	return false;
}

//theta(1)
int Set::size() const {
	//TODO - Implementation
	return this->length;
}

//theta(1)
bool Set::isEmpty() const {
	//TODO - Implementation
	return this->head == -1;
}

//theta(1)
Set::~Set() {
	//TODO - Implementation
	delete[] this->nodes;
}


//Theta(1) amortized - n is the number of elements
void Set::shrink()
{
	if (this->capacity / 2 == this->length && this->capacity > 2)
	{
		DLLANode* newNodes = new DLLANode[this->length];
		for (int i = 1; i < this->length - 1; i++)
		{
			newNodes[i].next = i + 1;
			newNodes[i].prev = i - 1;
		}
		newNodes[0].next = 1;  newNodes[this->length - 1].next = -1;
		newNodes[0].prev = -1; newNodes[this->length - 1].prev = this->length - 2;

		int i = 0, current = this->head;
		while (i != this->length)
		{
			newNodes[i].info = this->nodes[current].info;
			i++;
			current = this->nodes[current].next;
		}
		delete[] this->nodes;
		this->nodes = newNodes;
		this->firstEmpty = -1;
		this->head = 0;
		this->tail = this->length - 1;
		this->capacity = this->length;
	}
}

//theta(1)
SetIterator Set::iterator() {
	return SetIterator(*this);
}


