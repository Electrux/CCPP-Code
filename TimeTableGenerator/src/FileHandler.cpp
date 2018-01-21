#include <string>
#include <vector>
#include <fstream>

#include "../include/DisplayFuncs.hpp"
#include "../include/DataStructure.hpp"

#include "../include/FileHandler.hpp"

std::vector< Data > RetrieveFile( const std::string & filename )
{
	std::vector< Data > alldata;

	std::fstream file;
	file.open( filename, std::ios::in );

	if( !file ) {
		DisplayData( "{R}Error: File not found: {C}" + filename + "\n" );
		return alldata;
	}

	std::string line;

	int ctr = 0;

	while( std::getline( file, line ) ) {
		if( line.empty() || line == "\n" )
			continue;

		Data data = DelimLineToData( line );
		if( data.name.empty() )
			continue;

		alldata.push_back( data );
		++ctr;
	}

	file.close();

	DisplayData( "{G}Info: Loaded {C}" + std::to_string( ctr ) + " {G}distinct values from file.\n" );

	return alldata;
}