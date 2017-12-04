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
		COUNTTYPE *stack;
		COUNTTYPE top;
		COUNTTYPE stacksize;

	public:

		Stack( COUNTTYPE size = MAX_TABLES )
		{
			stacksize = size;
			stack = new COUNTTYPE[ size ];
			top = -1;
		}

		~Stack()
		{
			delete[] stack;
		}

		bool Push( COUNTTYPE data )
		{
			if( top == stacksize - 1 )
				return false;

			top++;

			stack[ top ] = data;

			return true;
		}

		COUNTTYPE Pop()
		{
			if( top < 0 ) return -16384;

			return stack[ top-- ];
		}

	};
}

#endif //HASHTABLEIMPLEMENTATION_STACK_HPP
