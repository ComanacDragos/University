#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111;
#define NULL_TELEM pair<int,int>(-11111, -11111);
class MultiMapIterator;

typedef struct Node {
	TKey key;
	TValue* values = new TValue[2];
	int length = 0, capacity = 2;
	Node* next;
}Node;

class MultiMap
{
	friend class MultiMapIterator;

private:
	//TODO - Representation

	int m, length;
	Node** elems;


	int hash(TKey key)const;
	void increaseSize(Node* node);
	void decreaseSize(Node* node);

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(TKey c, TValue v);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(TKey c, TValue v);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(TKey c) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//removes a key together with all its values
	//returns a vector with the values that were previously associated to this value (and were removed)
	vector<TValue> removeKey(TKey key);

	//descturctor
	~MultiMap();


};

