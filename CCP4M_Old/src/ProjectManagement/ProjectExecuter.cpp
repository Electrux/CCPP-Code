#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>

#include "../../include/ColorDefs.hpp"

#include "../../include/ProjectManagement/ProjectBuilder.hpp"
#include "../../include/ProjectManagement/ConfigMgr.hpp"

#include "../../include/ProjectManagement/ProjectExecuter.hpp"

int ExecuteProject( std::vector< std::string > & args )
{
	if( BuildProject( args ) != 0 )
		return 1;

	ConfigMgr conf;

	if( conf.RetrieveConfig( "." ) != 0 )
		return 1;

	std::string projectname = conf.GetDataString( "Core", "Name" );

	std::string command = "./build/" + projectname;

	if( args.size() > 3 ){

		command += " ";

		for( int i = 3; i < ( int )args.size(); ++i ) {
			command += args[ i ];
			command += " ";
		}

		command.erase( command.end() - 1 );
	}

	std::cout << "\n" << BOLD_MAGENTA << "Executing Project..."
		  << RESET << std::endl << std::endl;

	return std::system( command.c_str() );
}
