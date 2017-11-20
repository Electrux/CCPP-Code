//
// Created by Electrux Redsworth on 9/24/17.
//

#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <string>
#include <map>
#include <vector>
#include <iostream>

namespace Electrux
{
	void DisplayVector( std::vector<int> vec )
	{
		std::cout << "{ ";

		for( auto num : vec )
			std::cout << num << ", ";

		std::cout << "\b\b }";
	}

	struct ShortestPathData
	{
		int dist;
		std::vector<int> nodes;
	};

	class Graph
	{
		std::map<int, std::map<int, int> > nodes;

		ShortestPathData GetShortestPathFor( int from, int to, std::vector<int> path, int dist )
		{
			if( std::find( path.begin(), path.end(), from ) != path.end()) return { -1, path };
			if( std::find( path.begin(), path.end(), to ) != path.end()) return { dist, path };

			path.push_back( from );

			auto nodelist = nodes[ from ];

			std::vector<ShortestPathData> newlocations;
			for( auto new_to : nodelist ) {
				if( new_to.first == to ) {
					path.push_back( new_to.first );
					dist += new_to.second;

					newlocations.push_back( { dist, path } );

					path.pop_back();
					dist -= new_to.second;
				} else {
					newlocations.push_back(
						GetShortestPathFor( new_to.first, to, path, dist + new_to.second ));
				}
			}

			ShortestPathData min = { -1, path };

			for( auto locs : newlocations ) {
				if( locs.dist > 0 ) {
					if( locs.dist < min.dist || min.dist == -1 )
						min = locs;
				}
			}

			return min;
		}

	public:

		bool AddNewNode( int nodeval )
		{
			if( NodeExists( nodeval )) return false;

			nodes.insert( { nodeval, std::map<int, int>() } );

			return true;
		}

		std::map<int, int> GetNodeConnections( int nodeval )
		{
			if( !NodeExists( nodeval )) return std::map<int, int>();

			return nodes[ nodeval ];
		}

		bool DeleteNode( int nodeval )
		{
			if( !NodeExists( nodeval )) return false;

			nodes.erase( nodeval );

			return true;
		}

		bool AddEdge( int fromnode, int tonode, int dist )
		{
			if((!NodeExists( fromnode ) ||
			    !NodeExists( tonode )))
				return -1;

			if( GetDistance( fromnode, tonode ) > 0 ) return false;

			nodes[ fromnode ][ tonode ] = dist;
			nodes[ tonode ][ fromnode ] = dist;


			return true;
		}

		bool DeleteEdge( int fromnode, int tonode )
		{
			if( !NodeExists( fromnode ) ||
			    !NodeExists( tonode ))
				return -1;

			if( GetDistance( fromnode, tonode ) <= 0 ) return false;

			nodes[ fromnode ].erase( tonode );
			nodes[ tonode ].erase( fromnode );

			return true;
		}

		ShortestPathData GetShortestPath( int fromnode, int tonode )
		{

			ShortestPathData shortestpath;
			shortestpath.dist = 0;

			if( !NodeExists( fromnode ) ||
			    !NodeExists( tonode ))
				return shortestpath;

			shortestpath = GetShortestPathFor( fromnode, tonode, shortestpath.nodes, shortestpath.dist );

			return shortestpath;
		}

		std::vector<int> GetAllNodes()
		{
			std::vector<int> allnodes;

			for( auto n : nodes )
				allnodes.push_back( n.first );

			return allnodes;
		}

		int GetDistance( int fromnode, int tonode )
		{
			if( !NodeExists( fromnode ) ||
			    !NodeExists( tonode ))
				return -1;

			if( fromnode == tonode ) return 0;

			if( nodes[ fromnode ].find( tonode ) != nodes[ fromnode ].end()) return 0;

			return nodes[ fromnode ][ tonode ];
		}

		bool NodeExists( int nodeval )
		{
			return !(nodes.find( nodeval ) == nodes.end());
		}

		int GetNodeCount()
		{
			return ( int ) nodes.size();
		}

		void DisplayAll()
		{
			for( auto edges : nodes ) {
				std::cout << "Node: " << edges.first << " is connected with:\n";
				for( auto edge : edges.second ) {
					TabbedValDisplay( 1, edge.first );
				}
				std::cout << "\n";
			}
		}

		void TabbedValDisplay( int level, int val )
		{
			for( int i = 0; i < level; ++i )
				std::cout << "\t";

			std::cout << val << "\n";
		}

	};
}

#endif //GRAPH_HPP
