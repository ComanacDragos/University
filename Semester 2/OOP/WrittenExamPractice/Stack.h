#include <string>
#include <string.h>
#include <assert.h>
#include <exception>

template <typename T>
class Stack
{
private:
	int capacity, size;
	T* arr;
public:
	Stack(int cap)
	{
		this->capacity = cap;
		this->size = 0;
		this->arr = new T[this->capacity];
	}

	
	Stack<T>& operator=(Stack<T>& s) {
		this->capacity = s.capacity;
		this->size = s.size;
		T* newArr = new T[this->capacity];
		for (int i = 0; i < this->size; i += 1)
			newArr[i] = s.arr[i];
		delete[] this->arr;
		this->arr = newArr;
		return *this;
	}
	
	Stack<T>& operator+(const T& s) {
		if (capacity == size)
			throw std::exception{ "Stack is full!" };
		this->arr[this->size] = s;
		this->size += 1;
		return *this;
	}

	int getMaxCapacity() { return this->capacity; }

	T pop() {
		this->size -= 1;
		return this->arr[this->size];
	}

	~Stack() { delete[] this->arr; }
};

void testStack()
{
	Stack<std::string> s{ 2 };
	assert(s.getMaxCapacity() == 2);
	try {
		s = s + "examination";
		s = s + "oop";
		s = s + "test";
	}
	catch (std::exception & e) {
		assert(strcmp(e.what(), "Stack is full!") == 0);
	}
	assert(s.pop() == "oop");
	assert(s.pop() == "examination");

}