#include <iomanip>
#include <fstream>
#include <sstream>
#include <climits>
#include "graphType.h"

using namespace std;

class weightedGraphType : public graphType
{
public:
	void createWeightedGraph(istream& input) {
		string line;
		int i = 0;
		//create graph
		while (getline(input, line) && !line.empty()) {
			stringstream ss(line);
			string num;
			while (ss >> num) {
				int v = stoi(num);
				addEdge(i, v);
			}
			i++;
		}

		//create weight matrix
		i = 0;
		while (getline(input, line) && !line.empty()) {
			int countWeight = 0;
			int j = 0;
			stringstream ss(line);
			string num;
			while (ss >> num) {
				int w = stoi(num);
				weights[i][j] = w;
				if (weights[i][j] > 0)
					countWeight++;
				j++;
			}
			if (graph[i].size() != countWeight)
				error = true;
			i++;
		}
		//read in how many clusters there are
		getline(input, line);
		if (!line.empty())
			clusters = stoi(line);
		else
			error = true;
		if (clusters  < 1 || clusters > gSize)
			error = true;
	}

	//create the minimum spanning tree
	void minimnumSpanning(int sourceVertex) {
		int start, end;
		int minWeight;
		bool *visited = new bool[gSize];

		for (int i = 0; i < gSize; i++) {
			visited[i] = false;
			edges[i] = sourceVertex;
			edgeWeights[i] = weights[sourceVertex][i];
		}
		visited[sourceVertex] = true;
		edgeWeights[sourceVertex] = 0;

		for (int i = 0; i < gSize - 1; i++) {
			minWeight = INT_MAX;
			for (int j = 0; j < gSize; j++) {
				if (visited[j]) {
					for (int k = 0; k < gSize; k++) {
						if (!visited[k] && weights[j][k] < minWeight && weights[j][k] > 0) {
							end = k;
							start = j;
							minWeight = weights[j][k];
						}
					}
				}
			}
			visited[end] = true;
			edges[end] = start;
			cout << "new edge: " << start << "-" << end << endl;
			edgeWeights[end] = minWeight;
		}
	}

	//find the edge with the highest weight in minimum spanning tree
	int findHighest() {
		int max = 0;
		int maxI = 0;
		for (int i = 0; i < gSize; i++) {
			if (edgeWeights[i] > max) {
				maxI = i;
				max = edgeWeights[i];
			}
		}
		return maxI;
	}

	//return the number of vertices
	int getSize() {
		return gSize;
	}


	bool isError() {
		return error;
	}

	//return the number of clusters
	int getClust() {
		return clusters;
	}

	//function to delete the edge with the highest weight
	void deleteHighest() {
		clusters--;
		while (clusters != 0) {
			int highest = findHighest();
			cout << "deleting " << edges[highest] << "-" << highest << endl;
			edges[highest] = highest;
			edgeWeights[highest] = 0;
			clusters--;
		}
	}
	//return the pointer
	int* getEdge() {
		return edges;
	}
	bool DFT(int vertex, bool visited[]) {
		visited[vertex] = true;

		for (auto v : graph[vertex]) {
			if (!visited[v])
				DFT(v, visited);
		}
		return visited;
	}
	bool* DepthFirstTraversal(int vertex) {
		bool *visited = new bool[gSize];
		for (int i = 0; i < gSize; i++) {
			visited[i] = false;
		}
		DFT(vertex, visited);
		return visited;
	}
	void printWeights() {
		for (int i = 0; i < gSize; i++) {
			for (int j = 0; j < gSize; j++) {
				if (weights[i][j] == -999) {
					cout << "-\t";
				}
				else {
					cout << weights[i][j] << "\t";
				}
			}
			cout << endl;
		}
		cout << endl;
	}

	weightedGraphType(int size = 0) : graphType(size) {
		weights = new int*[size];
		for (int i = 0; i < size; i++)
			weights[i] = new int[size];
		edges = new int[size];
		edgeWeights = new int[size];
		clusters = -1;
		error = false;
	}
	~weightedGraphType() {
		for (int i = 0; i < gSize; i++)
			delete[] weights[i];
		delete[] weights;
		delete[] edges;
		delete[] edgeWeights;
	}
protected:
	bool error;
	int clusters;
	int *edges;
	int **weights; //pointer to create weight matrix
	int *edgeWeights; //pointer to create the array to store
	//the smallest weight from source to vertices
};



