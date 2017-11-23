#include <stdio.h>
#include <stdlib.h>

#include "../include/array.h"

int count_faults( struct array * memory, struct array * ref_str )
{
	int page_fault = 0;
	
	while( ref_str->count > 0 ) {
		if( find( memory, ref_str->arr[ 0 ] ) == -1 ) {
			page_fault++;

			printf( "fault: %d for %d\n", page_fault, ref_str->arr[ 0 ] );

			printf( "Current memory: " );
			display_array( memory );
			printf( "\n" );

			if( memory->size == memory->count )
				del_first_elem( memory );
			
			insert_elem( memory, ref_str->arr[ 0 ] );

			del_first_elem( ref_str );
		}
		else {
			del_first_elem( ref_str );
		}
	}

	return page_fault;
}

int main()
{
	struct array memory;
	struct array ref_str;

	printf( "Enter slot count: " );
	scanf( "%d", & memory.size );

	memory.arr = ( int * )malloc( sizeof( * memory.arr ) * memory.size );
	memory.count = 0;

	printf( "Enter page count: " );
	scanf( "%d", & ref_str.size );

	ref_str.count = ref_str.size;

	ref_str.arr = ( int * )malloc( sizeof( * ref_str.arr ) * ref_str.size );

	for( int i = 0; i < ref_str.size; ++i ) {
		printf( "Enter %d page: ", i + 1 );
		scanf( "%d", & ref_str.arr[ i ] );
	}

	printf( "\nTotal Faults: %d\n", count_faults( & memory, & ref_str ) );

	free( memory.arr );
	free( ref_str.arr );

	return 0;
}
