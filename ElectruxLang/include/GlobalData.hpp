#ifndef GLOBALDATA_HPP
#define GLOBALDATA_HPP

#include <string>

#include "Stack.hpp"
#include "Vars.hpp"

static Stack< std::string > func_stack;

static Stack< Variable > last_return;

void SetCurrentFunction( const std::string & func_name );
void RemoveLastFunction();
std::string GetCurrentFunction();

void SetCurrentReturnValue( const Variable & var );
Variable GetCurrentReturnValue();
void RemoveLastReturnValue();

#endif // GLOBALDATA_HPP