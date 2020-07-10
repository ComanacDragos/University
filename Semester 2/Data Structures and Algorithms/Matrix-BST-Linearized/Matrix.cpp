#include "Matrix.h"
#include <exception>
using namespace std;

//Theta(1)
Matrix::Matrix(int nrLines, int nrCols) {
	   
	//TODO - Implementation
	this->lines = nrLines;
	this->columns = nrCols;
	this->root = nullptr;
}

//Theta(1)
int Matrix::nrLines() const {
	//TODO - Implementation
	return this->lines;
}

//Theta(1)
int Matrix::nrColumns() const {
	//TODO - Implementation
	return this->columns;
}

//O(n) - n - height of the tree
TElem Matrix::element(int i, int j) const {
	//TODO - Implementation
	if (i < 0 || j < 0 || j >= this->columns || i >= this->lines)
		throw std::exception("Invalid position");

	if (this->root == nullptr)
		return NULL_TELEM;

	int index = i * this->columns + j;
	Node* current = this->root;

	while (current != nullptr)
	{
		if (current->index == index)
			return current->value;
		if (current->index < index)
			current = current->rightChild;
		else
			current = current->leftChild;
	}
	return NULL_TELEM;
}

//O(n) - n - height of the tree
TElem Matrix::modify(int i, int j, TElem e) {
	//TODO - Implementation

	if (i < 0 || j < 0 || j >= this->columns || i >= this->lines)
		throw std::exception("Invalid position");

	int index = i * this->columns + j;
	if (this->root == nullptr)
	{
		if (e == NULL_TELEM)
			return NULL_TELEM;

		Node* newNode = new Node;
		newNode->index = index;
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
		if (current->index == index)
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

					if (parent->index < current->index)
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
						delete current;
						return old;
					}
					if (current->index < parent->index)
						parent->leftChild = current->rightChild;
					else
						parent->rightChild = current->rightChild;
					delete current;
					return old;
				}
				if (current->rightChild == nullptr)
				{
					if (parent == nullptr) // delete root
					{
						this->root = current->leftChild;
						delete current;
						return old;
					}
					if (current->index < parent->index)
						parent->leftChild = current->leftChild;
					else
						parent->rightChild = current->leftChild;
					delete current;
					return old;
				}
				//third case: node has 2 childred
				Node* succesor = current->rightChild;
				parent = current;
				while (succesor->leftChild != nullptr)
				{
					parent = succesor;
					succesor = succesor->leftChild;
				}
				
				if(succesor->rightChild == nullptr) //if the succesor is a leaf
				{
					if (parent->index < succesor->index)
						parent->rightChild = nullptr;
					else
						parent->leftChild = nullptr;

					current->value = succesor->value;
					current->index = succesor->index;

					delete succesor;
					return old;
				}
				else // succesor has only one child(the right child)
				{
					if (parent->index < succesor->index)
						parent->rightChild = succesor->rightChild;
					else
						parent->leftChild = succesor->rightChild;

					current->value = succesor->value;
					current->index = succesor->index;

					delete succesor;
					return old;
				}
			}
			//update
			current->value = e;
			return old;

		}
		if (current->index < index)
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
	newNode->index = index;
	newNode->value = e;
	newNode->leftChild = nullptr;
	newNode->rightChild = nullptr;

	if (parent->index < index)
		parent->rightChild = newNode;
	else
		parent->leftChild = newNode;

	return NULL_TELEM;
}


//Best Case- Theta(1) - elem is the root
//Worst Case - Theta(n) - n is the number of elements - when the elem does not exist
//Overall O(n) - n is the number of elements
pair<int, int> Matrix::positionOf(TElem elem) const
{

	if (this->root == nullptr)
		return std::pair<int, int>{-1, -1};

	Node* current = this->root;

	int stackSize = 1;
	int stackCapacity = 2;
	Node** stack = new Node * [stackCapacity];

	stack[0] = this->root;


	while (stackSize != 0)
	{
		Node* current = stack[stackSize - 1];
		stackSize -= 1;

		if (current->value == elem)
		{
			int i = current->index / this->columns;
			int j = current->index % this->columns;
			delete[] stack;
			return std::pair<int, int>{i, j};
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

		if (current->leftChild != nullptr)
		{
			stack[stackSize] = current->leftChild;
			stackSize += 1;
		}
		if (current->rightChild != nullptr)
		{
			stack[stackSize] = current->rightChild;
			stackSize += 1;
		}

	}

	delete[] stack;
	return std::pair<int, int>{-1, -1};
}

//Theta(n) - n - number of nodes
Matrix::~Matrix()
{
	if (this->root == nullptr)
		return;

	Node* current = this->root;

	int stackSize = 1;
	int stackCapacity = 2;
	Node** stack = new Node * [stackCapacity];

	stack[0] = this->root;


	while (stackSize != 0)
	{
		Node* current = stack[stackSize - 1];
		stackSize -= 1;

		if (stackCapacity - 1 <= stackSize)
		{
			stackCapacity *= 2;
			Node** largerStack = new Node * [stackCapacity];
			for (int i = 0; i < stackSize; i++)
				largerStack[i] = stack[i];

			delete[] stack;
			stack = largerStack;
		}

		if (current->leftChild != nullptr)
		{
			stack[stackSize] = current->leftChild;
			stackSize += 1;
		}
		if (current->rightChild != nullptr)
		{
			stack[stackSize] = current->rightChild;
			stackSize += 1;
		}
		delete current;
	}

	delete[] stack;

}


