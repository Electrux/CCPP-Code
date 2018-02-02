#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string>
#include <vector>
#include <map>

#include "Errors.hpp"
#include "DataTypes.hpp"

ErrorTypes ExecuteAll( const std::vector< std::vector< DataType::Data > > & alldata );

ErrorTypes ExecuteStatement( const std::vector< std::vector< DataType::Data > > & alldata, int & line );

#endif // EXECUTOR_HPP