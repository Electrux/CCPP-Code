//
// Created by electrux on 7/25/17.
//

#ifndef INI_PARSER_ENUMS_HPP
#define INI_PARSER_ENUMS_HPP

#include <string>

namespace Electrux
{
	enum STATUS_CODES
	{
		SUCCESS,
		FILE_NOT_FOUND,
		FILE_NOT_OPEN_FOR_WRITE,
		EMPTY_FILE,
		NO_SECTION_EXISTS_IN_FILE,
		NO_SECTION_EXISTS_IN_PARSER,
		SECTION_NOT_EXISTS,
		SECTION_ALREADY_EXISTS,
		SECTION_REMOVED_NO_DATA,
		KEY_NOT_EXISTS,
		KEY_ALREADY_EXISTS,
		INVALID_DATA_TYPE,
		DATA_OUT_OF_RANGE,
		
		NONE,
		
		LAST_ELEMENT
	};
	
	enum FATAL_ERROR_MODES
	{
		THROW_EXCEPTION,
		STDOUT
	};
	
	const std::string STATUS_MSG[LAST_ELEMENT] = {
		
		"Success",
		"File not found",
		"Could not open file ( Unknown error )",
		"Empty file",
		"No section exists in file",
		"No section exists in parser",
		"Section not exists",
		"Section already exists",
		"Section removed because it was empty",
		"Key not exists",
		"Key already exists",
		"Invalid data type",
		"Data out of range",
		
		"None"
		
	};
}

#endif //INI_PARSER_ENUMS_HPP
