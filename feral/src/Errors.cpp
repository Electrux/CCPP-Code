/**
 * \file Errors.cpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#include "Errors.hpp"

namespace err
{
const char * str( Errors code )
{
	switch ( code ) {
	case E_OK: return "ok";
	case E_FILE_IO_ERR: return "file io error";
	case E_FILE_EMPTY: return "file is empty";
	case E_LEX_FAIL: return "lexer failed";
	case E_FAIL: // fallthrough
	default: return "fail";
	}
}
}
