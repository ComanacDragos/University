#pragma once
#include "Set.h"
#include <exception>

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	 Set& set;
	SetIterator( Set& s);

	//TODO - Representation
	int current;

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;

	//removes and returns the current element from the iterator
	//after the operation the current element from the Iterator is the next element from the Set, or, if the removed element was the last one, the iterator is invalid
	//throws exception if the iterator is invalid
	TElem remove();


	/*
	
	Obs: In order for this operation to work, you need to perform some other changes in your code:
Iterator operation from the Set no longer is const
The reference to the  Set in the iterator is no longer const (but it is still a reference!)
The parameter passed to the constructor of the iterator class is no longer const

*/

};


