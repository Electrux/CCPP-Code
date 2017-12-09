#ifndef FILEPARSER_HPP
#define FILEPARSER_HPP

#include <string>
#include <vector>

class FileParser
{
	std::string filename;

	std::vector< std::string > lines;

public:

	bool ParseFile( std::string _filename );

	std::string GetLine( int loc );

	std::vector< std::string > & GetAllLines();

	int GetTotalLines();

	void ClearAll();
};

#endif // FILEPARSER_HPP
