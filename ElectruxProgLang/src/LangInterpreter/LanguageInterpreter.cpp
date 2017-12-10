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

		int retval = ExecuteLine( lines, i );
		if( retval != OK )
			return retval;
	}

	return OK;
}

int Interpreter::ExecuteLine( const std::vector< std::string > & lines, int & line )
{
	std::vector< std::string > lineparts = DelimitString( lines[ line ] );

	if( lineparts.empty() || lineparts[ 0 ][ 0 ] == '#' ) {
		line++;
		return OK;
	}

	if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::BREAK ] ) {
		line++;
		return BREAK;
	}

	if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::CONTINUE ] ) {
		line++;
		return CONTINUE;
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
	else if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::IF ] ||
		 lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::ELSEIF ] ) {

		// Modifies the line value to skip till end condition.
		retval |= InterpretConditional( lines, lineparts, line );
	}
	else if( lineparts[ 0 ] == COMMANDS_STRING[ COMMANDS::FOR ] ) {

		// Modifies the line value to skip till end condition.
		retval |= InterpretLoop( lines, lineparts, line );
	}
	else {
		line++;
	}

	return retval;
}

int Interpreter::InterpretPrint( std::vector< std::string > & lineparts, int line )
{
	if( lineparts.size() < 2 ) {
		std::cerr << "Error on line: " << line
			  << "\n\tNothing specified to print!" << std::endl;
		return ERR;
	}

	std::string formattedstring;

	if( FormatString( lineparts, formattedstring, line ) != 0 )
		return ERR;

	std::cout << formattedstring << std::endl;

	return OK;
}

int Interpreter::InterpretNewVar( std::vector< std::string > & lineparts, int line )
{
	// New var is in four parts: var varname = varval

	if( lineparts.size() < 4 || lineparts[ 2 ] != "=" ) {
		std::cerr << "Error on line: " << line
			  << "\n\tNeed to use format:"
			  << "\n\t\tvar <varname> = <val>" << std::endl;
		return ERR;
	}

	DataTypes type = GetType( lineparts[ 1 ] );
	if( type == INT || type == FLT ) {
		std::cerr << "Error on line: " << line
			  << "\n\tAttempted to create a variable with integer name!"
			  << std::endl;
		return ERR;
	}

	if( AddVariable( lineparts[ 1 ], lineparts[ 3 ], line ) != OK )
		return ERR;

	return OK;
}

int Interpreter::InterpretScan( std::vector< std::string > & lineparts, int line )
{
	if( lineparts.size() < 2 ) {
		std::cerr << "Error on line: " << line
			  << "\n\tNo variable provided to scan to!" << std::endl;
		return ERR;
	}

	std::string temp;

	for( int i = 1; i < ( int )lineparts.size(); ++i ) {

		std::getline( std::cin, temp );

		if( AddVariable( lineparts[ i ], temp, line, false ) != OK )
			return ERR;
	}

	return OK;
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
		return ERR;
	}

	int indentlevel = GetIndentLevel( lines[ line ] );

	int endline = -1, elseline = -1;

	std::vector< int > elseifs;

	for( int i = line + 1; i < ( int )lines.size(); ++i ) {

		if( GetWord( lines[ i ], 0 ) == COMMANDS_STRING[ COMMANDS::ENDIF ] &&
		    indentlevel == GetIndentLevel( lines[ i ] ) ) {

			endline = i;
			break;
		}

		if( GetWord( lines[ i ], 0 ) == COMMANDS_STRING[ COMMANDS::ELSEIF ] &&
		    indentlevel == GetIndentLevel( lines[ i ] ) ) {

			elseifs.push_back( i );
		}

		if( GetWord( lines[ i ], 0 ) == COMMANDS_STRING[ COMMANDS::ELSE ] &&
		    indentlevel == GetIndentLevel( lines[ i ] ) ) {

			elseline = i;
		}
	}

	if( endline == -1 ) {
		std::cerr << "Error on line: " << line + 1
			  << "\n\tConditional is started here but it never ends!"
			  << " Note that in conditionals and loops, indentation matters!"
			  << std::endl;
		return ERR;
	}

	int res = EvalCondition( lineparts, line );
	if( res == -1 )
		return ERR;

	int retval = 0;

	int executetill = endline;

	bool donesomeif = false;

	if( elseifs.empty() ) {
		if( elseline != -1 ) {
			executetill = elseline;
		}
	}
	else {
		executetill = * elseifs.begin();
	}

	if( res == OK ) {

		donesomeif = true;

		for( line += 1; line < executetill; ) {

			retval |= ExecuteLine( lines, line );

			if( ( retval & BREAK ) == BREAK ||
			    ( retval & CONTINUE ) == CONTINUE )
				break;
			if( retval != OK )
				return retval;
		}
	}
	else if( !elseifs.empty() ) {

		int finalline = elseline != - 1 ? elseline : endline;

		for( auto elseif = elseifs.begin(); elseif != elseifs.end(); ++elseif ) {

			std::vector< std::string > templineparts =
				DelimitString( lines[ * elseif ] );

			int eval = EvalCondition( templineparts, * elseif );

			if( eval == -1 )
				return ERR;

			if( eval == OK ) {

				donesomeif = true;

				executetill = ( elseif == elseifs.end() - 1 )
					? finalline : ( * ( elseif + 1 ) );

				for( line = ( * elseif ) + 1; line < executetill; ) {

					retval |= ExecuteLine( lines, line );

					if( ( retval & BREAK ) == BREAK ||
					    ( retval & CONTINUE ) == CONTINUE )
						break;
					if( retval != OK )
						return retval;
				}

				break;
			}
		}
	}

	if( elseline != -1 && !donesomeif ) {

		for( line = elseline + 1; line < endline; ) {

			retval |= ExecuteLine( lines, line );

			if( ( retval & BREAK ) == BREAK ||
			    ( retval & CONTINUE ) == CONTINUE )
				break;
			if( retval != OK )
				return retval;
		}
	}

	line = endline + 1;

	return retval;
}

int Interpreter::InterpretLoop( const std::vector< std::string > & lines,
			   const std::vector< std::string > & lineparts,
			   int & line )
{
	// Format is:
	// for x in a .. b :
	//     TODO
	// rof

	if( lineparts.size() < 7 ) {
		std::cerr << "Error on line: " << line + 1
			  << "\n\tFormat for if is:"
			  << "\n\t\tfor x in a .. b :" << std::endl;
		return ERR;
	}

	auto replvalleft = GetReplacementValue( lineparts[ 3 ], line + 1 );
	auto replvalright = GetReplacementValue( lineparts[ 5 ], line + 1 );

	auto typeleft = GetType( replvalleft );
	auto typeright = GetType( replvalright );

	if( typeleft != typeright ) {
		std::cerr << "Error on line: " << line + 1
			  << "\n\tThe types of both limits in range must be same!"
			  << std::endl;
		return ERR;
	}

	if( typeleft == FLT || typeleft == STR ) {
		std::cerr << "Error on line: " << line + 1
			  << "\n\tThe types of the limits can be nothing except integers!"
			  << std::endl;
		return ERR;
	}

	int rangeleft = std::stoi( replvalleft );
	int rangeright = std::stoi( replvalright );

	std::string var = lineparts[ 1 ];

	int originalline = line;

	if( AddVariable( var, "0", originalline + 1 ) != OK )
		return ERR;

	int indentlevel = GetIndentLevel( lines[ line ] );

	int endline = -1;

	for( int i = line + 1; i < ( int )lines.size(); ++i ) {

		if( GetWord( lines[ i ], 0 ) == COMMANDS_STRING[ COMMANDS::ENDFOR ] &&
		    indentlevel == GetIndentLevel( lines[ i ] ) ) {

			endline = i;
			break;
		}
	}

	if( endline == -1 ) {
		std::cerr << "Error on line: " << line + 1
			  << "\n\tLoop is started here but it never ends!"
			  << " Note that in conditionals and loops, indentation matters!"
			  << std::endl;
		return ERR;
	}

	int retval = 0;

	bool breakloop = false;

	while( rangeleft < rangeright ) {

		if( UpdateVariable( var, std::to_string( rangeleft ), line + 1 ) != OK )
			return ERR;

		for( int ln = line + 1; ln < endline; ) {

			int prevret = retval;

			retval |= ExecuteLine( lines, ln );

			if( ( retval & CONTINUE ) == CONTINUE ) {
				retval = prevret;
				break;
			}
			else if( ( retval & BREAK ) == BREAK ) {
				breakloop = true;
				break;
			}
			else if( retval != OK ) {
				return retval;
			}
		}

		if( breakloop )
			break;

		rangeleft++;
	}

	DeleteVariable( var, originalline + 1 );

	line = endline + 1;

	return OK;
}
