#include <iostream>
#include "../include/LinkedList.hpp"

int main()
{
	LinkedList< int > test;

	for( int i = 0; i < 1000000; ++i )
		test.Insert( i );

	//test.DeleteLast();

	std::cout << "\n";
	test.Display();
	std::cout << "\n";
	
	return 0;
}
