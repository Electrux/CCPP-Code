#include <iostream>
#include <string>
#include <vector>

#include "../include/DataTypes.hpp"
#include "../include/Vars.hpp"

#include "../include/Stack.hpp"

template< class T > void Stack< T >::Push( const T & val )
{
	stack.push_back( val );
}

template< class T > T Stack< T >::Pop()
{
	if( stack.size() < 1 ) {
		std::cerr << "Attempted to pop from empty stack!" << std::endl;
		return T();
	}

	return * stack.erase( stack.end() - 1 );
}

template< class T > T Stack< T >::Last()
{
	if( stack.size() < 1 ) {
		std::cerr << "Attempted to pop from empty stack!" << std::endl;
		return T();
	}

	return stack[ stack.size() - 1 ];
}

template< class T > T Stack< T >::GetVal( int loc )
{
	if( loc >= ( int )stack.size() ) {
		std::cerr << "Attempted to access an out of bounds element from stack!"
			  << std::endl;
		return T();
	}

	return stack[ loc ];
}

template< class T > size_t Stack< T >::Size()
{
	return stack.size();
}

template class Stack< DataType::Data >;
template class Stack< std::string >;
template class Stack< Variable >;