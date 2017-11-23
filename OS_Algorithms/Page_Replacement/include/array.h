#ifndef ARRAY_H
#define ARRAY_H

#include <stdio.h>

struct array
{
	int * arr;
	int size;
	int count;
#ifdef LRU
	int * last_used;
#endif
};

void del_first_elem( struct array * arr )
{
	for( int i = 0; i < arr->count - 1; ++i ) {
		arr->arr[ i ] = arr->arr[ i + 1 ];
	}

	if( arr->count > 0 )
		arr->count--;
}

void repl_elem( struct array * arr, int pos, int withelem )
{
	if( arr->count <= pos )
		return;

	arr->arr[ pos ] = withelem;
}

int insert_elem( struct array * arr, int val )
{
	if( arr->count == arr->size )
		return -1;

	arr->arr[ arr->count ] = val;

	return arr->count++;
}

int find( struct array * arr, int what )
{
	for( int i = 0; i < arr->count; ++i )
		if( arr->arr[ i ] == what )
			return i;

	return -1;
}

void display_array( struct array * arr )
{
	for( int i = 0; i < arr->count; ++i ) {
		printf( "%d ", arr->arr[ i ] );
	}
	
	printf( "\n" );
}

#endif
