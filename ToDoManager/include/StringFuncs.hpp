#ifndef STRINGFUNCS_HPP
#define STRINGFUNCS_HPP

#include <string>

bool Trim( std::string & str );

std::string Concatenate( std::vector< std::string > & args, int after = -1 );

#endif // STRINGFUNCS_HPP
