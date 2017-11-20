#include <iostream>
#include <map>
#include <vector>
#include "Graph.hpp"

int main()
{
	Electrux::Graph graph;

	for( int i = 1; i <= 5; ++i )
		graph.AddNewNode( i );

	graph.AddEdge( 1, 2, 5 );
	graph.AddEdge( 2, 3, 2 );
	graph.AddEdge( 2, 5, 4 );
	graph.AddEdge( 3, 4, 1 );
	graph.AddEdge( 4, 5, 1 );

	auto shortest = graph.GetShortestPath( 1, 5 );

	std::cout << "Shortest Distance: " << shortest.dist << "\tShortest Path: ";
	Electrux::DisplayVector( shortest.nodes );
	std::cout << "\n";

	return 0;
}