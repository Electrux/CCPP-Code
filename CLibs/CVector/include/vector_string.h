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

	if( vec->data == NULL )
		vec->data = ( char ** )malloc( sizeof( * vec->data ) * 1 );
	else
		vec->data = ( char ** )realloc( vec->data, vec->size + 1 );

	vec->data[ vec->size ] = strdup( str );

	vec->size += 1;

	return vec->size;
}

char * vector_str_pop( struct StrVector * vec, char * removed )
{
	if( vec->size <= 0 )
		return NULL;

	if( removed != NULL )
		strcpy( removed, vec->data[ vec->size - 1 ] );

	free( vec->data[ vec->size - 1 ] );

	if( vec->size - 1 > 0 )
		vec->data = ( char ** )realloc( vec->data, vec->size - 1 );
	else
		free( vec->data );

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
