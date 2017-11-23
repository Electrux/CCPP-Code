#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LRU
#include "../include/array.h"

int get_least_recently_used( struct array * memory )
{
	if( memory->count <= 0 )
		return -1;
	
	int leastrecentnum = memory->arr[ 0 ],
		leastrecentduration = memory->last_used[ 0 ];
	
	for( int i = 0; i < memory->count; ++i ) {

		if( leastrecentduration < memory->last_used[ i ] ) {
			leastrecentduration = memory->last_used[ i ];
			leastrecentnum = memory->arr[ i ];
		}
	}

	return leastrecentnum;
}

int count_faults( struct array * memory, struct array * ref_str )
{
	int page_fault = 0;

	while( ref_str->count > 0 ) {

		for( int i = 0; i < memory->count; ++i )
			memory->last_used[ i ]++;

		int loc = find( memory, ref_str->arr[ 0 ] );

		if( loc == -1 ) {

			page_fault++;

			printf( "fault: %d for %d\n", page_fault, ref_str->arr[ 0 ] );

			printf( "Current memory: " );
			display_array( memory );

			if( memory->size == memory->count ) {
				int least_used =
					get_least_recently_used( memory );
				int pos = find( memory, least_used );

				printf( "Least recently unused %d at %d\n", least_used, pos );
				printf( "\n" );

				repl_elem( memory, pos, ref_str->arr[ 0 ] );
				memory->last_used[ pos ] = 0;
			}
			else {
				printf( "\n" );
				insert_elem( memory, ref_str->arr[ 0 ] );
			}
		}
		else {
			memory->last_used[ loc ] = 0;
		}

		del_first_elem( ref_str );
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
	memory.last_used = ( int * )malloc( sizeof( * memory.arr ) * memory.size );
	memset( memory.last_used, 0, memory.size * sizeof( * memory.last_used ) );

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
	free( memory.last_used );
	free( ref_str.arr );
	
	return 0;
}
