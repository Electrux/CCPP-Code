#include <iostream>
#include <string>
#include <vector>

#include "../../include/CommonFuncs.hpp"
#include "../../include/ProjectManagement/ProjectData.hpp"
#include "../../include/ProjectManagement/ConfigMgr.hpp"

#include "../../include/ProjectManagement/BuildFilesGenerator.hpp"

int GenerateBuildFiles()
{
	ConfigMgr config;

	if( config.RetrieveConfig( "." ) != 0 )
		return 1;

	ProjectData data;

	data.name = config.GetDataString( "Core", "Name" );
	data.deps = DelimStringToVector( config.GetDataString( "Core", "Libs" ) );
	data.dir = ".";

	std::string mainsrc = config.GetDataString( "Core", "MainSrc" );
	std::string _othersrc = config.GetDataString( "Core", "OtherSrc" );

	std::string standard = config.GetDataString( "Core", "Std" );
	std::string _flags = config.GetDataString( "Core", "OtherFlags" );

	std::vector< std::string > flagvec = DelimStringToVector( _flags );

	std::string flags = " ";
	for( auto fl : flagvec ) {
		flags += "--" + fl;
		flags += " ";
	}

	std::vector< std::string > othersrc = DelimStringToVector( _othersrc );

	for( auto it = othersrc.begin(); it != othersrc.end(); ++it ) {

		// Remove the .cpp extension...
		it->erase( it->end() - 1 );
		it->erase( it->end() - 1 );
		it->erase( it->end() - 1 );
		it->erase( it->end() - 1 );
	}

	for( auto othersource : othersrc ) {

		std::string othersourcewithoutdir;
		for( auto ch = othersource.rbegin(); ch != othersource.rend(); ++ch ) {

			if( *ch == '/' )
				break;
			othersourcewithoutdir += *ch;
		}
		std::reverse( othersourcewithoutdir.begin(), othersourcewithoutdir.end() );

		std::string compilestr =
			"clang++ -c" + flags + "-std=" + standard
			+ " -o build/" + othersourcewithoutdir
			+ ".o src/" + othersource + ".cpp";

		std::cout << "Building object: "//src/" << othersource << ".cpp"
			  << "build/" << othersourcewithoutdir << ".o" << "\n";

		std::system( compilestr.c_str() );
	}

	if( !mainsrc.empty() ) {

		std::string compilestr =
			"clang++ -g" + flags + "-std=" + standard + " -o build/" + data.name;

		for( auto othersource : othersrc ) {

			std::string othersourcewithoutdir;
			for( auto ch = othersource.rbegin(); ch != othersource.rend(); ++ch ) {

				if( *ch == '/' )
					break;
				othersourcewithoutdir += *ch;
			}
			std::reverse( othersourcewithoutdir.begin(),
				      othersourcewithoutdir.end() );
		
			compilestr += " build/" + othersourcewithoutdir + ".o ";
		}

		compilestr += " src/" + mainsrc;

		std::cout << "Compiling and linking: src/" << mainsrc << "\n";

		std::system( compilestr.c_str() );
	}

	return 0;
}


