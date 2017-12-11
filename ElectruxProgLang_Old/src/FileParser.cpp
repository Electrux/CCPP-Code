#include <string>
#include <fstream>
#include <vector>

#include "../include/FileParser.hpp"

bool FileParser::ParseFile( std::string _filename )
{
	filename = _filename;

	std::fstream file;

	file.open( filename, std::ios::in );

	if( !file )
		return false;

	std::string line;

	while( std::getline( file, line ) ) {

		lines.push_back( line );
	}

	file.close();

	return true;
}

std::string FileParser::GetLine( int loc )
{
	if( loc >= ( int )lines.size() )
		return "";

	return lines[ loc ];
}

std::vector< std::string > & FileParser::GetAllLines()
{
	return lines;
}

int FileParser::GetTotalLines()
{
	return ( int )lines.size();
}

void FileParser::ClearAll()
{
	lines.clear();
	filename.clear();
}
