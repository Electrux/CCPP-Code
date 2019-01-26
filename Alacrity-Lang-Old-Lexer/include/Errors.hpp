/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <iostream>
#include <string>

inline void err( const std::string & msg, const int line = -1, const int col = -1 )
{
	if( line == -1 ) std::cerr << "Error: " << msg << "\n";
	else std::cerr << "Error on line " << line << " [" << col << "]" << ": " << msg << "\n";
}

inline int ret_err( const std::string & msg, const int err_code = -1, const int line = -1, const int col = -1 )
{
	err( msg, line, col );
	return err_code;
}

#endif // ERRORS_HPP