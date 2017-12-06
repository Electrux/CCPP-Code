#include <vector>
#include <string>

#include "../include/ToVector.hpp"

std::vector< std::string > ToVector( int argc, char ** argv )
{
	std::vector< std::string > temp;

	for( int i = 0; i < argc; ++i ) {

		temp.push_back( argv[ i ] );
	}

	return temp;
}
