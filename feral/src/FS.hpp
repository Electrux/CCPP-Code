/**
 * \file FS.hpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#ifndef FS_HPP
#define FS_HPP

#include <string>
#include <unistd.h>

#include "Errors.hpp"
#include "SrcFile.hpp"

namespace fs
{
/**
 * \brief Read entire file in a srcfile_t struct
 * 
 * \param file File to read
 * \param content All the file data is stored here
 * \return Errors Status of file read operation
 */
Errors read_file( const std::string & file, srcfile_t & content );

/**
 * \brief Check if a file exists
 * 
 * \param file File to check
 * \return bool True if exists, false if not 
 */
inline bool fexists( const std::string & file )
{
	return access( file.c_str(), F_OK ) != -1;
}
}

#endif // FS_HPP
