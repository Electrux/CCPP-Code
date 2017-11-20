//
// Created by Electrux Redsworth on 9/12/17.
//

#ifndef HASHTABLEIMPLEMENTATION_STACK_HPP
#define HASHTABLEIMPLEMENTATION_STACK_HPP

#include <climits>
#include "Constants.hpp"

namespace Electrux
{
	class Stack
	{
		int *stack;
		int top;
		int stacksize;

	public:

		Stack( int size = MAX_TABLES )
		{
			stacksize = size;
			stack = new int[size];
			top = -1;
		}

		~Stack()
		{
			delete[] stack;
		}

		bool Push( int data )
		{
			if( top == stacksize - 1 )
				return false;

			top++;

			stack[ top ] = data;

			return true;
		}

		int Pop()
		{
			if( top < 0 ) return INT_MIN;

			return stack[ top-- ];
		}

	};
}

#endif //HASHTABLEIMPLEMENTATION_STACK_HPP
