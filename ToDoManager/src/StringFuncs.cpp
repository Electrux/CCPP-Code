#include <string>
#include <vector>

#include "../include/StringFuncs.hpp"

bool Trim( std::string & str )
{
	if( str.empty() )
		return false;

	if( * str.begin() == ' ' || * str.begin() == '\t' || * str.begin() == '\n' )
		str.erase( str.begin() );

	if( * ( str.end() - 1 ) == ' ' ||
	    * ( str.end() - 1 ) == '\t' ||
	    * ( str.end() - 1 ) == '\n' )
		str.erase( str.end() - 1 );

	for( std::string::iterator it = str.begin(); it != str.end(); ) {

		if( *it == '\t' ||
		    ( *it == ' ' && ( it + 1 ) != str.end() && * ( it + 1 ) == ' ' ) )
			it = str.erase( it );
		else
			++it;
	}

	return true;
}

std::string Concatenate( std::vector< std::string > & args, int after )
{
	std::string temp;

	for( int i = after + 1; i < ( int )args.size(); ++i ) {
		temp += args[ i ];
		temp += " ";
	}

	Trim( temp );

	return temp;
}
