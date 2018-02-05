#ifndef MODULELOADER_HPP
#define MODULELOADER_HPP

#include <vector>

#include "../Errors.hpp"
#include "../DataTypes.hpp"

ErrorTypes LoadModule( const std::vector< DataType::Data > & dataline );

#endif // MODULELOADER_HPP