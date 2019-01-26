/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#ifndef IO_HPP
#define IO_HPP

#include <iostream>

namespace IO
{
	class Out
	{
		int m_tabs;
		void Tab() const;
		void Tab( const bool has_next_decl, const bool has_next_elem ) const;
	public:
		Out();
		const Out & operator() () const;
		const Out & operator() ( const bool has_next_decl, const bool has_next_elem = false ) const;
		const Out & operator<< ( const std::string & val ) const;
		const Out & operator<< ( const char * val ) const;
		const Out & operator<< ( const int val ) const;
		const Out & operator<< ( const long val ) const;
		const Out & operator<< ( const long long val ) const;
		const Out & operator<< ( const float val ) const;
		const Out & operator<< ( const double val ) const;
		const Out & operator<< ( const short val ) const;
		const Out & operator<< ( const void * val ) const;

		void IncTab( const int tabs = 1 );
		void DecTab( const int tabs = 1 );

		int GetTab() const;
	};

	extern Out out;
}

#endif // IO_HPP
