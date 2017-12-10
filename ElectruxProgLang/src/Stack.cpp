#include <iostream>
#include <string>
#include <vector>

#include "../include/Stack.hpp"

void Stack::Push( const std::string & val )
{
	stack.push_back( val );
}

std::string Stack::Pop()
{
	if( stack.size() < 1 ) {
		std::cerr << "Attempted to pop from empty stack!" << std::endl;
		return "";
	}

	return * stack.erase( stack.end() - 1 );
}

std::string Stack::GetLast()
{
	if( stack.size() < 1 ) {
		std::cerr << "Attempted to pop from empty stack!" << std::endl;
		return "";
	}

	return stack[ stack.size() - 1 ];
}

std::string Stack::GetVal( int loc )
{
	if( loc >= ( int )stack.size() ) {
		std::cerr << "Attempted to access an out of bounds element from stack!"
			  << std::endl;
		return "";
	}

	return stack[ loc ];
}

size_t Stack::Size()
{
	return stack.size();
}
