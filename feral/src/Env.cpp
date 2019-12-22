/**
 * \file Env.cpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#include "Env.hpp"

#define MAX_PATH 2048

namespace env
{
std::string get( const std::string & key )
{
	const char * env = std::getenv( key.c_str() );
	return env == NULL ? "" : env;
}

std::string get_cwd()
{
	char cwd[ MAX_PATH ];
	if( getcwd( cwd, sizeof( cwd ) ) != NULL ) {
		return cwd;
	}
	return "";
}

void set_cwd( const std::string & dir )
{
	chdir( dir.c_str() );
}

std::string get_file_dir( const std::string & file, std::string * fname )
{
	auto last_slash_loc = file.find_last_of( '/' );
	if( last_slash_loc == std::string::npos ) {
		if( fname != nullptr ) {
			* fname = file;
		}
		return get_cwd();
	}
	std::string fdir = file.substr( 0, last_slash_loc );
	if( fname != nullptr ) {
		* fname = file.substr( last_slash_loc + 1 );
	}
	dir_full_path( fdir );
	return fdir;
}

void dir_full_path( std::string & dir )
{
	std::string cwd = get_cwd();
	set_cwd( dir );
	std::string res = get_cwd();
	set_cwd( cwd );
	dir = res;
}
}
