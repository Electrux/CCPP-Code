#include <iostream>
#include "../include/CommonFuncs.hpp"
#include "../include/ProjectManager.hpp"

void ShowMainHelp( std::vector< std::string > & args );

int main( int argc, char ** argv )
{
	auto args = ToVector( argc, argv );

	if( args.size() < 2 ) {
		std::cout << "Usage: " << args[ 0 ] << " [ help/project/pkg ] ...\n";
		return 1;
	}

	if( args[ 1 ] == "project" ) {
		return HandleProject( args );
	}
	else if( args[ 1 ] == "pkg" ) {
//		return ManagePackage( args );
	}
	else if( args[ 1 ] == "help" ) {
		ShowMainHelp( args );
	}
	else {
		std::cout << "Invalid parameter. Possible options are: help, project, pkg\n";
		return 1;
	}

	return 0;
}

void ShowMainHelp( std::vector< std::string > & args )
{
	std::cout << "Help:\n\n";

	std::cout << "Usage: " << args[ 0 ] << " parameter [ parameter args ]\n";
	std::cout << "\tParameters are:\n";
	std::cout << "\t\thelp\n";
	std::cout << "\t\t\tShow this help menu\n";

	std::cout << "\t\tproject\n";
	std::cout << "\t\t\tCreate, manipulate and run C++ projects\n";

	std::cout << "\t\tpkg\n";
	std::cout << "\t\t\tManage C++ packages - libraries\n";

	std::cout << "\nYou can get more information from the categorized help of "
		  << "each parameter. To do that, here is an example:\n";
	std::cout << "\t" << args[ 0 ] << " project help\n";
}
