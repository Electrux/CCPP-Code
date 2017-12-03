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

	int CreateDefaultFile( std::string project_dir );
};

#endif // CONFIGMGR_HPP
