#include <iostream>
#include <fstream>
#include <algorithm>
#include <list>

using namespace std;
class graphType
{
protected:
	int maxSize; //maximum number of vertices
	int gSize; //current number of vertices
	std::list<int> *graph;

public:
	template <class T>
	static inline bool contains(std::list<T> &l, const T &v) {
		return std::find(l.begin(), l.end(), v) != l.end();
	}
	//function to check if graph is empty
	bool isEmpty() const {
		return gSize == 0;
	}
	//clear the graph
	void clearGraph() {
		for (int index = 0; index < gSize; index++) {
			graph[index].clear();
		}
		gSize = 0;
	}
	//print the graph
	void printGraph() const {
		for (int index = 0; index < gSize; index++)
		{
			cout << "[" << index << "] ";
			for (auto v : graph[index])
				cout << v << " ";
			cout << endl;
		}
		cout << endl;
	}
	//add the edge
	void addEdge(int u, int v) {
		if (graph[u].empty())
			gSize++;
		if (graph[v].empty())
			gSize++;

		if (!contains(graph[u], v))
			graph[u].push_back(v);
		if (!contains(graph[v], u))
			graph[v].push_back(u);
	}
	//return size of graph
	int getgSize() const {
		return gSize;
	}
    
    
    //constructor
	graphType(int size = 0) {
		maxSize = size;
		gSize = 0;
		graph = new list<int>[size];
	}
	//destructor
    ~graphType() {
		delete[] graph;
	}
};
