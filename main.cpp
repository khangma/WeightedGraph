#include "weightedGraphType.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "ArgumentManager.h"
using namespace std;


int main(int argc, char* argv[]) {
	/*if (argc < 2) {
		cout << "Usage: main \"A=<file>;C=<file>\"" << endl;
		return -1;
	}

	// get input and output file names from arguments
	ArgumentManager am(argc, argv);
	string infilename = am.get("A");
	string outfilename = am.get("C");

	cout << "File name for matrix A: " << infilename << endl
		<< "File name for matrix C: " << outfilename << endl;

	ifstream inFile(infilename);
	ofstream outFile(outfilename);
	*/

	ifstream inFile("10.txt");
	int size = 0;
	string line;
	while (getline(inFile, line) && !line.empty()) {
		size++;
	}
	inFile.clear();
	inFile.seekg(0);
	weightedGraphType graph(size);
	graph.createWeightedGraph(inFile);
	inFile.close();
	if (graph.isError()) {
		cout << "";
		system("pause");
		return 0;
	}
	graph.printGraph();
	graph.printWeights();
	graph.minimnumSpanning(0);
	while (graph.getClust() > 0) {
		graph.deleteHighest();
	}

	int* edge = graph.getEdge();
	weightedGraphType spanningTree(size);
	for (int i = 0; i < size; i++) {
		spanningTree.addEdge(edge[i], i);
	}

	std::list<int>* cluster = new list<int>[size];

	bool * visited = new bool[size];
	for (int i = 0; i < size; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < size; i++) {
		if (!visited[i]) {
			bool * thingsToAdd = spanningTree.DepthFirstTraversal(i);
			for (int j = 0; j < size; j++) {
				if (thingsToAdd[j]) {
					cluster[i].push_back(j);
					visited[j] = true;
				}
			}
		}
	}
	for (int i = 0; i < size; i++) {
		if (cluster[i].empty())
			continue;
		else {
			for (auto v : cluster[i]) {
				cout << v << " ";
				//outFile << v << " ";
			}
			cout << endl;
			//outFile << endl;
		}
	}
	return 0;
}