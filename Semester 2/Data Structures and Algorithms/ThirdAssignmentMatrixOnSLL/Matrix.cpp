#include "Matrix.h"
#include <exception>
using namespace std;

//theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	this->lines = nrLines;
	this->columns = nrCols;
	this->head = NULL;
}


//theta(1)
int Matrix::nrLines() const {
	//TODO - Implementation
	return this->lines;
}


//theta(1)
int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->columns;
}


//O(n) - where n is the number of non-null elements in the matrix
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if (i < 0 || j < 0 || i >= this->lines || j >= this->columns)
		throw exception("Bad position");
	
	if (this->head == NULL)
		return NULL_TELEM;

	Node* p = this->head;
	while (p != NULL)
	{
		if (p->line == i && p->column == j)
			return p->value;
		p = p->next;
	}
	return NULL_TELEM;
}

//O(n) - where n is the number of non-null elements in the matrix
TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	if (i < 0 || j < 0 || i >= lines || j >= columns)
		throw exception("Bad position");

	Node* new_node = new Node;
	new_node->line = i;
	new_node->column = j;
	new_node->value = e;
	new_node->next = NULL;

	//empty list case
	if (this->head == NULL)
	{
		if (e != NULL_TELEM)
			this->head = new_node;
		return NULL_TELEM;
	}

	Node* p = head;
	Node* previous = NULL;

	//get to required line
	while (p != NULL && p->line < i)
	{
		previous = p;
		p = p->next;
	}

	//get to required column
	while (p != NULL && p->line == i && p->column < j)
	{
		previous = p;
		p = p->next;
	}
	
	if (previous == NULL)
	{
		//check if we need to modify the head value
		if (p->line == i && p->column == j)
		{
			TElem aux = p->value;
			if (e != NULL_TELEM)
			{
				p->value = e;
				return aux;
			}
			else
			{
				this->head = p->next;
				delete p;
				return aux;
			}
		}
		else
		{
			//insert new head
			if (e == NULL_TELEM)
				return NULL_TELEM;

			new_node->next = this->head;
			this->head = new_node;

			return NULL_TELEM;
		}
	}
	
	if (p == NULL)
	{
		//add new_node at the end
		previous->next = new_node;
		new_node->next = NULL;

		return NULL_TELEM;
	}

	if (p->line == i && p->column == j)
	{
		//first case: update an existing value with a non-null value
		TElem aux = p->value;
		if (e != NULL_TELEM)
		{
			p->value = e;
			return aux;
		}
		//second case: update an existing value with a null value
		else
		{
			previous->next = p->next;
			delete p;
			return aux;
		}
	}
	if (e == NULL_TELEM)
		//third case: update a null value with a null value
		return NULL_TELEM;
	else
	{
		//fourth case: update a null value with a non-null value
		previous->next = new_node;
		new_node->next = p;
		return NULL_TELEM;
	}
}


// Best case Theta(1) : the list is empty
// Worst case Theta(n): when we need to check for the last line (meaning that we need to parse all elements)
// Overall: O(n)
// where n is the number of non null elements in the matrix
int Matrix::numberOfNonZeroElems(int line) const
{
	if (line < 0 || line >= this->lines)
		throw exception("bad line");

	int numberOfNonZeroElements = 0;
	Node* p = this->head;


	while (p!= NULL && p->line < line)
		p = p->next;

	while (p!=NULL && p->line == line)
	{
		p = p->next;
		numberOfNonZeroElements += 1;
	}
	return numberOfNonZeroElements;
}

//theta(n) - where n is the number of non-null elements in the matrix
Matrix::~Matrix()
{
	Node* p = this->head;
	while (p != NULL)
	{
		Node* aux = p->next;
		delete p;
		p = aux;
	}
}
