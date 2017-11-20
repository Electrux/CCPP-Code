#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../include/funcs.h"

int main( int argc, char **argv )
{
	if( argc <= 1 ) {
		printf( "Usage: %s [Options] File(s)\n", argv[ 0 ] );
		exit( 0 );
	}
	
	struct String *sources;
	int source_count = get_sources( argc, ( const char ** )argv, &sources );
	
	if( source_count < 1) {
		printf( "Error: No source found in the arguments specified!\n" );
		exit( 0 );
	}
	
	int is_std_given = is_option_available( argc, ( const char ** )argv, "-std=" );
	int is_out_obj_given = is_option_available( argc, ( const char ** )argv, "-o" );
	
	bool is_src_cpp = is_source_cpp( source_count, sources );
	
	int out_obj_size = ( is_out_obj_given ) ? 0 : ( int )strlen( sources[ 0 ].str ) + 10;
	
	char fstr[ net_argv_size( argc, ( const char ** )argv ) + out_obj_size ];
	
	if( is_src_cpp )
	{
		strcpy( fstr, "clang++ " );
		
		if( !is_std_given )
			strcat( fstr, "-std=c++14 " );
	}
	else
	{
		strcpy( fstr, "clang " );
		
		if( !is_std_given )
			strcat( fstr, "-std=c11 " );
	}
	
	for( int i = 1; i < argc; ++i )
	{
		strcat( fstr, argv[ i ] );
		strcat( fstr, " " );
	}
	
	if( !is_out_obj_given )
	{
		strcat( fstr, "-o ");
		
		// Fetch the pointer to the ouput file name and concatenate it to fstr
		char *out_file = get_output_file_name( sources );
		strcat( fstr, out_file );

		// Free the allocated memory
		free( out_file );
	}
	
	//Free the memory allocated to each string in sources, and sources itself
	for( int i = 0; i < source_count; ++i )
		free( sources[i].str );
	free( sources );
	
	printf( "%s\n", fstr );
	
	system( fstr );
	return 0;
}