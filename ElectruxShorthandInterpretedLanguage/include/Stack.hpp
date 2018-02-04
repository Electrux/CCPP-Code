#ifndef STACK_HPP
#define STACK_HPP

#include <string>
#include <vector>

template< class T > class Stack
{
	std::vector< T > stack;

public:

	void Push( const T & val );

	T Pop();

	T Last();

	T GetVal( int loc );

	size_t Size();
};

#endif // STACK_HPP