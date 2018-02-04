#ifndef RETURN_HPP
#define RETURN_HPP

#include <vector>

#include "../Errors.hpp"
#include "../DataTypes.hpp"

ErrorTypes ExecuteReturn( const std::vector< DataType::Data > & line );

#endif // RETURN_HPP