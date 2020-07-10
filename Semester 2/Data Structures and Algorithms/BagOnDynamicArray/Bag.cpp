#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//TODO - Implementation
	lenght = 0;
	capacity = 1;
	frequencies = new TElem[capacity];
	frequencies[0] = 0;
	
	min = -1;
	max = -1;
	
}


//complexity O(n)
void Bag::add(TElem elem) {
	//TODO - Implementation
	if (lenght == 0)
	{
		min = elem;
		max = elem;
		frequencies[0]++;
		lenght = 1;
		return;
	}
	if (elem < min)
	{
		capacity = max - elem + 1;
		TElem* new_frequencies = new TElem[capacity];
		
		for (int i = 0; i < min - elem; i++)
			new_frequencies[i] = 0;

		for (int i = min - elem; i < capacity; i++)
			new_frequencies[i] = frequencies[i - (min - elem)];
		
		delete frequencies;
		frequencies = new_frequencies;
		min = elem;
	}
	if (elem > max)
	{
		capacity = elem - min + 1;
		TElem* new_frequencies = new TElem[capacity];

		for (int i = 0; i < max-min+1; i++)
			new_frequencies[i] = frequencies[i];
		
		for (int i = max - min + 1; i < capacity; i++)
			new_frequencies[i] = 0;

		delete frequencies;
		frequencies = new_frequencies;
		max = elem;
	}
	frequencies[elem - min]++;
	lenght++;
}

//complexity O(n)
bool Bag::remove(TElem elem) {
	//TODO - Implementation
	if(elem<min || elem>max || frequencies[elem-min] == 0)
		return false; 
	frequencies[elem - min]--;
	lenght--;
	if (lenght == 0)
		return true;
	int left = 0, right=capacity-1;

	while (frequencies[left] == 0)
		left++;

	while (frequencies[right] == 0)
		right--;

	if (left != 0 || right != capacity - 1)
	{
		min += left;
		max -= capacity-1-right;
		capacity = right - left + 1;

		TElem* new_frequencies = new TElem[capacity];
	
		for (int i = left; i <= right; i++)
			new_frequencies[i - left] = frequencies[i];
	
		delete frequencies;
		frequencies = new_frequencies;
	}

	return true;
}

// Complexity: theta(1);
bool Bag::search(TElem elem) const {
	//TODO - Implementation
	if (frequencies[elem - min] == 0 || elem > max || elem < min)
		return false;
	return true;
}

// Complexity: theta(1);
int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	if (elem < min || elem > max || lenght == 0)
		return 0;
	return frequencies[elem - min];
}

// Complexity: theta(1);
int Bag::size() const {
	//TODO - Implementation
	return lenght;
}

// Complexity: theta(1);
bool Bag::isEmpty() const {
	//TODO - Implementation
	return lenght == 0;
}

BagIterator Bag::iterator() const {
	//TODO - Implementation
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
	delete frequencies;
}

