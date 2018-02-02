#include <string>

#include "../include/Stack.hpp"

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