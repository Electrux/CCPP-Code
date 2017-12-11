#include <iostream>
#include <fstream>

#include "../include/StringFuncs.hpp"

#include "../include/FileParser.hpp"

#include "../include/LangInterpreter/LanguageInterpreter.hpp"

int main( int argc, char ** argv )
{
	auto args = ToVector( argc, argv );

	if( args.size() < 2 ) {
		std::cerr << "Error: No file specified to parse from!" << std::endl;
		return 1;
	}

	FileParser parser;
	bool res = parser.ParseFile( args[ 1 ] );

	if( !res ) {
		std::cerr << "Error: Unable to parse specified file. Check if it exists."
			  << std::endl;
		return 1;
	}

	if( parser.GetTotalLines() == 0 ) {
		std::cerr << "Error: File to be parsed is empty!" << std::endl;
		return 1;
	}

	Interpreter interpreter( parser );

	return interpreter.Interpret();
}
