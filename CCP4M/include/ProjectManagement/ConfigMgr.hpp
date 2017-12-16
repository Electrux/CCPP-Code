#ifndef CONFIGMGR_HPP
#define CONFIGMGR_HPP

#include <string>

#include "ProjectData.hpp"
#include "../INI_System/INI_Parser.hpp"

class ConfigMgr
{
	ProjectData data;
	Electrux::INI_Parser parser;

public:

	void SetProject( ProjectData & proj );
	ProjectData GetProject();

	int CreateDefaultConfig( std::string project_dir );

	int RetrieveConfig( std::string project_dir );

	std::string GetDataString( std::string section, std::string key );

	std::string GetLibraryFlags( std::string lib );
};

#endif // CONFIGMGR_HPP
