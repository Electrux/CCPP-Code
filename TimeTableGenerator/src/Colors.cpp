#include <string>
#include <map>

#include "../include/Colors.hpp"

int SubstituteColors( std::string & str )
{
	int len = 0;
	std::string var;

	for( std::string::iterator it = str.begin(); it != str.end(); ) {
		if( * it == '{' && it + 1 != str.end() ) {
			it = str.erase( it );
			if( * it == '{' ) {
				len++;
				++it;
				continue;
			}

			var = "";
			while( it != str.end() && * it != '}' ) {
				var += * it;
				it = str.erase( it );
			}
			it = str.erase( it );

			if( COLORS.find( var ) != COLORS.end() ) {
				it = str.insert( it, COLORS[ var ].begin(), COLORS[ var ].end() );
				it += COLORS[ var ].size();
			}
			continue;
		}

		len = * it == '\n' ? 0 : len + 1;
		++it;
	}

	return len;
}