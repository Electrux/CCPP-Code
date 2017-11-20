#include <iostream>
#include "NodeList.hpp"

namespace Electrux
{
	struct ShortestPathData
	{
		int dist;
		std::vector<int> path;
	};

	class Graph
	{
		NodeList *start, *end;
		int directed;
		
		ShortestPathData CustomGetShortestPath(int src, int dest, std::vector<int> &path, int dist = 0);

		Data getSmallestDist(std::vector<Data> data);

	public:
		enum Direction
		{
			DIRECTED,
			UNDIRECTED
		};

		Graph();
		Graph(int direction);
		bool add_node(int id);
		bool delete_node(int id);
		void disp_node_tree(std::vector<int> vec);
		bool add_edge(int srcnode, int destnode, int weight);
		bool delete_edge(int from, int to);
		NodeList *GetNodeList(int _base);
		bool NodeListExists(int _base);
		int edge_exists(int from, int to);
		std::vector<int> getNodes();
		ShortestPathData getShortestPath(int src, int dest);
		Graph generateKruskalGraph();
		void arrangeVisits(std::vector<mnode> &vec);
		bool findInVector(std::vector<mnode> &vec, int id);
		friend std::ostream & Graph::operator << (std::ostream &os, const Graph &graph);
	};
}
