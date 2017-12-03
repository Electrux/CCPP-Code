#include "../include/CommonFuncs.hpp"

#include <string>
#include <vector>

std::vector< std::string > ToVector( int argc, char ** argv )
{
	std::vector< std::string > temp;

	for( int i = 0; i < argc; ++i )
		temp.push_back( argv[ i ] );

	return temp;
}

std::vector< std::string > DelimStringToVector( std::string str, char delim )
{
	std::string temp;
	std::vector< std::string > val;

	for( auto ch : str ) {

		if( ch == delim ) {
			val.push_back( temp );
			temp.clear();
			continue;
		}

		temp += ch;
	}

	if( !temp.empty() )
		val.push_back( temp );

	return val;
}
