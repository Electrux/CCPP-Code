/*
	Copyright (c) 2019, Electrux
	All rights reserved.
	Using the BSD 3-Clause license for the project,
	main LICENSE file resides in project's root directory.

	Please read that file and understand the license terms
	before using or altering the project.
*/

#include <dlfcn.h>

#include "dylib.h"

typedef struct
{
	char * file;
	void * handle;
	UT_hash_handle hh;
} handles_t;

static handles_t * hnds = NULL;

void dy_init()
{
	hnds = NULL;
}

void dy_deinit()
{
	if( hnds == NULL ) return;
	handles_t * res, * tmp;
	HASH_ITER( hh, hnds, res, tmp ) {
		HASH_DEL( hnds, res );
		dlclose( res->handle );
		free( res->file );
		free( res );
	}
}

void * dy_load( const char * file_str )
{
	handles_t * res;
	HASH_FIND_STR( hnds, file_str, res );
	if( res != NULL ) return res->handle;
	void * hnd = dlopen( file_str, RTLD_LAZY );
	if( hnd == NULL ) {
		printf( "dynamic library error: %s\n", dlerror() );
		return NULL;
	}
	res = malloc( sizeof( handles_t ) );
	res->file = strdup( file_str );
	res->handle = hnd;
	HASH_ADD_STR( hnds, file, res );
}

void dy_unload( const char * file_str )
{
	handles_t * res;
	HASH_FIND_STR( hnds, file_str, res );
	if( res == NULL ) return;
	HASH_DEL( hnds, res );
	dlclose( res->handle );
	free( res->file );
	free( res );
}

void * dy_get_sym( const char * file_str, const char * sym )
{
	handles_t * res;
	HASH_FIND_STR( hnds, file_str, res );
	if( res == NULL ) return NULL;
	return dlsym( res->handle, sym );
}
