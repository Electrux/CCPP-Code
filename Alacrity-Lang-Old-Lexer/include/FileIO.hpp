/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef FILE_IO_HPP
#define FILE_IO_HPP

#include <string>

#include "Core.hpp"

namespace FS
{
	std::variant< int, std::string > ReadFile( const std::string & file_name );
}

#endif // FILE_IO_HPP