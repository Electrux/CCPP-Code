#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <string>

enum DataTypes
{
	INT,
	FLT,
	STR,
};

DataTypes GetType( const std::string & data );

#endif // DATATYPES_HPP
