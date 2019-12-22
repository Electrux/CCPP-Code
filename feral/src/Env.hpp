/**
 * \file Env.hpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#ifndef ENV_HPP
#define ENV_HPP

#include <vector>
#include <string>

namespace env
{
/**
 * \brief Get values from environment variables
 * 
 * \param key The variable from which to retrieve value
 * \return std::string The retrieved value; empty string if value does not exist for given key
 */
std::string get( const std::string & key );

/**
 * \brief Get the current working directory
 * 
 * \return std::string The current working directory
 */
std::string get_cwd();
/**
 * \brief Set the current working directory
 * 
 * \param dir Directory to which cwd is set
 */
void set_cwd( const std::string & dir );

/**
 * \brief Get precise directory of a file
 * 
 * \param file The file for which full path is retrieved
 * \param fname Optionally, pointer to a string which will be set to the file name (minus directory parts)
 * \return std::string The full location of file
 */
std::string get_file_dir( const std::string & file, std::string * fname = nullptr );
/**
 * \brief Gets the absolute path of a file
 * 
 * \param file The file for which full path is retrieved
 * \return std::string The full path of file
 */
inline std::string get_file_abs_loc( const std::string & file )
{
	std::string fdir, fname;
	fdir = get_file_dir( file, & fname );
	return fdir + "/" + fname;
}

/**
 * \brief Fetches exact location of a directory by changing cwd temporarily to it
 * 
 * \param dir The directory path, modified by the function
 */
void dir_full_path( std::string & dir );
}

#endif // ENV_HPP
