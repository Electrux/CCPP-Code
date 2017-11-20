//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_CMAKEGENERATOR_HPP
#define PROJECTCREATOR_CMAKEGENERATOR_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sys/stat.h>
#include <fstream>
#include "Data.hpp"
#include "FindSFML.hpp"
#include "DirFileFunctions.hpp"
#include "FindSDL2.hpp"
#include "FindSDL2_Image.hpp"
#include "FindSDL2_TTF.hpp"
#include "SFMLDefaultMain.hpp"
#include "SDL2DefaultMain.hpp"

const std::string CMAKEMODPATH = "/cmake_modules";

std::string SetupSDL2( const std::string &lang, const std::string &projfolder, bool withsdl2_image = false, bool withsdl2_ttf = false );
std::string SetupSFML( const std::string &lang, const std::string &projfolder );

void GenCMakeConfig( std::string &project, std::string &projfolder, std::string &lang, std::vector< std::string > &libs )
{
	std::string srcfile = "main." + LANGUAGEEXTS[ lang ];
	std::string standard = ( lang == "c" ) ? "set(CMAKE_C_STANDARD 11)\n" : "set(CMAKE_CXX_STANDARD 14)\n";

	std::string cmakestr =
			"cmake_minimum_required(VERSION " + CMAKE_MIN + ")\n"
			"\nset(CMAKE_MODULE_PATH \"${CMAKE_CURRENT_LIST_DIR}/cmake_modules\")\n"
			"project(" + project + ")\n\n"
			"set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build)\n"
			"\n" +
			standard +
			"\n"
			"set(SOURCE_FILES src/" + srcfile + ")\n"
			"add_executable(" + project + " ${SOURCE_FILES})\n"
			"\n";

	std::string cmakemodfolder = projfolder + CMAKEMODPATH;
	CreateDir( cmakemodfolder );


	if( std::find( libs.begin(), libs.end(), "sdl2" ) != libs.end() && std::find( libs.begin(), libs.end(), "sfml" ) != libs.end() )
		std::cout << "\nWARNING: Found SDL and SFML both in libraries list. Will prefer SDL. SFML will not be included.\n\n";

	if( std::find( libs.begin(), libs.end(), "sdl2" ) != libs.end() ) {
		bool usesdl2_image = ( std::find( libs.begin(), libs.end(), "sdl2img" ) != libs.end() );
		bool usesdl2_ttf = ( std::find( libs.begin(), libs.end(), "sdl2ttf" ) != libs.end() );

		cmakestr += SetupSDL2( lang, projfolder, usesdl2_image, usesdl2_ttf );

	} else if( std::find( libs.begin(), libs.end(), "sfml" ) != libs.end() ) {

		cmakestr += SetupSFML( lang, projfolder );

	}

	CreateFileWithContents( projfolder + "/CMakeLists.txt", cmakestr );
}


std::string SetupSDL2( const std::string &lang, const std::string &projfolder, bool withsdl2_image, bool withsdl2_ttf )
{
	std::string sdlstr;

	std::string findsdl2_image = ( withsdl2_image ) ? "find_package(SDL2_image REQUIRED >=2.0.0)\n" : "";
	std::string includesdl2_image = ( withsdl2_image ) ? " ${SDL2_IMAGE_INCLUDE_DIR}" : "";
	std::string linksdl2_image = ( withsdl2_image ) ? " ${SDL2_IMAGE_LIBRARY}" : "";

	std::string findsdl2_ttf = ( withsdl2_ttf ) ? "find_package(SDL2_ttf REQUIRED)\n" : "";
	std::string includesdl2_ttf = ( withsdl2_ttf ) ? " ${SDL2_TTF_INCLUDE_DIR}" : "";
	std::string linksdl2_ttf = ( withsdl2_ttf ) ? " ${SDL2_TTF_LIBRARY}" : "";


	if( lang != "c++" && lang != "c" ) {
		std::cout << "WARNING: Cannot include SDL2 since it is a C/C++ library.\n";
	}
	else {
		sdlstr = "find_package(SDL2 REQUIRED)\n" +
			findsdl2_image +
			findsdl2_ttf +
			"\n"
			"include_directories(${SDL2_INCLUDE_DIR}" + includesdl2_image + includesdl2_ttf + ")\n"
			"target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}" + linksdl2_image + linksdl2_ttf + ")\n";

		CreateFileWithContents( projfolder + CMAKEMODPATH + "/FindSDL2.cmake", FINDSDL2FILESTR );

		if( withsdl2_image )
			CreateFileWithContents( projfolder + CMAKEMODPATH + "/FindSDL2_image.cmake", FINDSDL2_IMAGEFILESTR );

		if( withsdl2_ttf )
			CreateFileWithContents( projfolder + CMAKEMODPATH + "/FindSDL2_ttf.cmake", FINDSDL2_TTFFILESTR );

		CreateFileWithContents( projfolder + "/src/main." + LANGUAGEEXTS[ lang ], SDL2DEFAULTMAIN[ lang ] );
	}

	return sdlstr;
}

std::string SetupSFML( const std::string &lang, const std::string &projfolder )
{
	std::string sfmlstr;
	if( lang != "c++" ) {
		std::cout << "WARNING: Cannot include SFML since it is a C++ library. Perhaps use SDL instead next time.\n";
	}
	else {
		sfmlstr =
			"find_package(SFML REQUIRED system window graphics network audio)\n"
			"if (SFML_FOUND)\n"
			"    include_directories(${SFML_INCLUDE_DIR})\n"
			"    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})\n"
			"endif()\n";

		CreateFileWithContents( projfolder + CMAKEMODPATH + "/FindSFML.cmake", FINDSFMLFILESTR );
		// Create a default main file for SFML.
		CreateFileWithContents( projfolder + "/src/main.cpp", SFMLDEFAULTMAIN );
	}
	return sfmlstr;
}

#endif //PROJECTCREATOR_CMAKEGENERATOR_HPP
