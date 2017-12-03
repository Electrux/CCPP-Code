#include <string>

#include "../../include/ProjectManagement/ProjectData.hpp"
#include "../../include/ProjectManagement/FSFuncs.hpp"
#include "../../include/ProjectManagement/ConfigMgr.hpp"

#include "../../include/ProjectManagement/ProjectFileGenerator.hpp"

int GenerateProjectFiles( ProjectData & data )
{
	std::cout << "Data.dir: " << data.dir << "\n";
	std::string proj_dir, proj_src, proj_inc, proj_build;

	SetFolderPaths( data.dir, data.name, proj_dir, proj_src, proj_inc, proj_build );

	CreateDir( proj_dir );
	CreateDir( proj_src );
	CreateDir( proj_inc );
	CreateDir( proj_build );

	CreateFileWithContents( proj_src + "/main.cpp", DEFAULTMAIN );

	ConfigMgr config;

	config.SetProject( data );

	return config.CreateDefaultFile( proj_dir );
}
