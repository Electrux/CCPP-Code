//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_DATA_HPP
#define PROJECTCREATOR_DATA_HPP

#include <map>
#include <string>

static std::map< std::string, std::string > LANGUAGEEXTS = {
	{ "c", "c" },
	{ "c++" , "cpp" }
};

static std::map< std::string, std::string > DEFAULT_INCLUDES = {
	{ "c", "#include <stdio.h>\n\n" },
	{ "c++", "#include <iostream>\n\n" }
};

const std::string CMAKE_MIN = "3.2";

class Flags
{
public:
	static const std::string HELP,
		LANG,
		DIR,
		PROJNAME,
		LIBS;
};

const std::string Flags::HELP     = "--help";
const std::string Flags::LANG     = "--lang";
const std::string Flags::DIR      = "--dir";
const std::string Flags::PROJNAME = "--name";
const std::string Flags::LIBS     = "--libs";

#endif //PROJECTCREATOR_DATA_HPP
