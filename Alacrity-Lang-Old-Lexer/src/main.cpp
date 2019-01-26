/*
	Copyright (c) 2018, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.

*/

#include <iostream>
#include <variant>

#include "../include/FileIO.hpp"
#include "../include/Lexer/Lexer.hpp"
#include "../include/Parser/Parser.hpp"

int main( int argc, char ** argv )
{
	if( argc < 1 ) {
		std::cerr << "Usage: " << argv[ 0 ] << " <source file>\n";
	}

	auto file_data_var = FS::ReadFile( argv[ 1 ] );
	if( std::holds_alternative< int >( file_data_var ) ) return std::get< int >( file_data_var );
	std::string file_data = std::get< std::string >( file_data_var );

	// TODO: Add basic preprocessor stuff for multiple file source support

	auto lex_syms_var = Lex::Tokenize( file_data );

	if( std::holds_alternative< int >( lex_syms_var ) ) return std::get< int >( lex_syms_var );
	auto lex_syms = std::get< Lex::Syms >( lex_syms_var );

	for( const auto & sym : lex_syms.GetSyms() ) {
		std::cout << "Symbol: " << sym->GetData()
			<< "\tType: " << Lex::SymTypeStrs[ sym->GetType() ]
			<< "\tDetail Type: " << sym->GetDetailType()
			<< "\tLocation: " << sym->GetLine() << "[" << sym->GetCol() << "]" << "\n";
	}

	auto parse_tree_var = Parser::Parse( & lex_syms );
	if( std::holds_alternative< int >( parse_tree_var ) ) return std::get< int >( parse_tree_var );
	auto parse_tree = std::get< Parser::ParseTree >( parse_tree_var );

	std::cout << "Post parsing:\n\n";

	std::cout << "ParseTree:\n";
	auto & stmts = parse_tree.GetStmts();
	for( int i = 0; i < ( int )stmts.size(); ++i ) {
		stmts[ i ]->Display( i != ( int )stmts.size() - 1 );
	}

	return 0;
}
