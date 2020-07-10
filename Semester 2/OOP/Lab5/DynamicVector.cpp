/*

#include "DynamicVector.h"

template <typename TElem>
DynamicVector<TElem>::DynamicVector()
{
	this->capacity = 2;
	this->length = 0;
	this->elements = new TElem[this->capacity];
}

template <typename TElem>
DynamicVector<TElem>::DynamicVector(const DynamicVector<TElem>& dynamicVector)
{
	this->capacity = dynamicVector.capacity;
	this->length = dynamicVector.length;
	this->elements = new TElem[this->capacity];

	for (int i = 0; i < this->length; i++)
		this->elements[i] = dynamicVector.elements[i];
}

template <typename TElem>
DynamicVector<TElem>::~DynamicVector()
{
	delete[] this->elements;
}

template <typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator=(const DynamicVector<TElem>& dynamicVector)
{
	if (this == &dynamicVector)
		return *this;

	this->capacity = dynamicVector.capacity;
	this->length = dynamicVector.length;
	delete[] this->elements;

	this->elements = new TElem[this->capacity];

	for (int i = 0; i < this->length; i++)
		this->elements[i] = dynamicVector.elements[i];

	return *this;
}

template <typename TElem>
void DynamicVector<TElem>::addElement(const TElem& element)
{	
	if (this->capacity == this->length)
		this->increaseSize();

	this->elements[this->length] = element;
	this->length += 1;
}

template <typename TElem>
void DynamicVector<TElem>::removeFromPosition(int position)
{
	
	for (int i = position; i < this->length; i++)
		this->elements[i] = this->elements[i + 1];
	
	this->length -= 1;

	if (this->length == this->capacity / 2)
		this->shrinkSize();
}

template <typename TElem>
int DynamicVector<TElem>::getLength()
{
	return this->length;
}

template <typename TElem>
TElem& DynamicVector<TElem>::getElement(int position)
{
	return this->elements[position];
}

template <typename TElem>
int DynamicVector<TElem>::findElement(TElem element)
{
	for (int i = 0; i < this->length; i++)
		if (this->elements[i] == element)
			return i;
	return -1;
}

template <typename TElem>
void DynamicVector<TElem>::increaseSize()
{
	this->capacity *= 2;
	TElem* largerElements = new TElem[this->capacity];
	
	for (int i = 0; i < this->length; i++)
		largerElements[i] = this->elements[i];

	delete[] this->elements;
	this->elements = largerElements;

}

template <typename TElem>
void DynamicVector<TElem>::shrinkSize()
{
	this->capacity /= 2;
	TElem* smallerElements = new TElem[this->capacity];

	for (int i = 0; i < this->length; i++)
		smallerElements[i] = this->elements[i];

	delete[] this->elements;
	this->elements = smallerElements;
}
*/