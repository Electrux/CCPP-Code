#include <string>

#include "../include/DataTypes.hpp"

DataTypes GetType( const std::string & data )
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
