#include <iostream>
#include <string>
#include <vector>

#include "../../include/CommonFuncs.hpp"
#include "../../include/ColorDefs.hpp"

#include "../../include/ProjectManagement/ProjectData.hpp"
#include "../../include/ProjectManagement/FSFuncs.hpp"
#include "../../include/ProjectManagement/ConfigMgr.hpp"

#include "../../include/ProjectManagement/BuildFilesGenerator.hpp"

int GenerateBuildFiles()
{
	std::string mainsrc, flags, libs;
	std::vector< std::string > othersrc;
	ProjectData data;
	ConfigMgr config;

	if( GetBuildData( config, data, mainsrc, flags, libs, othersrc ) != 0 )
		return 1;

	if( libs == " " )
		libs = "";

	if( CreateBuildDirectories( othersrc ) != 0 )
		return 1;

	std::string standard = config.GetDataString( "Core", "Std" );

	int filecount = othersrc.size() + ( ( mainsrc.empty() ) ? 0 : 1 );

	float percent = 0.0, percentdelta = 100.0 / filecount;

	if( !othersrc.empty() )
		std::cout << std::endl;

	for( auto othersource : othersrc ) {

		percent += percentdelta;

		std::string compilestr =
			"clang++ -c" + flags + "-std=" + standard
			+ " -o build/buildfiles/" + othersource
			+ ".o src/" + othersource + libs;

		std::cout << "[" << ( int )percent << "%]\t"
			  << YELLOW << "Building CXX object: "
			  << CYAN << "build/buildfiles/" << othersource << ".o"
			  << RESET << "\n";

		std::system( compilestr.c_str() );
	}

	if( !mainsrc.empty() ) {

		percent += percentdelta;

		std::string compilestr =
			"clang++ -g" + flags + "-std=" + standard + " -o build/" + data.name
			+ libs;

		for( auto othersource : othersrc )		
			compilestr += " build/buildfiles/" + othersource + ".o ";

		compilestr += " src/" + mainsrc;

		std::cout << "\n[" << ( int )percent << "%]\t"
			  << BOLD_YELLOW << "Building and Linking CXX executable: "
			  << BOLD_GREEN << "build/" << data.name << RESET << "\n";

		std::system( compilestr.c_str() );
	}

	return 0;
}

int CreateBuildDirectories( std::vector< std::string > & othersrc )
{
	std::string buildfilesdir = "build/buildfiles/";

	int retval = 0;

	for( auto src : othersrc ) {

		if( src.find( '/' ) == std::string::npos )
			continue;

		retval |= CreateDir( buildfilesdir + GetDirectoryFromSource( src ) );
	}

	return retval;
}

std::string GetDirectoryFromSource( std::string src )
{
	std::string dir;

	bool foundslash = false;

	for( auto it = src.rbegin(); it != src.rend(); ++it ) {

		if( *it == '/' && foundslash == false ) {

			foundslash = true;
			continue;
		}

		if( foundslash )
			dir += *it;
	}

	std::reverse( dir.begin(), dir.end() );

	return dir;
}

int GetBuildData( ConfigMgr & config, ProjectData & data, std::string & mainsrc,
		  std::string & flags, std::string & libs,
		  std::vector< std::string > & othersrc )
{
	if( config.RetrieveConfig( "." ) != 0 )
		return 1;

	data.name = config.GetDataString( "Core", "Name" );
	data.deps = DelimStringToVector( config.GetDataString( "Core", "Libs" ) );
	data.dir = ".";

	mainsrc = config.GetDataString( "Core", "MainSrc" );
	std::string _othersrc = config.GetDataString( "Core", "OtherSrc" );

	std::string _flags = config.GetDataString( "Core", "OtherFlags" );
	std::string _libs = config.GetDataString( "Core", "Libs" );

	std::vector< std::string > flagvec = DelimStringToVector( _flags );
	std::vector< std::string > libvec = DelimStringToVector( _libs );

	flags = " ";
	for( auto fl : flagvec ) {
		flags += fl;
		flags += " ";
	}

	libs = " ";
	for( auto lb : libvec ) {
		libs += lb;
		libs += " ";
	}

	std::vector< std::string > __othersrc = DelimStringToVector( _othersrc );

	if( __othersrc.size() == 1 && * __othersrc.begin() == "*" ) {

		if( GetFilesInDir( "src", othersrc, true ) != 0 )
			return 1;
	}
	else {
		for( auto it = __othersrc.begin(); it != __othersrc.end(); ++it ) {

			if( * ( it->end() - 1 ) == '*' ) {

				// Remove * and /
				it->erase( it->end() - 1 );
				it->erase( it->end() - 1 );

				if( *it == "src" ) {
					if( GetFilesInDir( "src", othersrc ) != 0 )
						return 1;
				}
				else {
					if( GetFilesInDir( "src/" + *it, othersrc ) != 0 )
						return 1;
				}
			}
		}
	}

	if( mainsrc.empty() )
		return 0;

	for( auto it = othersrc.begin(); it != othersrc.end(); ++it ) {

		if( *it == mainsrc ) {
			othersrc.erase( it );
			break;
		}
	}

	return 0;
}
