#include <iostream>
#include <cstdarg>
#include <vector>
#include <map>
#include "../include/Graph.hpp"


int main()
{
	Electrux::Graph graph;
	
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
	
	auto sd = graph.getShortestPath(1, 4);

	std::cout << "Shortest path: ";
	for( auto node : sd.path )
		std::cout << node << "->";
	std::cout << "\b\b  \n";

	std::cout << "Distance: " << sd.dist << "\n";

	return 0;
}

