#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <vector>
#include <map>

#include "Errors.hpp"
#include "DataTypes.hpp"

ErrorTypes ExecuteAll( const std::vector< std::vector< DataType::Data > > & alldata,
			const std::string & space = "global", const std::string & func = "" );

ErrorTypes ExecuteStatement( const std::vector< std::vector< DataType::Data > > & alldata, int & line,
			const std::string & space = "global", const std::string & func = "" );

#endif // EXECUTOR_HPP