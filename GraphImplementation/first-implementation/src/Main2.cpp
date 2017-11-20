#include <iostream>
#include <cstdarg>
#include <vector>
#include <map>
#include "Graph.hpp"


int main()
{
	Electrux::Graph graph(Electrux::Graph::Direction::UNDIRECTED);

	/*
	graph.add_node(1);
	graph.add_node(2);
	graph.add_node(3);
	graph.add_node(4);
	graph.add_node(5);
	graph.add_node(6);

	graph.add_edge(1, 2, 1);
	graph.add_edge(1, 3, 3);
	graph.add_edge(1, 6, 2);
	graph.add_edge(2, 3, 3);
	graph.add_edge(2, 5, 5);
	graph.add_edge(3, 4, 6);
	graph.add_edge(6, 4, 1);
	graph.add_edge(6, 5, 4);
	//*/
	///*
	graph.add_node(1);
	graph.add_node(2);
	graph.add_node(3);
	graph.add_node(4);
	graph.add_node(5);
	graph.add_node(6);

	graph.add_edge(1, 2, 1);
	graph.add_edge(1, 6, 5);
	graph.add_edge(1, 3, 9);
	graph.add_edge(2, 3, 4);
	graph.add_edge(2, 4, 15);
	graph.add_edge(2, 6, 3);
	graph.add_edge(3, 4, 10);
	graph.add_edge(4, 5, 7);
	graph.add_edge(6, 4, 11);
	//*/
	/*
	graph.add_node(1);
	graph.add_node(2);
	graph.add_node(3);
	graph.add_node(4);
	graph.add_node(5);
	graph.add_node(6);
	graph.add_node(7);

	graph.add_edge(1, 2, 25);
	graph.add_edge(1, 6, 10);
	graph.add_edge(2, 3, 14);
	graph.add_edge(2, 7, 12);
	graph.add_edge(3, 4, 4);
	graph.add_edge(4, 7, 17);
	graph.add_edge(4, 5, 20);
	graph.add_edge(5, 7, 22);
	graph.add_edge(5, 6, 23);
	//*/
	//auto sd = graph.getShortestPath(1, 5); //Will show all possible paths.
	
	auto ktree = graph.generateKruskalGraph();

	std::cout << ktree << "\n";
	/*
	std::cout << "\n\n\nShortest distance: " << sd.dist << " and path: ";
	graph.disp_node_tree(sd.path);
	std::cout << "\n\n";
	*/
	system("pause");
	return 0;
}
