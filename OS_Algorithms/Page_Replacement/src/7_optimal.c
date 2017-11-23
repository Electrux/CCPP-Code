#include <stdio.h>
#include <stdlib.h>

#include "../include/array.h"

int get_longest_unused_from( struct array * memory, struct array * ref_str )
{
	if( memory->count <= 0 )
		return -1;
	
	int longestnum = memory->arr[ 0 ],
		longestduration = 0;
	
	for( int i = 0; i < memory->count; ++i ) {

		int num = memory->arr[ i ];
		int ctr = 0;
		while( ctr < ref_str->count ) {
			if( ref_str->arr[ ctr ] == num )
				break;

			ctr++;
		}

		if( ctr > longestduration ) {
			longestduration = ctr;
			longestnum = num;
		}
	}

	return longestnum;
}

int count_faults( struct array * memory, struct array * ref_str )
{
	int page_fault = 0;

	while( ref_str->count > 0 ) {
		if( find( memory, ref_str->arr[ 0 ] ) == -1 ) {
			page_fault++;

			printf( "fault: %d for %d\n", page_fault, ref_str->arr[ 0 ] );

			printf( "Current memory: " );
			display_array( memory );
			
			if( memory->size == memory->count ) {
				int longest_unused =
					get_longest_unused_from( memory, ref_str );
				int pos = find( memory, longest_unused );

				printf( "Longest unused %d at %d\n", longest_unused, pos );
				printf( "\n" );

				repl_elem( memory, pos, ref_str->arr[ 0 ] );
			}
			else {
				printf( "\n" );
				insert_elem( memory, ref_str->arr[ 0 ] );
			}
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
