#ifndef INPUT_HPP
#define INPUT_HPP

#include <vector>

#include "../Errors.hpp"
#include "../DataTypes.hpp"
#include "../Vars.hpp"

ErrorTypes ExecuteInput( const std::vector< DataType::Data > & line, DataType::Data & var );

#endif // INPUT_HPP