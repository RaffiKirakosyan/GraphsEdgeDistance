// Graph course work.cpp : Defines the entry point for the Eole application.
//

#include "stdafx.h"/
#include <iostream>
#include <vector>
#include <queue>

class Graph{
private:

	struct Vertice { 

		int name;

		Vertice(int n) 
			:name(n)
		{}
	};

	struct Edge {
	
		Vertice e1;
		Vertice e2;

		Edge(Vertice ed1, Vertice ed2)
			:e1(ed1),
			e2(ed2)
		{ }
		void print() {
			std::cout << e1.name << " - " << e2.name << std::endl;
		}

	};

	std::vector<int> *Ver;
	
	//Helpers
	
	int minPathBFS_Helper(std::vector<int> edges[], int u, int v, int n){
		// BFS distance checker

		// visited[n] = 0 for all Vertice
		std::vector<bool> visited(n, 0);
		std::vector<int> distance(n, 0);
		std::queue<int> Q;

		distance[u] = 0;

		Q.push(u);
		visited[u] = true;
		while (!Q.empty())
		{
			int x = Q.front();
			Q.pop();

			for (int i = 0; i<edges[x].size(); i++)
			{
				if (visited[edges[x][i]])
					continue;

				// update distance for i
				distance[edges[x][i]] = distance[x] + 1;
				Q.push(edges[x][i]);
				visited[edges[x][i]] = 1;
			}
		}

		return distance[v];
	}
	
	void addVertice(std::vector<int> verts[], int u, int v)
	{
		verts[u].push_back(v);
		verts[v].push_back(u);
	}

public:
	
	// 
	std::vector<Vertice> V;
	std::vector<Edge> E;
	
	//methods
	Graph() {
	
	}
	~Graph() { 
		clear(); 
	}


	void insert() {
		std::cout << "Graph's Vertices count : ";
		int v, i=1;
		std::cin >> v;
		
		while (i<=8) {

			if (v == 0) {
				return;
			}
			V.push_back(Vertice(i++));
		}
		std::cout << "\nGraph's Edges\nFrom - To[example a - b]" << std::endl;
		while (true) {
		
			char l;
			int v1, v2;

			std::cin >> v1 >> l >> v2;
			
			if (v1 == 0 && v1 == 0) {
				break;
			}
			E.push_back(Edge(Vertice(v1), Vertice(v2)));
		}

		std::cout << std::endl;		
	}

	void clear() {
		E.clear();
		std::cout << "\nGraph is cleared" << std::endl;
	}
	
	int Distance(Vertice eF, Vertice eT) {
		Ver = new std::vector<int>[E.size()];
		int ret;
		for (int i = 0; i < E.size(); ++i) {
			addVertice(Ver, E[i].e1.name, E[i].e2.name);
		}
		ret = minPathBFS_Helper(Ver, eF.name, eT.name, E.size());
		delete[] Ver;
		return ret;
	}

	void VerticeDistanceList(){

		Ver = new std::vector<int>[E.size()];

		for (int i = 0; i < E.size(); ++i) {
			addVertice(Ver, E[i].e1.name, E[i].e2.name);
		}

		std::cout << "F - T : Dist\n";
		for (int u = 1; u < E.size(); ++u) {
			for (int v = u+1; v < E.size(); ++v) {
				std::cout << u << " - " << v << " : ";
				std::cout << minPathBFS_Helper(Ver, u, v, E.size()) << std::endl;
			}
		}
		delete[] Ver;
	}

};


int main()
{
	/*
	[example]
	8

	1 - 2
	1 - 3
	1 - 4
	2 - 5
	4 - 5
	3 - 4
	3 - 6
	5 - 7
	6 - 7
	0 - 0


	*/

	Graph G;
	G.insert();
	
	system("cls");
	
	std::cout << "Vertices" << std::endl;

	for (int i = 1; i <= G.V.size(); ++i) {
		std::cout << i << "  ";
	}
	
	std::cout << std::endl;
	
	std::cout << "Edges\nF - T" << std::endl;
	
	int i = 0;
	while (i!=G.E.size()) {
		G.E[i++].print();
	}

	std::cout << std::endl;

	G.VerticeDistanceList();
	
	std::cout << "\nSet 2 Vertice number from this range[1.." << G.V.size() << "] : ";
	int from, to;
	std::cin >> from >> to;
	std::cout << "Distance between "<<from << " and "<< to << " is: "<< G.Distance(from, to) << std::endl;

	return 0;
}
