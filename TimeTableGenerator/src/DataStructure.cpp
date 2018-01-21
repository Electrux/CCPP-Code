#include <string>
#include <vector>

#include "../include/DataStructure.hpp"

Data DelimLineToData( const std::string & str, const char delim )
{
	std::string temp;
	std::vector< std::string > val;

	for( auto ch : str ) {

		if( ch == delim && !temp.empty() ) {
			val.push_back( temp );
			temp.clear();
			continue;
		}

		temp += ch;
	}

	if( !temp.empty() )
		val.push_back( temp );
	
	Data data;

	// less than data's number of elements.
	if( str.size() < 2 )
		return data;

	data.name = val[ 0 ];
	data.frequency = std::stoi( val[ 1 ] );

	return data;
}