#ifndef VAR_HPP
#define VAR_HPP

#include <string>
#include <vector>
#include <map>

#include "../Errors.hpp"
#include "../DataTypes.hpp"

ErrorTypes HandleVar( const std::vector< std::vector< DataType::Data > > & alldata, const int & line );

#endif // VAR_HPP