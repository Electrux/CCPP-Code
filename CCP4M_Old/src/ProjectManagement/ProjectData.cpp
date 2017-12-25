#include <iostream>
#include <vector>
#include <string>

#include "../../include/CommonFuncs.hpp"

#include "../../include/ProjectManagement/ProjectData.hpp"

ProjectData GetProjectData( std::vector< std::string > & args )
{
	ProjectData data;

	bool invalidformat = false;
	bool founddir = false;
	bool founddeps = false;
	bool foundname = false;

	for( auto arg = args.begin() + 3; arg != args.end(); ++arg ) {

		if( arg->find( "--" ) != std::string::npos ) {

			if( ( arg + 1 ) == args.end() ||
			    ( arg + 1 )->find( "--" ) != std::string::npos ) {

				invalidformat = true;
				break;
			}

			if( arg->find( "dir" ) != std::string::npos && !founddir ) {

				++arg;
				data.dir = * arg;
				founddir = true;
			}
			else if( arg->find( "deps" ) != std::string::npos && !founddeps ) {

				++arg;
				data.deps = DelimStringToVector( * arg, ',' );

				if( data.deps.empty() ) {
					invalidformat = true;

					std::cout << "Error: No dependencies specified."
						  << " However, the --deps flag was used\n";

					break;
				}
			}
			else {
				std::cout << "Error: Invalid flag or repetition occurred."
					  << " Please use:\n"
					  << "\t" << args[ 0 ] << " project new help\n"
					  << "for more information\n";

				invalidformat = true;

				break;
			}
		}
		else {
			if( foundname ) {
				std::cout << "Error: Invalid flag or repetition occurred."
					  << " Please use:\n"
					  << "\t" << args[ 0 ] << " project new help\n"
					  << "for more information\n";

				invalidformat = true;

				break;
			}

			data.name = * arg;
			foundname = true;
		}
	}

	if( !founddir )
		data.dir = ".";

	if( invalidformat ) {

		if( data.name.empty() ) {
			std::cout << "Cannot have unnamed project\n";
		}
		data.name.clear();
		data.deps.clear();
		data.dir.clear();
	}

	return data;
}
