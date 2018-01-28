#ifndef PRINT_HPP
#define PRINT_HPP

#include <string>
#include <vector>

#include "../Errors.hpp"
#include "../DataTypes.hpp"

ErrorTypes ExecutePrint( const std::vector< DataType::Data > & line,
			const std::string & space = "global", const std::string & func = "" );

int SubstituteVars( std::string & str, const std::vector< std::string > & args, const int & lineinfile,
			const std::string & space = "global", const std::string & func = "" );

std::string VarToString( const std::string & var, const int & lineinfile,
			const std::string & space = "global", const std::string & func = "" );

#endif // PRINT_HPP