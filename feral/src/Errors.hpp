/**
 * \file Errors.hpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <cstdlib>
#include <string>

enum Errors
{
	E_OK,

	E_FILE_IO_ERR,
	E_FILE_EMPTY,

	E_LEX_FAIL,

	E_FAIL,
};

namespace err
{
/**
 * \brief Fetches string equivalents of errors
 * 
 * \param code The error code using which, string is selected
 * \return const char* The resultant error string
 */
const char * str( Errors code );
}

#endif // ERRORS_HPP
