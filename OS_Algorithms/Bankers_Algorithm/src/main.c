#include <stdio.h>
#include <stdlib.h>

struct System
{
	int * available;
};

struct Process
{
	int * allocated;
	int * max;
};

int ** create_matrix( int column, int row )
{
	int ** temp;

	temp = ( int ** ) malloc( sizeof( * temp ) * column );

	for( int i = 0; i < column; ++i ) {
		int * rows = ( int * ) malloc( sizeof( * rows ) * row );
		temp[ i ] = rows;
	}

	return temp;
}

int * create_array( int size )
{
	int * temp;

	temp = ( int * ) malloc( sizeof( * temp ) * size );

	return temp;
}

int * copy_array( int * from, int size )
{
	int * temp;

	temp = ( int * ) malloc( sizeof( * temp ) * size );

	for( int i = 0; i < size; ++i )
		temp[ i ] = from[ i ];

	return temp;
}

struct Process * create_process( int r_types )
{
	struct Process * proc = ( struct Process * )
		malloc( sizeof( * proc ) );

	proc->allocated = create_array( r_types );
	proc->max = create_array( r_types );

	for( int i = 0; i < r_types; ++i ) {
		printf( "Enter process allocated for %d: ", i );
		scanf( "%d", & proc->allocated[ i ] );
		
		printf( "Enter process max for %d: ", i );
		scanf( "%d", & proc->max[ i ] );
	}

	return proc;
}

int all_less_or_equal( int * arr1, int * arr2, int size )
{
	int cond = 1;

	for( int i = 0; i < size; ++i ) {
		cond &= arr1[ i ] <= arr2[ i ];
	}

	return cond;
}

int is_finished( struct Process * proc, const int r_types )
{
	int ret_val = 1;

	for( int i = 0; i < r_types; ++i ) {
		ret_val &= proc->allocated[ i ] == proc->max[ i ];
	}

	return ret_val;
}

int * get_need( struct Process * proc, int r_types )
{
	int * need = ( int * )
		malloc( sizeof( * need ) * r_types );

	for( int j = 0; j < r_types; ++j )
		need[ j ] = proc->max[ j ] - proc->allocated[ j ];

	return need;
}

int safety_check( struct System * sys,
		  struct Process ** processes,
		  const int r_types,
		  const int proccount )
{
	int * work = copy_array( sys->available, r_types );

	int * finished = create_array( proccount );

	for( int i = 0; i < proccount; ++i )
		finished[ i ] = 0;

	int tocontinue = 1;

	while( tocontinue ) {
		int nomodification = 1;

		for( int i = 0; i < proccount; ++i ) {
			int * need = get_need( processes[ i ], r_types );
			if( all_less_or_equal( 
		}

		if( nomodification )
			tocontinue = 0;
	}
}

int main()
{
	int r_types;
	int proccount;

	struct System sys;
	struct Process ** processes;

	printf( "Enter resouce count: " );
	scanf( "%d", & r_types );

	sys.available = create_array( r_types );

	printf( "\nEnter resources available:-\n" );

	for( int i = 0; i < r_types; ++i ) {
		printf( "Resource %d: ", i );
		scanf( "%d", & sys.available[ i ] );
	}

	printf( "\nEnter process count: " );
	scanf( "%d", & proccount );

	processes = ( struct Process ** ) malloc( sizeof( * processes ) * proccount );

	printf( "\nEnter process info:-\n" );

	for( int i = 0; i < proccount; ++i ) {
		printf( "\nEnter process %d info:-\n", i );
		processes[ i ] = create_process( r_types );
	}

	for( int i = 0; i < proccount; ++i ) {
		free( processes[ i ]->allocated );
		free( processes[ i ]->max );
	}
	free( processes );

	free( sys.available );

	return 0;
}
