#include <iostream>
#include <vector>
#include <string>
#include <climits>

#include "../../include/Commands.hpp"
#include "../../include/FileParser.hpp"
#include "../../include/StringFuncs.hpp"

#include "../../include/LangInterpreter/LanguageInterpreter.hpp"

Interpreter::Interpreter( FileParser & parser ) : lines( parser.GetAllLines() )
{}

int Interpreter::Interpret()
{
	if( lines.empty() )
		return false;

	int retval = 0;

	for( int i = 0; i < ( int )lines.size(); ++i ) {

		std::vector< std::string > lineparts = DelimitString( lines[ i ] );

		if( lineparts.empty() || lineparts[ 0 ][ 0 ] == '#' )
			continue;

		if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::PRINT ]  ) {

			retval |= InterpretPrint( lineparts, i + 1 );
		}
		else if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::VAR ] ) {

			retval |= InterpretNewVar( lineparts, i + 1 );
		}
		else if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::SCAN ] ) {

			retval |= InterpretScan( lineparts, i + 1 );
		}

		if( retval != 0 )
			return retval;
	}

	return retval;
}

int Interpreter::InterpretPrint( std::vector< std::string > & lineparts, int line )
{
	if( lineparts.size() < 2 ) {
		std::cerr << "Error on line: " << line
			  << "\n\tNothing specified to print!" << std::endl;
		return 1;
	}

	std::string formattedstring;

	if( FormatString( lineparts, formattedstring, line ) != 0 )
		return 1;

	std::cout << formattedstring << std::endl;

	return 0;
}

int Interpreter::InterpretNewVar( std::vector< std::string > & lineparts, int line )
{
	// New var is in four parts: var varname = varval

	if( lineparts.size() < 4 || lineparts[ 2 ] != "=" ) {
		std::cerr << "Error on line: " << line
			  << "\n\tNeed to use format:\n\t\tvar <varname> = <val>!" << std::endl;
		return 1;
	}

	if( IsInt( lineparts[ 1 ] ) != INT_MIN ) {
		std::cerr << "Error on line: " << line
			  << "\n\tAttempted to create a variable with integer name!"
			  << std::endl;
		return 1;
	}

	if( intvars.find( lineparts[ 1 ] ) != intvars.end() ||
	    strvars.find( lineparts[ 1 ] ) != strvars.end() ) {
		std::cerr << "Error on line: " << line
			  << "\n\tRedeclaration of a previously created variable: "
			  << lineparts[ 1 ] << std::endl;
		return 1;
	}

	if( AddVariable( lineparts[ 1 ], lineparts[ 3 ], line ) != 0 )
		return 1;

	return 0;
}

int Interpreter::InterpretScan( std::vector< std::string > & lineparts, int line )
{
	if( lineparts.size() < 2 ) {
		std::cerr << "Error on line: " << line
			  << "\n\tNo variable provided to scan to!" << std::endl;
		return 1;
	}

	std::string temp;

	for( int i = 1; i < ( int )lineparts.size(); ++i ) {

		std::getline( std::cin, temp );

		if( AddVariable( lineparts[ i ], temp, line, false ) != 0 )
			return 1;
	}

	return 0;
}

