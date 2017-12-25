#include <iostream>
#include <vector>
#include <string>

#include "../../include/CommonFuncs.hpp"
#include "../../include/ProjectManagement/ProjectData.hpp"
#include "../../include/ProjectManagement/ConfigMgr.hpp"
#include "../../include/ProjectManagement/BuildFilesGenerator.hpp"

#include "../../include/ProjectManagement/ProjectBuilder.hpp"

int BuildProject( std::vector< std::string > & args )
{
	if( args.size() < 3 ) {
		std::cout << "No parameter given to the command. Please use:\n";
		std::cout << "\t" << args[ 0 ] << " project build\n";
		std::cout << "for more information\n";
		return 1;
	}

	if( args[ 3 ] == "help" ) {
		ShowBuildHelp( args );
		return 0;
	}

	return GenerateBuildFiles();
}

void ShowBuildHelp( std::vector< std::string > & args )
{
	std::cout << "Help:\n\n";

	std::cout << "Usage: " << args[ 0 ] << " project new [ help ] / "
		  << "[ [ name ] --[ options ] ]\n";
	std::cout << "\tArgs are:\n";
	std::cout << "\t\thelp\n";
	std::cout << "\t\t\tShow this help menu\n";

	std::cout << "\t\tname\n";
	std::cout << "\t\t\tName of the C++ project. ( Mandatory )\n";

	std::cout << "\t\toptions are:\n";

	std::cout << "\t\t\t--dir\n";
	std::cout << "\t\t\t\tSpecifiy the directory of the project\n";

	std::cout << "\t\t\t--deps\n";
	std::cout << "\t\t\t\tAdd a comma separated list of dependencies/libraries\n";
}
