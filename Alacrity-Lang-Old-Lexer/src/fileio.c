#include <stdio.h>
#include <stdlib.h>

#include "vec.h"
#include "fileio.h"

vec_t * read_file( const char * file )
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	fp = fopen( file, "r" );
	if( fp == NULL ) {
		fprintf( stdout, "failed to open source file: %s\n", file );
		return NULL;
	}

	vec_t * lines = vec_create( -1, NULL );

	while( ( read = getline( & line, & len, fp ) ) != -1 ) {
		vec_add( lines, line );
	}

	fclose( fp );
	if( line ) free( line );
	return lines;
}
