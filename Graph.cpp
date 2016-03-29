/* An implementation of an undirected graph using adjacency lists
 * Code by: Humayun Kabir, humayun.k1@gmail.com */

#include <iostream>
#include <fstream>
#include "linkedList.cpp"

class Graph {
private:
	//Number of vertices in the graph
	int n;
	
	//Adjacency list of each vertex
	LinkedList<int> *adj;

public:
	//Constructor
	Graph(int n) : n(n) {
		adj = new LinkedList<int>[n];
	}

	//Makes a graph from an input file
	//First line contains n m (number vertices and number edges)
	//each line contains an edge: i j (i is connected to j)
	Graph(char *fileName) {
		ifstream fileHandle(fileName);
		if( fileHandle.is_open() ) {

			int value, numToken = 0;
			int i, j;

			while( fileHandle >> value ) {
				numToken++;

				if( numToken == 1 ) {
					n = value;
					adj = new LinkedList<int>[n];
				}
				else if(numToken == 2) {
					cout<<"Number of Edges: "<<value<<endl;
				}
				else {
			
					if( numToken % 2 == 1) 
						i = value - 1;
					else {
						j = value - 1;
						adj[i].add(j);
						adj[j].add(i);
					}
				}
			}
			
			fileHandle.close();
		}
		else 
			cout<<"File could not be opened\n";
	}

	//add edge (v,w)
	void addEdge(int v, int w) {
		adj[v].add(w);
		adj[w].add(v);
	}

	//returns adjacency of a vertex v
	LinkedList<int> & adjList(int v) {
		return adj[v];
	}

	//returns number of vertices in the graph
	int N() {
		return n;
	}

	//returns number of edges in the graph
	int M() {
		int numEdges = 0;
		for(int v = 0; v < n; v++)
			numEdges += adj[v].size();
		return numEdges/2;
	}

	//returns degree of a vertex
	int degree(int v) {
		return adj[v].size();
	}

	//Destructor
       ~Graph() {
           delete [] adj;
       }
	

};


//test the graph
int main() {

	Graph g("graph2.txt");

	cout<<"Number of vertices: "<<g.N() <<endl;
	cout<<"Number of edges: "<<g.M() <<endl;

	int vertex = 0;
	
	cout<<"Degree of vertex "<< vertex<< " is: "<< g.degree(vertex) << endl;
	cout<<"Adjacency list of "<< vertex <<": \n";


	for(LinkedList<int>::iterator it = g.adjList(0).begin(); it != g.adjList(0).end(); it++) {
		cout<<*it<<endl;
	}
	return 0;
}
