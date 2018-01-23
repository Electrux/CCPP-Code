#ifndef PARSER_HPP
#define PARSER_HPP

#include <vector>

#include "Errors.hpp"
#include "DataTypes.hpp"

ErrorTypes ParseAll( const std::vector< std::vector< DataType::Data > > & alldata );

#endif // PARSER_HPP