#ifndef VECTOR_INT_H
#define VECTOR_INT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct IntVector
{
	size_t size;
	int * data;
};

struct IntVector * create_int_vector()
{
	struct IntVector * vec = ( struct IntVector * )malloc( sizeof( struct IntVector ) );

	vec->size = 0;
	vec->data = NULL;

	return vec;
}

int delete_int_vector( struct IntVector * vec )
{
	if( vec == NULL )
		return -1;

	int size = vec->size;

	if( vec->size > 0 )
		free( vec->data );
	free( vec );

	return size;
}

int vector_int_push( struct IntVector * vec, const int num )
{
	vec->data = ( int * )realloc( vec->data, ( vec->size + 1 ) * sizeof( * vec->data ) );

	vec->data[ vec->size ] = num;

	vec->size += 1;

	return vec->size;
}

int vector_int_pop( struct IntVector * vec )
{
	if( vec->size <= 0 )
		return -1;

	int retval = vec->data[ vec->size - 1 ];

	if( vec->size - 1 < 1 )
		free( vec->data );
	else
		vec->data = ( int * )realloc( vec->data, vec->size - 1 );

	vec->size -= 1;

	return retval;
}

int vector_int_get( const struct IntVector * vec, const int loc )
{
	if( ( int )vec->size <= loc )
		return -1;

	return vec->data[ loc ];
}

void vector_int_print( const struct IntVector * vec )
{
	printf( "[ " );
	for( int i = 0; i < ( int )vec->size; ++i ) {
		if( i == ( int ) vec->size - 1 )
			printf( "%d", vec->data[ i ] );
		else
			printf( "%d, ", vec->data[ i ] );
	}
	printf( " ]" );
}

#endif // VECTOR_INT_H
