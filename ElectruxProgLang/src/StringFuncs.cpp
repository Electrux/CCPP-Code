#include <iostream>
#include <vector>
#include <string>

#include "../include/StringFuncs.hpp"

std::vector< std::string > ToVector( int argc, char ** argv )
{
	std::vector< std::string > temp;

	for( int i = 0; i < argc; ++i )
		temp.push_back( argv[ i ] );

	return temp;
}

std::vector< std::string > DelimitString( std::string & str, char delim )
{
	std::string temp;
	std::vector< std::string > tempvec;

	bool encounteredquote = false;

	for( auto ch : str ) {

		if( ch == '\'' || ch == '\"' )
			encounteredquote = !encounteredquote;

		if( ch == delim && !encounteredquote ) {

			tempvec.push_back( temp );
			temp.clear();

			continue;
		}

		temp += ch;
	}

	if( !temp.empty() )
		tempvec.push_back( temp );

	return tempvec;
}

std::string GetWord( std::string & str, int loc, char delim )
{
	std::string temp;
	int ctr = 0;

	for( auto ch : str ) {

		if( ch == delim ) {
			if( loc == ctr )
				break;
			ctr++;
		}

		if( ctr == loc )
			temp += ch;
	}

	return temp;
}

std::string GetStringBetweenQuotes( const std::string & str )
{
	std::string temp;

	bool startquote = false;

	for( auto ch : str ) {

		if( ch == '\"' || ch == '\'' ) {
			startquote = !startquote;
		}
		else if( startquote )
			temp += ch;
	}

	return temp;
}
