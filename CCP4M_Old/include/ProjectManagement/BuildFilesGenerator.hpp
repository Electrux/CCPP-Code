#ifndef BUILDFILESGENERATOR_HPP
#define BUILDFILESGENERATOR_HPP

#include <vector>

#include "ProjectData.hpp"
#include "ConfigMgr.hpp"

int GenerateBuildFiles();

int CreateBuildDirectories( std::vector< std::string > & othersrc );

std::string GetDirectoryFromSource( std::string src );

int GetBuildData( ConfigMgr & config, ProjectData & data, std::string & mainsrc,
		  std::string & flags, std::string & libs,
		  std::vector< std::string > & othersrc );

int GetWildCardSources( std::vector< std::string > & __othersrc,
			std::vector< std::string > & othersrc );

#endif // BUILDFILESGENERATOR_HPP
