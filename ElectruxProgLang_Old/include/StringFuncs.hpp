#ifndef STRINGFUNCS_HPP
#define STRINGFUNCS_HPP

#include <vector>

std::vector< std::string > ToVector( int argc, char ** argv );
std::vector< std::string > DelimitString( const std::string & str, char delim = ' ' );
std::string GetWord( const std::string & str, int loc, char delim = ' ' );
std::string GetStringBetweenQuotes( const std::string & str );
int GetIndentLevel( const std::string & str );

#endif // STRINGFUNCS_HPP
