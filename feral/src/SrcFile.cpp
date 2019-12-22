/**
 * \file SrcFile.cpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#include <cstdarg>

#include "SrcFile.hpp"

srcfile_t::srcfile_t( const std::string & full_name, const std::string & dir )
	: m_full_name( full_name ), m_dir( dir ) {}

void srcfile_t::add_data( const std::string & data ) { m_data += data; }
void srcfile_t::add_cols( const std::vector< src_col_range_t > & cols )
{ m_cols.insert( m_cols.end(), cols.begin(), cols.end() ); }

const std::string & srcfile_t::get_data() const { return m_data; }

void srcfile_t::fail( const size_t idx, const char * msg, ... ) const
{
	size_t line, col_begin, col_end, col;
	bool found = false;
	for( size_t i = 0; i < m_cols.size(); ++i ) {
		if( idx >= m_cols[ i ].begin && idx < m_cols[ i ].end ) {
			line = i;
			col_begin = m_cols[ i ].begin;
			col_end = m_cols[ i ].end;
			col = idx - col_begin;
			found = true;
			break;
		}
	}
	if( !found ) {
		fprintf( stderr, "could not find error: " );
		va_list vargs;
		va_start( vargs, msg );
		vfprintf( stderr, msg, vargs );
		fprintf( stderr, "\n" );
		va_end( vargs );
		fprintf( stderr, "in file: %s, with index: %zu\n", m_full_name.c_str(), idx );
		return;
	}

	fprintf( stderr, "%s %zu[%zu]: error: ", m_full_name.c_str(), line, col );

	va_list vargs;
	va_start( vargs, msg );
	vfprintf( stderr, msg, vargs );
	fprintf( stderr, "\n" );
	va_end( vargs );

	std::string err_line = m_data.substr( col_begin, col_end - col_begin );
	fprintf( stderr, "%s", err_line.c_str() );

	std::string spcs;
	int tab_count = 0;
	for( auto & ch : err_line ) {
		if( ch == '\t' ) ++tab_count;
	}
	for( int i = 0; i < tab_count; ++i ) spcs += '\t';
	for( int i = 0; i < col - tab_count; ++i ) {
		spcs += " ";
	}
	fprintf( stderr, "%s^\n", spcs.c_str() );
}
