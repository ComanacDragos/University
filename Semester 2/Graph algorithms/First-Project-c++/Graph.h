#pragma once

#include <utility>
#include <unordered_map>

using namespace std;


struct hash_pair
{
	template <int, int>
	int operator()(const pair<int, int>& p)const
	{
		auto hash1 = hash<int>{}(p.first);
		auto hash2 = hash<int>{}(p.second);
		return hash1 ^ hash2;
	}
};

class Graph
{
private:
	unordered_map<pair<int, int>, int, hash_pair>costs;
	unordered_map<int, unordered_map<int, int>> inbound;
	unordered_map<int, unordered_map<int, int>> outbound;
	int nodes, edges;

public:
	//constructor
	Graph();

	//returns the number of nodes
	int getNodes();

	//returns the number of edges;
	int getEdges();

	//returns true if a given node is in the graph or false otherwise
	bool isNode(int node);

	//returns true if a given edge exists or false otherwise
	bool isEdge(int left, int right);
};

