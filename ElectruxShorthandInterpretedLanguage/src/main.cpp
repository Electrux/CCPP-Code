#include <iostream>
#include <fstream>
#include <vector>

#include "../include/StringFuncs.hpp"
#include "../include/DataTypes.hpp"
#include "../include/Functions.hpp"
#include "../include/Vars.hpp"

#include "../include/Executor.hpp"

#include "../include/Lexer.hpp"

int main( int argc, char ** argv )
{
	std::fstream file;

	if( argc < 2 )
		file.open( "./test.epl", std::ios::in );
	else
		file.open( argv[ 1 ], std::ios::in );

	std::string line;

	std::vector< std::vector< DataType::Data > > alldata;

	int fileline = 1;
	while( std::getline( file, line ) ) {
		if( line.empty() || line == "\n" ) {
			++fileline;
			continue;
		}

		auto dataline = Lexer::ParseLexicoSymbols( line, fileline );
		if( !dataline.empty() )
			alldata.push_back( dataline );
		++fileline;
	}

	file.close();

	std::cout << "\n\nExecuting...\n\n";

	Vars::InitializeVars( argc, ( const char ** )argv );

	ExecuteAll( alldata );

	// Cleanup
	Function::DelAllFuncs();
	Vars::DelAllVars();

	return 0;
}
