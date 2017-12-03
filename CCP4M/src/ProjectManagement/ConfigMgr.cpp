#include <iostream>
#include <string>
#include <vector>

#include "../../include/ProjectManagement/ProjectData.hpp"
#include "../../include/INI_System/INI_Parser.hpp"

#include "../../include/ProjectManagement/ConfigMgr.hpp"

void ConfigMgr::SetProject( ProjectData & proj ) { data = proj; }
ProjectData ConfigMgr::GetProject() { return data; }

int ConfigMgr::CreateDefaultFile( std::string project_dir )
{
	if( data.name.empty() )
		return 1;

	std::string concatlibs;

	for( auto lib : data.deps ) {
		concatlibs += lib;
		concatlibs += ',';
	}

	if( !concatlibs.empty() )
	concatlibs.erase( concatlibs.end() - 1 );

	parser.CreateSection( "Core" );
	parser.SetDataString( "Core", "Name", data.name );
	parser.SetDataString( "Core", "Version", "0.1" );
	parser.SetDataString( "Core", "Libs", concatlibs );
	parser.SetDataString( "Core", "OtherFlags", "" );
	parser.SetDataString( "Core", "Std", "c++14" );

	parser.CreateSection( "Deps" );
	for( auto lib : data.deps ) {
		parser.SetDataString( "Deps", lib, "Default" );
	}

	std::cout << "Creating file: " << project_dir + "/ccp4m.ini\n";
	parser.SaveToFile( project_dir + "/ccp4m.ini" );

	return 0;
}
