/**
 * \file Main.cpp
 * @author Electrux Redsworth (ElectruxRedsworth@gmail.com)
 * \date 2019-12-20
 * 
 * @copyright Copyright (c) 2019, all rights reserved.<br/>
 * This project uses the BSD 3-clause license,<br/>
 * attached in the project root directory.<br/>
 * 
 */

#include <vector>
#include <string>

#include "Config.hpp"
#include "Errors.hpp"
#include "Args.hpp"
#include "Env.hpp"
#include "FS.hpp"
#include "SrcFile.hpp"
#include "Lex.hpp"

int main( int argc, char ** argv )
{
	std::vector< std::string > args;
	size_t flags = args::get( argc, ( const char ** )argv, args );

	if( flags & OPT_V ) {
		fprintf( stdout, "Feral %d.%d.%d\nBuilt with %s\nOn %s\n", FERAL_VERSION_MAJOR,
			      FERAL_VERSION_MINOR, FERAL_VERSION_PATCH, BUILD_CXX_COMPILER, BUILD_DATE );
		return E_OK;
	}

	if( args.size() < 1 ) {
		fprintf( stderr, "usage: %s [flags] <source file>\n", argv[ 0 ] );
		return E_FAIL;
	}

	// absolute path of feral binary
	std::string fer_bin = env::get_file_abs_loc( argv[ 0 ] );

	// FROM HERE, REQUIRED BY IMPORT FUNCTION TOO
	// absolute directory & location of the primary source file
	std::string main_src_dir, main_src_path;
	main_src_dir = env::get_file_dir( args[ 0 ], & main_src_path );
	main_src_path = main_src_dir + "/" + main_src_path;

	Errors err = E_OK;

	// read source file
	srcfile_t srcfile( main_src_path, main_src_dir );
	err = fs::read_file( main_src_path, srcfile );
	if( err != E_OK ) {
		fprintf( stderr, "failed retrieving data from file: %s, with error: %s\n",
			 main_src_path.c_str(), err::str( err ) );
		return err;
	}

	// lexically analyze
	lex::toks_t toks;
	err = lex::tokenize( srcfile, toks );
	if( err != E_OK ) { goto cleanup; }

	// show tokens
	if( flags & OPT_T ) {
		fprintf( stdout, "Tokens (%zu):\n", toks.size() );
		for( size_t i = 0; i < toks.size(); ++i ) {
			auto & tok = toks[ i ];
			fprintf( stdout, "ID: %zu\tType: %s\tSymbol: %s\n",
				 i, TokStrs[ tok.type ], tok.data.c_str() );
		}
	}

cleanup:
	return err;
}
