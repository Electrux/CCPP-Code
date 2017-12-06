#include <string>
#include <cstdlib>

#include "../include/Data.hpp"
#include "../include/FileFunctions.hpp"

bool GetEnv( std::string key, std::string & val )
{
	val = std::getenv( key.c_str() );

	return !val.empty();
}

bool GetFile( std::string & file )
{
	std::string homedir;

	if( !GetEnv( "HOME", homedir ) )
		return false;

	file = homedir + "/" + filename;

	return true;
}
