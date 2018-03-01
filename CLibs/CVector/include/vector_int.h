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

	if( vec->data != NULL )
		free( vec->data );
	free( vec );

	return size;
}

int vector_int_push( struct IntVector * vec, const int num )
{
	int * newdata = ( int * )malloc( sizeof( * newdata ) * ( vec->size + 1 ) );

	for( int i = 0; i < ( int )vec->size; ++i )
		newdata[ i ] = vec->data[ i ];

	newdata[ vec->size ] = num;

	if( vec->data != NULL )
		free( vec->data );

	vec->data = newdata;
	vec->size += 1;

	return vec->size;
}

int vector_int_pop( struct IntVector * vec, int * removed )
{
	if( vec->size <= 0 )
		return -1;

	if( removed != NULL )
		* removed = vec->data[ vec->size - 1 ];

	int * newdata = ( int * )malloc( sizeof( * newdata ) * ( vec->size - 1 ) );

	for( int i = 0; i < ( int )vec->size - 1; ++i )
		newdata[ i ] = vec->data[ i ];

	// The if vec->data == NULL condition is not really needed due to the vec->size ( first ) condition.
	free( vec->data );

	vec->data = newdata;
	vec->size -= 1;

	if( removed != NULL )
		return * removed;

	return -1;
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
