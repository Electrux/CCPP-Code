#ifndef COMMONFUNCS_HPP
#define COMMONFUNCS_HPP

#include <string>
#include <vector>

std::vector< std::string > ToVector( int argc, char ** argv );

std::vector< std::string > DelimStringToVector( std::string str, char delim = ',' );

std::string GetStringBetweenQuotes( std::string & str );

std::string GetStringTillLastSlash( std::string & str );

#endif //COMMONFUNCS_HPP
