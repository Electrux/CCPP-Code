#include <iostream>
#include <vector>
#include <string>
#include <climits>

#include "../../include/Commands.hpp"
#include "../../include/FileParser.hpp"
#include "../../include/StringFuncs.hpp"

#include "../../include/LangInterpreter/LanguageInterpreter.hpp"

int Interpreter::AddVariable( const std::string & var,
			      const std::string & val,
			      int line, bool isvarcheck )
{
	if( intvars.find( var ) != intvars.end() ||
	    strvars.find( var ) != strvars.end() ) {
		std::cerr << "Error on line: " << line
			  << "\n\tRedeclaration of a previously created variable: "
			  << var << std::endl;
		return 1;
	}

	int intval = IsInt( val );

	if( intval != INT_MIN ) {

		intvars[ var ] = intval;
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
				if( IsConstString( lineparts[ argctr ] ) ||
				    IsInt( lineparts[ argctr ] ) != INT_MIN ) {

					fmtstr += GetStringBetweenQuotes( lineparts[ argctr ] );
				}
				else {
					std::string val;
					if( !GetVarVal( lineparts[ argctr ], val, line ) )
						return 1;

					fmtstr += val;
				}
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

int Interpreter::IsInt( const std::string & data )
{
	int temp = 0;

	for( auto ch : data ) {
		if( ch < '0' || ch > '9' )
			return INT_MIN;

		temp = ( temp * 10 ) + ( ch - '0' );
	}

	return temp;
}

bool Interpreter::GetVarVal( const std::string & key, std::string & val, const int line )
{
	if( intvars.find( key ) != intvars.end() ) {

		val = std::to_string( intvars[ key ] );

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
