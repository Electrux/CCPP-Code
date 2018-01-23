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

	std::vector< std::vector< DataType::Data > > alldata;

	while( std::getline( file, line ) ) {
		if( line.empty() || line == "\n" )
			continue;

		auto dataline = Lexer::ParseLexicoSymbols( line );
		if( !dataline.empty() )
			alldata.push_back( dataline );
	}

	return 0;
}
