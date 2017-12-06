#include <iostream>
#include <cstdlib>
#include <string>

#include "../include/ToVector.hpp"
#include "../include/TaskFunctions.hpp"

int main( int argc, char **argv )
{
	auto args = ToVector( argc, argv );
	
	if( args.size() < 2 ) {

		std::cout << "Usage: " << args[ 0 ]
			  << " [ do/alter/done/list/help ] < args... >" << std::endl;
		return 1;
	}

	if( args[ 1 ] == "do" ) {
		// Not of the return value because zero = good for program...
		// but not for functions...
		return !inserttask( args );
	}
	else if( args[ 1 ] == "alter" ) {
		// Not of the return value because zero = good for program...
		// but not for functions...
		return !altertask( args );
	}
	else if( args[ 1 ] == "done" ) {
		// Not of the return value because zero = good for program...
		// but not for functions...
		return !deletetask( args );
	}
	else if( args[ 1 ] == "list" ) {
		showtasks();
		return 0;
	}
	else if( args[ 1 ] == "help" ) {

		HelpFunction();
		return 0;
	}

	return 1;
}
