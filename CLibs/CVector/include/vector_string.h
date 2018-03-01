#ifndef VECTOR_STRING_H
#define VECTOR_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StrVector
{
	size_t size;
	char ** data;
};

struct StrVector * create_str_vector()
{
	struct StrVector * vec = ( struct StrVector * )malloc( sizeof( struct StrVector ) );

	vec->size = 0;
	vec->data = NULL;

	return vec;
}

int delete_str_vector( struct StrVector * vec )
{
	if( vec == NULL )
		return -1;

	// How many are deleted
	int size = vec->size;

	for( int i = 0; i < size; ++i )
		free( vec->data[ i ] );

	if( vec->data != NULL )
		free( vec->data );

	free( vec );

	return size;
}

int vector_str_push( struct StrVector * vec, const char * str )
{
	if( strlen( str ) <= 0 )
		return 0;

	char ** newdata = ( char ** )malloc( sizeof( * newdata ) * ( vec->size + 1 ) );

	for( int i = 0; i < ( int )vec->size; ++i )
		newdata[ i ] = vec->data[ i ];

	newdata[ vec->size ] = strdup( str );

	if( vec->data != NULL )
		free( vec->data );

	vec->data = newdata;
	vec->size += 1;

	return vec->size;
}

char * vector_str_pop( struct StrVector * vec, char * removed, const int removed_size )
{
	if( vec->size <= 0 )
		return NULL;

	int len = strlen( vec->data[ vec->size - 1 ] );
	// Increment by one to account for null terminator
	len += 1;

	if( removed_size > 0 && removed_size >= len && removed != NULL )
		strcpy( removed, vec->data[ vec->size - 1 ] );

	char ** newdata = ( char ** )malloc( sizeof( * newdata ) * ( vec->size - 1 ) );

	for( int i = 0; i < ( int )vec->size - 1; ++i )
		newdata[ i ] = vec->data[ i ];

	free( vec->data[ vec->size - 1 ] );
	free( vec->data );

	vec->data = newdata;
	vec->size -= 1;

	return removed;
}

char * vector_str_get( const struct StrVector * vec, const int loc )
{
	if( ( int )vec->size <= loc )
		return NULL;

	return vec->data[ loc ];
}

void vector_str_print( const struct StrVector * vec )
{
	printf( "[ " );
	for( int i = 0; i < ( int )vec->size; ++i ) {
		if( i == ( int ) vec->size - 1 )
			printf( "%s", vec->data[ i ] );
		else
			printf( "%s, ", vec->data[ i ] );
	}
	printf( " ]" );
}

#endif // VECTOR_STRING_HPP
