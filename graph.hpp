#ifndef GRAPH_HPP
#define GRAPH_HPP
#include <iostream>
using namespace std;

const int INF = 0x47474747;

class Graph {
	private:
	int **adjMatrix;
	int _V;
	public:
	Graph(int max = 5)
	{
		_V = max;
		adjMatrix = new int*[_V];
		for (int i = 0; i < _V; i++)
		{
			adjMatrix[i] = new int[_V];
			for (int j = 0; j < _V;  j++)
				adjMatrix[i][j] = INF;
		}
	}
	void addEdge(int v, int u)
	{
		adjMatrix[v][u] = 1;
		adjMatrix[u][v] = 1;
	}
	void addWeightedEdge(int v, int u, int wt)
	{
		adjMatrix[v][u] = wt;
		adjMatrix[u][v] = wt;
	}
	int* adj(int v)
	{
		return adjMatrix[v];
	}
	void show()
	{
		cout<<"   ";
		for (int i = 0; i < _V; i++)
			cout<<i<<" ";
		cout<<endl;
		for (int i = 0; i < _V; i++)
		{
			cout<<i<<": ";
			for (int j = 0; j < _V; j++)
			{
				if (adjMatrix[i][j] == INF)
					cout<<"% ";
				else
					cout<<adjMatrix[i][j]<<" ";
			}
			cout<<endl;
		}
	}
	int V()
	{
		return _V;
	}
};

#endif
