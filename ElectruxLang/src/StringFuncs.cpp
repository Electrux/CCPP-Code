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

std::vector< std::string > DelimitString( const std::string & str, char delim )
{
	std::string temp;
	std::vector< std::string > tempvec;

	bool inquote = false;

	for( auto ch = str.begin(); ch != str.end(); ++ch ) {

		// Tabs and spaces for indentation
		if( *ch == '\t' )
			continue;

		if( ( ch + 3 ) < str.end() &&
		    * ch == ' ' &&
		    * ( ch + 1 ) == ' ' &&
		    * ( ch + 2 ) == ' ' &&
		    * ( ch + 3 ) == ' ' ) {

			ch += 3;
			continue;
		}

		if( * ch == '\'' || * ch == '\"' )
			inquote = !inquote;

		if( * ch == delim && !inquote ) {

			if( !temp.empty() )
				tempvec.push_back( temp );
			temp.clear();

			continue;
		}

		temp += * ch;
	}

	if( !temp.empty() )
		tempvec.push_back( temp );

	return tempvec;
}

std::string GetWord( const std::string & str, int loc, char delim )
{
	std::string temp;
	int ctr = 0;

	for( auto ch = str.begin(); ch != str.end(); ++ch ) {

		// Tabs and spaces for indentation
		if( *ch == '\t' )
			continue;

/*		if( ( ch + 3 ) < str.end() &&
		    * ch == ' ' &&
		    * ( ch + 1 ) == ' ' &&
		    * ( ch + 2 ) == ' ' &&
		    * ( ch + 3 ) == ' ' ) {

			ch += 3;
			continue;
		}
*/
		if( * ch == delim ) {
			if( loc == ctr )
				break;
			ctr++;
		}

		if( ctr == loc )
			temp += * ch;
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

int GetIndentLevel( const std::string & str )
{
	if( str.empty() )
		return 1;

	int ctr = 0;

	auto it = str.begin();

	while( *it == '\t' ) {
		ctr++;
		it++;
	}

	it = str.begin();

	if( ctr == 0 ) {

		while( *it == ' ' ) {
			ctr++;
			it++;
		}
	}

	return ctr;
}
