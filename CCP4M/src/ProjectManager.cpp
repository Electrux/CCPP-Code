#include <iostream>
#include <vector>

#include "../include/ProjectManagement/ProjectCreator.hpp"

#include "../include/ProjectManager.hpp"

int HandleProject( std::vector< std::string > & args )
{
	if( args.size() < 3 ) {
		std::cout << "Usage: " << args[ 0 ] << " project [ help/new/run/build ] ...\n";
		return 1;
	}

	if( args[ 2 ] == "help" ) {
		ShowProjectHelp( args );
	}
	else if( args[ 2 ] == "new" ) {
		return CreateProject( args );
	}
	else if( args[ 2 ] == "build" ) {
//		return BuildProject( args );
	}
	else if( args[ 2 ] == "run" ) {
//		return RunProject( args );
	}
	else {
		std::cout << "Invalid parameter. Possible Options are: help, new, run, build\n";
		return 1;
	}

	return 0;	
}

void ShowProjectHelp( std::vector< std::string > & args )
{
	std::cout << "Help:\n\n";

	std::cout << "Usage: " << args[ 0 ] << " project [ help/new/run/build ] ...\n";
	std::cout << "\tParameters are:\n";
	std::cout << "\t\thelp\n";
	std::cout << "\t\t\tShow this help menu\n";

	std::cout << "\t\tnew\n";
	std::cout << "\t\t\tCreate a new C++ project\n";

	std::cout << "\t\tbuild\n";
	std::cout << "\t\t\tBuild C++ projects. You must be in the directory of a project\n";

	std::cout << "\t\trun\n";
	std::cout << "\t\t\tBuild and run C++ projects."
		  << " You must be in the directory of a project\n";

	std::cout << "\nYou can get more information from the categorized help of "
		  << "each parameter. To do that, here is an example:\n";
	std::cout << "\t" << args[ 0 ] << " project new help\n";
}
