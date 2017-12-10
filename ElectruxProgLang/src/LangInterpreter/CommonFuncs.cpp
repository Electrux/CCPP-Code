#include <iostream>
#include <vector>
#include <string>
#include <climits>

#include "../../include/Commands.hpp"
#include "../../include/FileParser.hpp"
#include "../../include/StringFuncs.hpp"
#include "../../include/DataTypes.hpp"

#include "../../include/LangInterpreter/LanguageInterpreter.hpp"

COMMANDS Interpreter::GetReturnCode( int val )
{
	if( val == 0 )
		return OK;

	

	return ERR;
}

int Interpreter::DeleteVariable( const std::string & var, int line )
{
	if( intvars.find( var ) != intvars.end() ) {

		intvars.erase( var );
		return 0;
	}

	if( strvars.find( var ) != strvars.end() ) {

		strvars.erase( var );
		return 0;
	}

	if( fltvars.find( var ) != fltvars.end() ) {

		fltvars.erase( var );
		return 0;
	}

	std::cerr << "Error on line: " << line
		  << "\n\tAttempted to delete a nonexistent variable: "
		  << var << std::endl;
	return 1;
}

int Interpreter::UpdateVariable( const std::string & var,
			      const std::string & val,
			      int line, bool isvarcheck )
{
	if( intvars.find( var ) == intvars.end() &&
	    strvars.find( var ) == strvars.end() &&
	    fltvars.find( var ) == fltvars.end() ) {
		std::cerr << "Error on line: " << line
			  << "\n\tAttempted to update a nonexistent variable: "
			  << var << std::endl;
		return 1;
	}

	DataTypes dt = GetType( val );

	if( dt == INT ) {

		intvars[ var ] = std::stoi( val );
	}
	else if( dt == FLT ) {

		fltvars[ var ] = std::stof( val );
	}
	else {
		if( !IsConstString( val ) ) {

			std::string tempval = val;

			if( isvarcheck && !GetVarVal( val, tempval, line ) )
				return 1;

			strvars[ var ] = tempval;
		}
		else {
			strvars[ var ] = GetStringBetweenQuotes( val );
		}
	}

	return 0;
}


int Interpreter::AddVariable( const std::string & var,
			      const std::string & val,
			      int line, bool isvarcheck )
{
	if( intvars.find( var ) != intvars.end() ||
	    strvars.find( var ) != strvars.end() ||
	    fltvars.find( var ) != fltvars.end() ) {
		std::cerr << "Error on line: " << line
			  << "\n\tRedeclaration of a previously created variable: "
			  << var << std::endl;
		return 1;
	}

	DataTypes dt = GetType( val );

	if( dt == INT ) {

		intvars[ var ] = std::stoi( val );
	}
	else if( dt == FLT ) {

		fltvars[ var ] = std::stof( val );
	}
	else {
		if( !IsConstString( val ) ) {

			std::string tempval = val;

			if( isvarcheck && !GetVarVal( val, tempval, line ) )
				return 1;

			strvars[ var ] = tempval;
		}
		else {
			strvars[ var ] = GetStringBetweenQuotes( val );
		}
	}

	return 0;
}

int Interpreter::FormatString( std::vector< std::string > & lineparts,
				std::string & fmtstr,
				int line )
{
	// Args start from 2
	int argctr = 2;

	if( !IsConstString( lineparts[ 1 ] ) ) {
		std::cerr << "Error on line: " << line
			  << "\n\tInvalid string for print!" << std::endl;
		return 1;
	}

	// +1 and -1 to counter the quotes.
	for( auto ch = lineparts[ 1 ].begin() + 1; ch != lineparts[ 1 ].end() - 1; ++ch ) {

		if( * ch == '{' && ( ch + 1 ) != lineparts[ 1 ].end() &&
		    ( ch != lineparts[ 1 ].begin() && * ( ch + 1 ) != '\'' ) ) {

			if( argctr >= ( int )lineparts.size() ) {
				fmtstr += "{NONE}";
			}
			else {
				std::string val =
					GetReplacementValue( lineparts[ argctr ], line );

				if( val == "" )
					return 1;

				fmtstr += val;
			}

			ch++;

			argctr++;
		}
		else {
			fmtstr += * ch;
		}
	}

	return 0;
}

std::string Interpreter::GetReplacementValue( const std::string & str, int line )
{
	if( IsConstString( str ) )
		return GetStringBetweenQuotes( str );

	DataTypes type = GetType( str );

	if( type == INT || type == FLT ) {
		return str;
	}

	std::string val;
	if( !GetVarVal( str, val, line ) )
		return "";

	return val;
}

bool Interpreter::IsConstString( const std::string & data)
{
	if( data.size() < 2 )
		return false;

	if( ( data[ 0 ] == '\"' &&
	    * ( data.end() - 1 ) == '\"' )
	    ||
	    ( data[ 0 ] == '\'' &&
	      * ( data.end() - 1 ) == '\'' ) ) {

		return true;
	}

	return false;
}

DataTypes Interpreter::GetType( const std::string & data )
{
	int decimalcount = 0;

	for( auto ch : data ) {
		if( ( ch < '0' || ch > '9' ) && ch != '.' ) {
			return DataTypes::STR;
		}
		if( ch == '.' )
			decimalcount++;
	}

	if( decimalcount == 0 )
		return DataTypes::INT;
	else if( decimalcount == 1 )
		return DataTypes::FLT;

	return DataTypes::STR;
}

bool Interpreter::GetVarVal( const std::string & key, std::string & val, const int line )
{
	if( intvars.find( key ) != intvars.end() ) {

		val = std::to_string( intvars[ key ] );

		return true;
	}

	if( fltvars.find( key ) != fltvars.end() ) {

		val = std::to_string( fltvars[ key ] );

		return true;
	}

	if( strvars.find( key ) != strvars.end() ) {

		val = strvars[ key ];

		return true;
	}

	std::cerr << "Error on line: " << line
		  << "\n\tUndefined Variable: " << key
		  << std::endl;

	return false;	
}
