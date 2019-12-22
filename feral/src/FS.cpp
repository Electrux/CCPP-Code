/**
 * \file FS.cpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#include <cstdio>
#include <string>

#include "FS.hpp"

namespace fs
{
Errors read_file( const std::string & file, srcfile_t & content )
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen( file.c_str(), "r" );
	if( fp == NULL ) {
		fprintf( stderr, "failed to open source file: %s\n", file.c_str() );
		return E_FILE_IO_ERR;
	}

	size_t prefix_idx = content.get_data().size();
	std::string code;
	std::vector< src_col_range_t > cols;
	size_t begin, end;
	while( ( read = getline( & line, & len, fp ) ) != -1 ) {
		begin = code.size();
		code += line;
		end = code.size();
		cols.push_back( { prefix_idx + begin, prefix_idx + end } );
	}

	fclose( fp );
	if( line ) free( line );

	if( code.empty() ) return E_FILE_EMPTY;

	content.add_data( code );
	content.add_cols( cols );
	return E_OK;
}
}
