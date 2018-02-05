#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "../../include/Errors.hpp"
#include "../../include/DataTypes.hpp"
#include "../../include/Executor.hpp"
#include "../../include/Lexer.hpp"

#include "../../include/LineTypeHandler/ModuleLoader.hpp"

ErrorTypes LoadModule( const std::vector< DataType::Data > & dataline )
{
	if( dataline.size() < 3 ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": Module loading requires a name!" << std::endl;
		return SYNTAX_ERROR;
	}

	std::fstream file;

	file.open( dataline[ 2 ].word + ".emod", std::ios::in );

	if( !file ) {
		std::cerr << "Error on line: " << dataline[ 0 ].fileline << ": No module named: " << dataline[ 2 ].word << std::endl;
		return ENTITY_NOT_FOUND;
	}

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

	ExecuteAll( alldata );

	return SUCCESS;
}