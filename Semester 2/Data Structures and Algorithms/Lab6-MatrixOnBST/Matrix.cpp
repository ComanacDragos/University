#include "Matrix.h"
#include <exception>
using namespace std;

//Thera
Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	this->lines = nrLines;
	this->columns = nrCols;
	this->size = 0;
	this->root = nullptr;
}


int Matrix::nrLines() const {
	//TODO - Implementation
	return this->lines;
}


int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->columns;
}

TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if (i < 0 || j < 0 || j >= this->columns || i >= this->lines)
		throw std::exception("Invalid position");

	if (this->root == nullptr)
		return NULL_TELEM;

	Node* current = this->root;

	int stackSize = 1;
	int stackCapacity = 2;
	Node** stack = new Node*[stackCapacity];
	
	stack[0] = this->root;

	
	while (stackSize != 0)
	{
		Node* current = stack[stackSize-1];
		stackSize -= 1;
		if (current->line == i && current->column == j)
		{
			delete[] stack;
			return current->value;
		}

		if (stackCapacity - 1 <= stackSize)
		{
			stackCapacity *= 2;
			Node** largerStack = new Node * [stackCapacity];
			for (int i = 0; i < stackSize; i++)
				largerStack[i] = stack[i];

			delete[] stack;
			stack = largerStack;
		}

		if(current->leftChild != nullptr)
		{ 
			stack[stackSize] = current->leftChild;
			stackSize += 1;
		}
		if(current->rightChild != nullptr)
		{
			stack[stackSize] = current->rightChild;
			stackSize += 1;
		}
	}

	delete[] stack;
	return NULL_TELEM;
}

TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation
	if (this->root == nullptr)
	{
		if (e == NULL_TELEM)
			return NULL_TELEM;

		Node* newNode = new Node;
		newNode->line = i;
		newNode->column = j;
		newNode->value = e;
		newNode->leftChild = nullptr;
		newNode->rightChild = nullptr;
		
		this->root = newNode;
		return NULL_TELEM;
	}

	Node* parent = nullptr;
	Node* current = this->root;

	while (current != nullptr)
	{
		if (current->value == e && current->line == i && current->column == j)
		{
			TElem old = current->value;

			if (e == NULL_TELEM) // delete
			{
				//first case: node is a leaf
				if (current->leftChild == nullptr && current->rightChild == nullptr)
				{
					if (parent == nullptr)//when the root is the only node
					{
						delete current;
						this->root = nullptr;
						return old;
					}

					if (parent->value < current->value)
						parent->rightChild = nullptr;
					else
						parent->leftChild = nullptr;
					delete current;
					return old;
				}
				//second case: node has one child
				if (current->leftChild == nullptr)
				{
					if (parent == nullptr) // delete root
					{
						this->root = current->rightChild;
						delete this->root;
						return old;
					}
					parent->rightChild = current->rightChild;
					delete current;
					return old;
				}
				if (current->rightChild == nullptr)
				{
					if (parent == nullptr) // delete root
					{
						this->root = current->leftChild;
						delete this->root;
						return old;
					}
					parent->leftChild = current->rightChild;
					delete current;
					return old;
				}
				//third case: node has 2 childred
				Node* succesor = current->rightChild;
				while (succesor->leftChild != nullptr)
					succesor = succesor->leftChild;

				current->value = succesor->value;
				current->line = succesor->line;
				current->column = succesor->column;
				
				delete succesor;
				return old;
			}
			//update
			if (current->leftChild->value <= e && e <= current->rightChild->value)
			{
				current->value = e;
				return old;
			}
			while(current->leftChild->value > e)
			{

			}
			
		}
		if (current->value < e)
		{
			parent = current;
			current = current->rightChild;
		}
		else
		{
			parent = current;
			current = current->leftChild;
		}
	}
	if (e == NULL_TELEM)
		return NULL_TELEM;

	//add
	Node* newNode = new Node;
	newNode->line = i;
	newNode->column = j;
	newNode->value = e;
	newNode->leftChild = nullptr;
	newNode->rightChild = nullptr;
	
	if (parent->value < e)
		parent->rightChild = newNode;
	else
		parent->leftChild = newNode;

	return NULL_TELEM;
}


