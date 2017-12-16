#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

#include "../../include/CommonFuncs.hpp"

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

// Can create directory in directory B)
int CreateDir( const std::string &dir )
{
	struct stat info;

	if( stat( dir.c_str(), & info ) == 0 )
		return 0;

	std::vector< std::string > dirs;

	std::string temp;
	for( auto ch : dir ) {

		if( ch == '/' ) {

			dirs.push_back( temp );
			temp.clear();
		}
		else {
			temp += ch;
		}
	}

	if( !temp.empty() )
		dirs.push_back( temp );

	std::cout << "Creating Directory: " << dir << "\n";

	int retval = 0;
	std::string finaldir;

	for( int i = 0; i < ( int )dirs.size(); ++i ) {

		finaldir += dirs[ i ];

		if( stat( finaldir.c_str(), & info ) != 0 )
			retval |= mkdir( finaldir.c_str(), 0755 );

		finaldir += "/";
	}

	return retval;
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

bool IsLatestBuild( std::string filename )
{
	std::vector< std::string > includes;

	std::fstream file;

	std::string srcfullpath = "src/" + GetStringTillLastSlash( filename );

	file.open( "src/" + filename, std::ios::in );

	if( !file )
		return false;

	std::string line;

	while( std::getline( file, line ) ) {

		if( line.find( "#include \"" ) != std::string::npos ) {

			//std::cout << "includes: " << line << "\n";

			includes.push_back( GetStringBetweenQuotes( line ) );
		}
	}

	file.close();

	long long buildfilemodtime = GetLastModifiedTime(
		"build/buildfiles/" + filename + ".o" );

	if( buildfilemodtime < 0 )
		return false;

	for( auto inc : includes ) {

		long long modtime = GetLastModifiedTime( srcfullpath + inc );

		if( modtime < 0 || modtime > buildfilemodtime )
			return false;
	}

	long long srcfilemodtime = GetLastModifiedTime( "src/" + filename );

	if( srcfilemodtime < 0 || srcfilemodtime > buildfilemodtime )
		return false;

	return true;
}

long long GetLastModifiedTime( std::string file )
{
	struct stat info;

	if( stat( file.c_str(), & info ) != 0 )
		return -1;

	return info.st_mtime;
}

int GetFilesInDir( std::string dir, std::vector< std::string > & temp, bool recursive )
{
	struct stat info;
	if( stat( dir.c_str(), & info ) != 0 )
		return 1;

	DIR* dirp = opendir( dir.c_str() );
	struct dirent * p;

	std::string tempdir;

	if( dir == "src" )
		tempdir = "";
	else if( dir.find( "src/" ) != std::string::npos )
		tempdir = dir.substr( 4 ) + "/";

	while( ( p = readdir( dirp ) ) != NULL ) {

		if( strcmp( p->d_name, "." ) == 0 || strcmp( p->d_name, ".." ) == 0 )
			continue;

		if( p->d_type == DT_DIR && recursive )
			GetFilesInDir( dir + "/" + p->d_name, temp );
		else if( p->d_type != DT_DIR )
			temp.push_back( tempdir + p->d_name );
	}

	return 0;
}
