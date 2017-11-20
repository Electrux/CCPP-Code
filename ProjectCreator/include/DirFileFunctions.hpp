//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_DIRFILEFUNCTIONS_HPP
#define PROJECTCREATOR_DIRFILEFUNCTIONS_HPP

#include <string>
#include <sys/stat.h>

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

void CreateFileWithContents( const std::string &filename, const std::string &contents = std::string() )
{
	std::cout << "Creating file: " << filename << "\n";

	std::fstream file;

	file.open( filename, std::ios::out );

	if( !contents.empty() )
		file << contents;

	file.close();
}

#endif //PROJECTCREATOR_DIRFILEFUNCTIONS_HPP
