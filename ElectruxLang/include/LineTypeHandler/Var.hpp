#ifndef VAR_HPP
#define VAR_HPP

#include <string>
#include <vector>
#include <map>

#include "../Errors.hpp"
#include "../DataTypes.hpp"

ErrorTypes HandleVar( const std::vector< std::vector< DataType::Data > > & alldata, const int & line,
			std::map< std::string, int > & vardeclline );

#endif // VAR_HPP