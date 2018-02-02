#ifndef GLOBALDATA_HPP
#define GLOBALDATA_HPP

#include <string>

#include "Stack.hpp"

static Stack< std::string > func_stack;

void SetCurrentFunction( const std::string & func_name );
void RemoveLastFunction();
std::string GetCurrentFunction();

#endif // GLOBALDATA_HPP