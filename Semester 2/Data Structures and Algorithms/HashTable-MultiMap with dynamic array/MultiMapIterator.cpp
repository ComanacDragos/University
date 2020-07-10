#include "MultiMapIterator.h"
#include "MultiMap.h"

//O(m)
MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	//TODO - Implementation
	this->current = nullptr;
	this->currentBucket = -1;
	this->currentIndex = -1;
	for (int i = 0; i < this->col.m; i++)
	{
		if (this->col.elems[i] != nullptr)
		{
			this->current = this->col.elems[i];
			this->currentBucket = i;
			this->currentIndex = 0;
			break;
		}
	}

}

//Theta(1)
TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if (this->valid() == false)
		throw(exception("Invalid iterator"));

	TElem pair{ this->current->key, this->current->values[this->currentIndex] };
	return pair;
}

//Theta(1)
bool MultiMapIterator::valid() const {
	//TODO - Implementation
	return this->current != nullptr;
}

//O(m)
void MultiMapIterator::next() {
	//TODO - Implementation
	if (this->valid() == false)
		throw(exception("Invalid iterator"));
	if (this->current->length-1 == this->currentIndex)
	{
		if (this->current->next != nullptr)
		{
			this->current = this->current->next;
			this->currentIndex = 0;
			return;
		}
		for (int i = this->currentBucket + 1; i < this->col.m; i++)
		{
			if (this->col.elems[i] != nullptr)
			{
				this->current = this->col.elems[i];
				this->currentBucket = i;
				this->currentIndex = 0;
				return;
			}
		}
		this->current = nullptr;
		this->currentBucket = -1;
		this->currentIndex = -1;
	}
	else
	{
		this->currentIndex += 1;
	}
	
}

//O(m)
void MultiMapIterator::first() {
	//TODO - Implementation
	this->current = nullptr;
	this->currentBucket = -1;
	this->currentIndex = -1;
	for (int i = 0; i < this->col.m; i++)
	{
		if (this->col.elems[i] != nullptr)
		{
			this->current = this->col.elems[i];
			this->currentBucket = i;
			this->currentIndex = 0;
			break;
		}
	}

}

