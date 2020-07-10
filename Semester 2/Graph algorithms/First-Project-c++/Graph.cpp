#include "Graph.h"
#include <iostream>
using namespace std;

Graph::Graph()
{
	nodes = 0;
	edges = 0;

	unordered_map<int, int> list;
	inbound.emplace(1, list);
	pair<int, int>p = { 1,2 };
	costs.emplace(p, 3);
	
}

int Graph::getNodes()
{
	return nodes;
}

int Graph::getEdges()
{
	return edges;
}

bool Graph::isNode(int n)
{
	unordered_map<int, unordered_map<int, int>>::local_iterator iter = inbound.find(n);
	
	if (iter == inbound.end())
		return false;
	return true;
}

bool Graph::isEdge(int left, int right)
{
	//unordered_map<pair<int, int>, int, hash_pair>::local_iterator iter = costs.find(create_pair(left, right));

	//if (costs.find(create_pair(left,right)) == costs.end())
		return false;
	return true;

}

