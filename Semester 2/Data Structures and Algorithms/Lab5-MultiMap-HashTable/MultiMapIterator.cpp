#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
	//TODO - Implementation
	this->current = nullptr;
	this->currentBucket = -1;
	for (int i = 0; i < this->col.m; i++)
	{
		if (this->col.elems[i] != nullptr)
		{
			this->current = this->col.elems[i];
			this->currentBucket = i;
			break;
			}
	}
}

TElem MultiMapIterator::getCurrent() const{
	//TODO - Implementation
	if (this->valid() == false)
		throw(exception("Invalid iterator"));
	return this->current->info;
}

bool MultiMapIterator::valid() const {
	//TODO - Implementation
	return this->current != nullptr;
}

void MultiMapIterator::next() {
	//TODO - Implementation
	if (this->valid() == false)
		throw(exception("Invalid iterator"));
	if (this->current->next != nullptr)
	{
		this->current = this->current->next;
		return;
	}
	for (int i = this->currentBucket + 1; i < this->col.m; i++)
	{
		if (this->col.elems[i] != nullptr)
		{
			this->current = this->col.elems[i];
			this->currentBucket = i;
			return;
		}
	}
	this->current = nullptr;
	this->currentBucket = -1;
}

void MultiMapIterator::first() {
	//TODO - Implementation
	this->current = nullptr;
	this->currentBucket = -1;
	for (int i = 0; i < this->col.m; i++)
	{
		if (this->col.elems[i] != nullptr)
		{
			this->current = this->col.elems[i];
			this->currentBucket = i;
			break;
		}
	}
}
