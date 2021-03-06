#include <string>

#include "../../include/ProjectManagement/ProjectData.hpp"
#include "../../include/ProjectManagement/FSFuncs.hpp"
#include "../../include/ProjectManagement/ConfigMgr.hpp"

#include "../../include/ProjectManagement/ProjectFileGenerator.hpp"

int GenerateProjectFiles( ProjectData & data )
{
	std::cout << "Project:\n\tName: " << data.name
		  << "\n\tDirectory: " << data.dir
		  << "\n\tDependencies: ";

	if( !data.deps.empty() ) {
		for( auto dep : data.deps )
			std::cout << dep << ", ";
		std::cout << "\b \n\n";
	}
	else {
		std::cout << "NONE\n\n";
	}

	std::string proj_dir, proj_src, proj_inc, proj_build;

	SetFolderPaths( data.dir, data.name, proj_dir, proj_src, proj_inc, proj_build );

	CreateDir( proj_dir );
	CreateDir( proj_src );
	CreateDir( proj_inc );
	CreateDir( proj_build );

	CreateFileWithContents( proj_src + "/main.cpp", DEFAULTMAIN );

	ConfigMgr config;

	config.SetProject( data );

	return config.CreateDefaultConfig( proj_dir );
}
