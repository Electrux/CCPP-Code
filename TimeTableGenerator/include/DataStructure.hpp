#ifndef DATASTRUCTURE_HPP
#define DATASTRUCTURE_HPP

#include <string>

struct Data
{
	std::string name;
	int frequency;
};

struct Table
{
	int rows;
	int cols;

	std::string ** data;
};

Data DelimLineToData( const std::string & str, const char delim = ',' );

#endif // DATASTRUCTURE_HPP