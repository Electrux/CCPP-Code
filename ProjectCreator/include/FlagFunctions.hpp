//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_FLAGFUNCTIONS_HPP
#define PROJECTCREATOR_FLAGFUNCTIONS_HPP

#include <iostream>
#include <vector>
#include "Data.hpp"

bool ShowHelpIfNeeded( const std::vector< std::string > &args )
{
	auto helpflag = std::find( args.begin(), args.end(), Flags::HELP );

	if( helpflag == args.end() ) return false;

	std::cout << "Usage:\n";
	std::cout << "\t--lang <Language>\t\tSet the language for the project\n";
	std::cout << "\t--name <Name>\t\tName of the project\n";
	std::cout << "\t--dir  <Directory>\t\tDirectory for the project\n";
	std::cout << "\t--libs <Libraries>\t\tComma separated list of libraries to include in the project\n";
	std::cout << "\n\t\tExample: " << args[ 0 ] << " --lang c++ --name test --dir ~ --libs sdl\n";
	std::cout << "\nEnd\n\n";

	return true;
}

bool GetLangFromFlag( const std::vector< std::string > &args, std::string &language )
{
	auto langflag = std::find( args.begin(), args.end(), Flags::LANG );

	// Language check.
	if( langflag == args.end() ) {
		std::cout << "Error: No language flag found. Use " + Flags::LANG + " <language> flag.\n";
		return false;
	}


	auto lang = langflag + 1;

	if( lang == args.end() || lang->find( "--" ) != std::string::npos || LANGUAGEEXTS.find( *lang ) == LANGUAGEEXTS.end() ) {
		std::cout << "Error: No (valid) language specified after the " + Flags::LANG + " flag.\n";
		std::cout << "\tValid languages are:\n";

		for( auto _lang : LANGUAGEEXTS )
			std::cout << "\t\t" << _lang.first << "\n";

		return false;
	}



	language = *lang;

	return true;
}

bool GetProjNameFromFlag( const std::vector< std::string > &args, std::string &proj )
{
	auto projnameflag = std::find( args.begin(), args.end(), Flags::PROJNAME );

	if( projnameflag == args.end() ) {
		std::cout << "Error: No Project Name flag found. Use " + Flags::PROJNAME + " <Project_Name> flag.\n";
		std::cout << "Note that no spaces are allowed in project name.\n";
		return false;
	}


	auto projname = projnameflag + 1;

	if( projname == args.end() || ( projname->find( "--" ) != std::string::npos ) ) {
		std::cout << "Error: No project name specified after the " + Flags::PROJNAME + " flag.\n";
		return false;
	}



	proj = *projname;

	return true;
}

bool GetDirFromFlag( const std::vector< std::string > &args, std::string &dir )
{
	auto dirflag = std::find( args.begin(), args.end(), Flags::DIR );

	if( dirflag == args.end() ) {
		std::cout << "Note: No custom directory was specified.\n";
		dir = ".";
		return false;
	}


	auto dirname = dirflag + 1;

	if( dirname == args.end() || ( dirname->find( "--" ) != std::string::npos ) ) {
		std::cout << "Error: No directory specified after the " + Flags::DIR + " flag.\n";
		return false;
	}



	dir = *dirname;

	if( *dir.begin() != '/' && *dir.begin() != '.' )
		dir = "./" + dir;

	return true;
}

bool GetLibsFromFlag( const std::vector< std::string > &args, std::vector< std::string > &libs )
{
	auto libflag = std::find( args.begin(), args.end(), Flags::LIBS );

	if( libflag == args.end() ) {
		std::cout << "Note: No library was specified.\n";
		return false;
	}


	auto dirs = libflag + 1;

	if( dirs == args.end() || ( dirs->find( "--" ) != std::string::npos ) ) {
		std::cout << "Error: No directory specified after the " + Flags::LIBS + " flag.\n";
		return false;
	}


	std::string temp;

	for( auto ch : *dirs ) {
		if( ch == ',' ) {

			libs.push_back( temp );
			temp.clear();

		} else {

			temp.push_back( ch );

		}
	}


	if( !temp.empty() )
		libs.push_back( temp );

	return true;
}

#endif //PROJECTCREATOR_FLAGFUNCTIONS_HPP
