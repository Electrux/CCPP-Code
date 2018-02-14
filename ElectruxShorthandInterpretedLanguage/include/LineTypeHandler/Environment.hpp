#include <vector>

#include "../Errors.hpp"
#include "../DataTypes.hpp"

ErrorTypes ExecuteSetEnv( const std::vector< DataType::Data > & dataline );

ErrorTypes ExecuteGetEnv( const std::vector< DataType::Data > & dataline, DataType::Data & result );

ErrorTypes ExecuteExecCommand( const std::vector< DataType::Data > & dataline, DataType::Data & result );