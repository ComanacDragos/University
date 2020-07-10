#include "SetIterator.h"
#include "Set.h"

//theta(1)
SetIterator::SetIterator(Set& m) : set(m)
{
	//TODO - Implementation
	this->current = set.head;
}


//theta(1)
void SetIterator::first() {
	//TODO - Implementation
	this->current = set.head;
}


//theta(1)
void SetIterator::next() {
	//TODO - Implementation
	if (this->current == -1)
		throw std::exception("invalid iterator");
	this->current = this->set.nodes[this->current].next;
}


//theta(1)
TElem SetIterator::getCurrent()
{
	//TODO - Implementation
	if (this->valid() == false)
		throw std::exception("invalid iterator");

	return this->set.nodes[this->current].info;
}

//theta(1)
bool SetIterator::valid() const {
	//TODO - Implementation
	return this->current != -1;
}


//Best case: Theta(1) - when the set does not perform shrink and the while loop executes only once
//Worst case Theta(n) - when the while loop executes n times(n -number of elements after removal)
//Overall: O(n)
TElem SetIterator::remove()
{
	if(this->valid() == false)
		throw std::exception("invalid iterator");
	
	int aux = this->current;
	TElem auxElem = this->set.nodes[aux].info;
	int next = this->set.nodes[aux].next;
	TElem nextElem = this->set.nodes[next].info;
	
	this->set.remove(this->set.nodes[aux].info);
	
	if (next == -1)
	{
		this->current = -1;
		return auxElem;
	}

	int p = this->set.head;

	while (p != -1)
	{
		if (this->set.nodes[p].info == nextElem)
		{
			this->current = p;
			break; 
		}
		p = this->set.nodes[p].next;
	}

	return auxElem;
}



