#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <vector>
#include <map>

#include "Errors.hpp"
#include "DataTypes.hpp"

ErrorTypes ExecuteAll( const std::vector< std::vector< DataType::Data > > & alldata );

ErrorTypes ExecuteStatement( const std::vector< std::vector< DataType::Data > > & alldata, const int & line,
			std::map< std::string, int > & vardeclline );

#endif // EXECUTOR_HPP