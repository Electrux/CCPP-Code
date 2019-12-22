/**
 * \file SrcFile.hpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#ifndef SRC_FILE_HPP
#define SRC_FILE_HPP

#include <vector>
#include <string>

#include "Errors.hpp"

/**
 * \brief Defines the range of columns for a line of source code
 * 
 */
struct src_col_range_t
{
	size_t begin;
	size_t end;
};

/**
 * \brief Defines a source code file object, contains its name, directory,
 * content, and line divisions (based on indices)
 * 
 */
class srcfile_t
{
	// full_name and dir are never modified once set
	std::string m_full_name;
	std::string m_dir;
	std::string m_data; // content
	std::vector< src_col_range_t > m_cols;
public:
	/**
	 * \brief Construct a new srcfile_t object
	 * 
	 * \param full_name Full name (path) of source file
	 * \param dir Directory of source file
	 */
	srcfile_t( const std::string & full_name, const std::string & dir );

	/**
	 * \brief Append content to an instance
	 * 
	 * \param data The content to be appended
	 */
	void add_data( const std::string & data );
	/**
	 * \brief Append line divisions to an instance
	 * 
	 * \param cols Line divisions to be appended (vector of src_col_range_t)
	 */
	void add_cols( const std::vector< src_col_range_t > & cols );

	/**
	 * \brief Get the data object
	 * 
	 * \return const std::string& Returns the data object with const qualifier
	 */
	const std::string & get_data() const;

	/**
	* \brief Print a proper message on code failure
	* 
	* \param idx Index in the code where error is
	* \param msg Error message to show
	* \param ... Format args for error message
	*/
	void fail( const size_t idx, const char * msg, ... ) const;
};

#endif // SRC_FILE_HPP
