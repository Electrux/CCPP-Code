#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>

#include "../../include/ProjectManagement/FSFuncs.hpp"

void SetFolderPaths( std::string &directory,
		     const std::string &projectname,
		     std::string &projfolder,
		     std::string &srcfolder,
		     std::string &includefolder,
		     std::string &buildfolder )
{
	// Incase the dirname given by user does not contain '/' at the end...
	directory = ( *(directory.end() - 1) == '/' ) ? directory : directory + "/";


	projfolder      = directory + projectname;

	srcfolder       = projfolder + "/src";
	includefolder   = projfolder + "/include";
	buildfolder     = projfolder + "/build";
}

int CreateDir( const std::string &dir )
{
	std::cout << "Creating Directory: " << dir << "\n";

	return mkdir( dir.c_str(), 0755 );
}

void CreateFileWithContents( const std::string &filename,
			     const std::string &contents )
{
	std::cout << "Creating file: " << filename << "\n";

	std::fstream file;

	file.open( filename, std::ios::out );

	if( !contents.empty() )
		file << contents;

	file.close();
}
