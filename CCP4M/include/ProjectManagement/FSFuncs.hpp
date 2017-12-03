#ifndef FSFUNCS_HPP
#define FSFUNCS_HPP

#include <string>

void SetFolderPaths( std::string &directory,
		     const std::string &projectname,
		     std::string &projfolder,
		     std::string &srcfolder,
		     std::string &includefolder,
		     std::string &buildfolder );

int CreateDir( const std::string &dir );

void CreateFileWithContents( const std::string &filename,
			     const std::string &contents = std::string() );

#endif // FSFUNCS_HPP
