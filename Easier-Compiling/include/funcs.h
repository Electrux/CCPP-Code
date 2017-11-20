//
// Created by electrux on 8/26/17.
//

#ifndef EASIERCOMPILING_FUNCS_H
#define EASIERCOMPILING_FUNCS_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct String
{
	char *str;
};


int net_argv_size( const int argc, const char ** argv )
{
	int count = 0;
	
	for( int i = 0; i < argc; ++i )
		count += strlen( argv[ i ] );
	
	return count;
}

char *get_output_file_name( const struct String *src)
{
	int loc = 0;
	for( int i = 0; src->str[ i ] != '\0'; ++i )
	{
		if( src->str[ i ] == '.' )
			loc = i;
	}
	
	char *name = ( char * ) malloc( ( loc + 1 ) * sizeof( char ) );
	
	strncpy( name, src->str, ( size_t )loc );
	name[ loc + 1 ] = '\0';
	
	return name;
}

int count_sources( const int argc, const char ** argv )
{
	int count = 0;
	
	for( int i = 1; i < argc; ++i )
	{
		// If the argument has .c or .cpp in it, it's a source file
		if( strstr( argv[ i ], ".c" ) != NULL || strstr( argv[ i ], ".cpp" ) != NULL )
			count++;
	}
	
	return count;
}

int get_sources( const int argc, const char ** argv, struct String **strs )
{
	int count = count_sources( argc, argv );
	
	size_t size_of_String = sizeof( struct String );
	size_t size_of_char = sizeof( char );
	
	*strs = ( struct String * ) malloc( size_of_String * count );
	
	int ctr = 0;
	
	for( int i = 1; i < argc; ++i )
	{
		// If the argument has .c or .cpp in it, it's a source file
		if( strstr( argv[ i ], ".c" ) != NULL || strstr( argv[ i ], ".cpp" ) != NULL ) {
			// Allocate size of argv[ i ] to the strs variable
			strs[ ctr ]->str = ( char * ) malloc( strlen( argv[ i ] ) * size_of_char );
			// Copy the string to the variable
			strcpy( strs[ ctr ]->str, argv[ i ] );
			ctr++;
		}
	}
	
	return count;
}

int is_option_available( const int argc, const char ** argv, const char *opt )
{
	for( int i = 1; i < argc; ++i )
	{
		if( argv[ i ][ 0 ] == '-' && strstr( argv[ i ], opt ) != NULL )
			return i;
	}
	
	return 0;
}

bool is_source_cpp( const int src_count, const struct String *srcs)
{
	for( int i = 0; i < src_count; ++i )
	{
		if(strstr( srcs[ i ].str, ".cpp" ) != NULL )
			return true;
	}
	
	return false;
}

#endif //EASIERCOMPILING_FUNCS_H
