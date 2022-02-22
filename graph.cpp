#include <iostream>
#include <queue>
#include <stack>
#include <random>
#include "graph.hpp"
using namespace std;

void visit(Graph& g, int curr, bool visited[])
{
	cout<<curr<<" ";
	visited[curr] = true;
	int *adj = g.adj(curr);
	for (int i = 0; i < g.V(); i++)
		if (adj[i] != INF && !visited[i])
		   visit(g, i, visited);
}

void dfs(Graph& g, int start)
{
	bool *visited = new bool[g.V()];
	for (int i = 0; i < g.V(); i++)
		visited[i] = false;
	cout<<"dfs visiting: ";
	visit(g, start, visited);
	cout<<"\n";
}

void connectedComponents(Graph& g)
{
	bool *visited = new bool[g.V()];
	for (int i = 0; i < g.V(); i++)
		visited[i] = false;
	cout<<"Connected Components:\n";
	int numCC = 1;
	for (int i = 0; i < g.V(); i++)
	{
        if (!visited[i])
        {
          cout<<"Component "<<numCC<<": ";
          visit(g, i, visited);
          cout<<endl;
          numCC++;
        }
    }
	cout<<"\n";
}

void showPath(int start, int stop, int pred[])
{
	stack<int> path;
	for (int crawl = stop; crawl != start; crawl = pred[crawl])
	{
		path.push(crawl);
	}
	cout<<start<<" -> ";
	while (!path.empty())
	{
	  cout<<path.top()<<" -> ";
	  path.pop();
	}
	cout<<"Finish.\n";
}

void Dijkstra(Graph& g, int start)
{
	int *dist = new int[g.V()];
	int *pred = new int[g.V()];
	for (int i = 0; i < g.V(); i++)
	{
		pred[i] = -1;
		dist[i] = INF;
	}
	priority_queue<pair<int,int>,
		       vector<pair<int,int>>,
		       greater<pair<int,int>>> pq;
	dist[start] = 0;
	pred[start] = start;
	pq.push(make_pair(0,start));
	while (!pq.empty())
	{
		int curr = pq.top().second;
		pq.pop();
		int *adj = g.adj(curr);
		for (int i = 0; i < g.V(); i++)
		{
			if (adj[i] != INF)
			{
				int ndist = dist[curr] + adj[i];
				if (dist[i] > ndist)
				{
					dist[i] = ndist;
					pred[i] = curr;
					pq.push(make_pair(dist[i], i));
				}

			}
		}
	}
	cout<<"Vertex   Distance from "<<start<<"  shortest path\n";
	for (int i = 0; i < g.V(); i++)
	{
		cout<<i<<"\t "<<dist[i]<<"\t";
		showPath(start, i, pred);
	}
}

void bfs(Graph& g, int start)
{
    bool *visited = new bool[g.V()];
    for (int i = 0; i < g.V(); i++)
        visited[i] = false;
    queue<int> fq;
    fq.push(start);
    visited[start] = true;
    cout<<"BFS visiting: ";
    while (!fq.empty())
    {
        int curr = fq.front();
        fq.pop();
        cout<<curr<<" ";
        int *adj = g.adj(curr);
        for (int u = 0; u < g.V(); u++)
        {
            if (adj[u] != INF && !visited[u])
            {
                fq.push(u);
                visited[u] = true;
            }
        }
    }
    cout<<endl;
}

int main(int argc, char *argv[])
{
	Graph g(41);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 40);
    for (int i = 0; i < 242; i++)
    {
       int v = dist(gen);
       int u = dist(gen);
       if (v != u)
            g.addWeightedEdge(v,u, rand() % 40);
    }
    g.show();
    connectedComponents(g);
    bfs(g, 5);
    Dijkstra(g, 0);
    return 0;
}
