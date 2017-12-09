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

	for( int i = 0; i < ( int )lines.size(); ) {

		if( ExecuteLine( lines, i ) != 0 )
			return 1;
	}

	return 0;
}

int Interpreter::ExecuteLine( const std::vector< std::string > & lines, int & line )
{
	std::vector< std::string > lineparts = DelimitString( lines[ line ] );

	if( lineparts.empty() || lineparts[ 0 ][ 0 ] == '#' ) {
		line++;
		return 0;
	}

	int retval = 0;

	if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::PRINT ]  ) {

		retval |= InterpretPrint( lineparts, line + 1 );
		line++;
	}
	else if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::SCAN ] ) {

		retval |= InterpretScan( lineparts, line + 1 );
		line++;
	}
	else if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::VAR ] ) {

		retval |= InterpretNewVar( lineparts, line + 1 );
		line++;
	}
	else if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::IF ] ) {

		// Modifies the line value to skip till end condition.
		retval |= InterpretConditional( lines, lineparts, line );
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
			  << "\n\tNeed to use format:"
			  << "\n\t\tvar <varname> = <val>" << std::endl;
		return 1;
	}

	DataTypes type = GetType( lineparts[ 1 ] );
	if( type == INT || type == FLT ) {
		std::cerr << "Error on line: " << line
			  << "\n\tAttempted to create a variable with integer name!"
			  << std::endl;
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

int Interpreter::InterpretConditional( const std::vector< std::string > & lines,
				       const std::vector< std::string > & lineparts,
				       int & line )
{
	// Format is:
	// if x CONDITION y :
	//     TODO
	// fi

	if( lineparts.size() < 5 ) {
		std::cerr << "Error on line: " << line + 1
			  << "\n\tFormat for if is:"
			  << "\n\t\tif a CONDITION b :" << std::endl;
		return 1;
	}

	int indentlevel = GetIndentLevel( lines[ line ] );

	int endline = -1;
	for( int i = line + 1; i < ( int )lines.size(); ++i ) {

		if( GetWord( lines[ i ], 0 ) == COMMANDS_STRING[ COMMANDS::ENDIF ] &&
		    indentlevel == GetIndentLevel( lines[ i ] ) ) {

			endline = i;
		}
	}

	if( endline == -1 ) {
		std::cerr << "Error on line: " << line + 1
			  << "\n\tConditional is started here but it never ends!"
			  << " Note that in conditionals and loops, indentation matters!"
			  << std::endl;
		return 1;
	}

	int res = EvalCondition( lineparts, line );
	if( res == -1 )
		return 1;

	int retval = 0;

	if( res ) {

		for( line += 1; line < endline; ) {
			retval |= ExecuteLine( lines, line );

			if( retval != 0 )
				return 1;
		}
	}
	else {
		line = endline;
	}

	line++;

	return retval;
}
