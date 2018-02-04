#include <string>

#include "../include/Stack.hpp"
#include "../include/Vars.hpp"

#include "../include/GlobalData.hpp"


void SetCurrentFunction( const std::string & func_name )
{
	func_stack.Push( func_name );
}

void RemoveLastFunction()
{
	if( func_stack.Size() > 0 )
		func_stack.Pop();
}

std::string GetCurrentFunction()
{
	return func_stack.Size() > 0 ? func_stack.Last() : "";
}

void SetCurrentReturnValue( const Variable & var )
{
	last_return.Push( var );
}

Variable GetCurrentReturnValue()
{
	return last_return.Size() < 1 ? ( Variable ){ Vars::INVALID, "" } : last_return.Last();
}

void RemoveLastReturnValue()
{
	if( last_return.Size() > 0 )
		last_return.Pop();
}