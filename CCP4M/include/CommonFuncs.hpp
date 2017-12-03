#ifndef COMMONFUNCS_HPP
#define COMMONFUNCS_HPP

#include <vector>

std::vector< std::string > ToVector( int argc, char ** argv );

std::vector< std::string > DelimStringToVector( std::string str, char delim = ',' );

#endif //COMMONFUNCS_HPP
