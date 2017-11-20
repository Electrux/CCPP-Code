#ifndef STACK_HPP
#define STACK_HPP

#include <vector>

template <typename T>
class Stack
{
       	std::vector< T > stack;

public:

	void Push( T c )
	{
		stack.push_back( c );
	}

	T Pop()
	{
		T retval = *( stack.end() - 1 );

		stack.erase( stack.end() - 1 );

		return retval;
	}

	size_t GetCount() { return stack.size(); }
};

#endif // STACK_HPP
