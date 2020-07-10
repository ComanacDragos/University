#include "Matrix.h"
#include <exception>
using namespace std;


Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	length = 0;
	lines = nrLines;
	columns = nrCols;
	head = NULL;
}

// theta(1)
int Matrix::nrLines() const {
	//TODO - Implementation
	return lines;
}


// theta(1)
int Matrix::nrColumns() const {
	//TODO - Implementation
	return columns;
}

//O(n)
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if (i < 0 || j < 0 || i >= lines || j >= columns)
		throw exception("Bad position");
	if (head == NULL)
		return 0;
	Node* p = head;
	while (p != NULL)
	{
		if (p->line == i && p->column == j)
			return p->value;
		p = p->next;
	}
	return NULL_TELEM;
}


//O(n)
TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	if (i < 0 || j < 0 || i >= lines || j >= columns)
		throw exception("Bad position");


	Node* new_node = new Node;
	new_node->line = i;
	new_node->column = j;
	new_node->value = e;
	new_node->next = NULL;

	if (head == NULL)
	{
		head = new_node;
		return 0;
	}

	Node* p = head;
	while (p->next != NULL && p->line != i)
	{
		p = p->next;
	}

	if (p->line == i && p->column == j)
	{
		TElem aux = p->value;
		p->value = e;
		return aux;
	}

	while (p->next != NULL && p->next->line == i && p->next->column < j)
		p = p->next;


	Node* aux = p->next;
	p->next = new_node;
	new_node->next = aux;
	return NULL_TELEM;
}

//theta(n)
Matrix::~Matrix()
{
	Node* p = head;
	while (p != NULL)
	{
		Node* aux = p->next;
		delete p;
		p = aux;
	}
}
