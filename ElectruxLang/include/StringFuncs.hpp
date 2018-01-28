#ifndef STRINGFUNCS_HPP
#define STRINGFUNCS_HPP

#include <vector>

std::vector< std::string > ToVector( int argc, char ** argv );
std::vector< std::string > DelimitString( const std::string & str, char delim = ' ' );
std::string GetWord( const std::string & str, int loc, char delim = ' ' );
std::string GetStringBetweenQuotes( const std::string & str );
int GetIndentLevel( const std::string & str );
bool StringToInteger( const std::string & str, int & val );

template< typename T > std::string VectorToString( const std::vector< T > & vec );

template<> std::string VectorToString< std::string >( const std::vector< std::string > & vec );
template<> std::string VectorToString< int >( const std::vector< int > & vec );
template<> std::string VectorToString< float >( const std::vector< float > & vec );

#endif // STRINGFUNCS_HPP
