#include <stdio.h>

#include "core.h"
#include "fileio.h"
#include "lexer.h"

int main( int argc, char ** argv )
{
	if( argc < 2 ) {
		fprintf( stdout, "usage: %s <source file>", argv[ 0 ] );
		return FAIL;
	}
	vec_t * input = read_file( argv[ 1 ] );
	if( input == NULL ) {
		return FILE_IO_ERR;
	}
	// tokenize the input
	status_t lex_status = tokenize( input );
	if( lex_status.code != OK ) return lex_status.code;
	vec_t * toks = ( vec_t * )lex_status.data;

	int len = vec_count( toks );
	for( int i = 0; i < len; ++i ) {
		const token_t * tok = ( const token_t * )vec_get_data( toks, i );
		fprintf( stdout, "Symbol: %s\ttype: %s\n", tok->data, TokStrs[ tok->type ] );
		fflush( stdout );
	}

//cleanup:
	vec_destroy( & toks );
	vec_destroy( & input );
	return 0;
}
