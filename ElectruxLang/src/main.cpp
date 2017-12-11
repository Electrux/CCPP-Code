#include <iostream>
#include <fstream>
#include <vector>

#include "../include/StringFuncs.hpp"
#include "../include/DataTypes.hpp"

#include "../include/Lexer.hpp"

int main( int argc, char ** argv )
{
	std::fstream file;

	file.open( "./build/test.epl", std::ios::in );

	std::string line;

	std::vector< std::vector< DataType::Data > > data;

	while( std::getline( file, line ) ) {
		auto lineparts = DelimitString( line );

		int indent = GetIndentLevel( line );

		if( lineparts.empty() ||
		    lineparts[ 0 ] == DataType::KEYWORDS_STR[ DataType::LINECOMMENT ] )
			continue;

		std::cout << indent << " -> ";
		data.push_back( Lexer::ParseLexicoSymbols( lineparts ) );
	}

	return 0;
}
