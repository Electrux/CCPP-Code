#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>
#include <vector>

#include "../Errors.hpp"
#include "../DataTypes.hpp"

ErrorTypes ExecutePrint( const std::vector< DataType::Data > & line );

int SubstituteVars( std::string & str, const std::vector< std::string > & args, const int & lineinfile );

std::string VarToString( const std::string & var, const int & lineinfile );

#endif // PRINT_HPP