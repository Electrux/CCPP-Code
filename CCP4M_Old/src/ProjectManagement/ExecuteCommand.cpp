#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <future>
#include <vector>

#include "../../include/ColorDefs.hpp"
#include "../../include/UTFChars.hpp"

#include "../../include/ProjectManagement/ExecuteCommand.hpp"
#include "../../include/ProjectManagement/CompileCommandData.hpp"

int ExecuteCommand( std::string command )
{
	int i = std::system( command.c_str() );

	return WEXITSTATUS( i );
}

void DisplayBuildResults( CCData & commands, int res, int percent )
{
	std::cout << "[" << percent << "%]\t"
		  << YELLOW << "Building CXX object: "
		  << CYAN << "build/buildfiles/" << commands.othersource << ".o"
		  << RESET << " ...";

	if( res == 0 )
		std::cout << " " << GREEN << TICK << RESET << "\n";
	else
		std::cout << " " << RED << CROSS << RESET << "\n";
}

int ExecuteAllCommands( std::vector< CCData > & commands, int count )
{
	int retval = 0;

	float percent = 0.0, percentdelta = 100.0 / count;

	std::vector< std::future< int > > results;

	int ctr = 0;

	size_t cores = std::thread::hardware_concurrency() / 2;

	for( int i = 0; i < ( int )commands.size(); ++i ) {

		results.push_back( std::async( std::launch::async,
					       ExecuteCommand,
					       commands[ i ].command ) );

		if( ( i + 1 ) % cores == 0 || i == ( int )commands.size() - 1 ) {

			for( auto it = results.begin(); it != results.end(); ) {

				percent += percentdelta;

				retval |= it->get();
				it = results.erase( results.begin() );

				DisplayBuildResults( commands[ ctr ], retval, ( int )percent );

				ctr++;

				if( retval != 0 )
					break;
			}
		}
	}

	for( auto & res : results )
		res.get();

	return retval;
}
