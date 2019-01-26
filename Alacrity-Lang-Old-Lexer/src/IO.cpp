/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#include <iostream>

#include "../include/IO.hpp"

using namespace IO;

IO::Out::Out() : m_tabs( 0 )
{}

void IO::Out::Tab() const
{
	for( int i = 0; i < m_tabs; ++i ) std::cout << "  ";
}

void IO::Out::Tab( const bool has_next_decl, const bool has_next_elem ) const
{
	for( int i = 0; i < m_tabs; ++i ) {
		if( i == m_tabs - 1 ) {
			if( has_next_elem ) std::cout << "  ├─";
			else std::cout << "  └─";
		}
		else {
			if( has_next_decl ) std::cout << "  │";
			else std::cout << "   ";
		}
	}
}

const Out & IO::Out::operator() () const
{
	Tab();
	return * this;
}

const Out & IO::Out::operator() ( const bool has_next_decl, const bool has_next_elem ) const
{
	Tab( has_next_decl, has_next_elem );
	return * this;
}

const Out & IO::Out::operator<< ( const std::string & val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const char * val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const int val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const long val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const long long val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const float val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const double val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const short val ) const
{
	std::cout << val;
	return * this;
}

const Out & IO::Out::operator<< ( const void * val ) const
{
	std::cout << val;
	return * this;
}

void IO::Out::IncTab( const int tabs )
{
	m_tabs += tabs;
}

void IO::Out::DecTab( const int tabs )
{
	m_tabs -= tabs;
}

int IO::Out::GetTab() const
{
	return m_tabs;
}

IO::Out IO::out;
