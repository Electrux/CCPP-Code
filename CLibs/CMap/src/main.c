#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define ALLOC( x, y ) ( x * ) malloc( sizeof( x ) * y )

struct HashVal
{
	char * key;
	void * val;
};

struct HashTable
{
	size_t size;
	size_t used;
	HashVal * values;
};

int hash_func( const char * key, const int tablesize, const int iteration )
{
	if( tablesize < 1 )
		return -1;

	const char * it = key;
	int hash = 0;

	while( * it != '\0' ) {
		int val = ( int )( * it ) + iteration;

		hash += val;
		hash *= val;
		hash ^= val;
		hash <<= val % 3;
		hash /= val;
		hash %= INT_MAX;

		++it;
	}

	return hash % tablesize;
}

struct HashTable * hash_create_empty()
{
	struct HashTable * hash = ALLOC( struct HashTable, 1 );
	if( hash == NULL )
		return NULL;

	hash->size = 0;
	hash->used = 0;
	hash->values = NULL;

	return hash;
}

struct HashTable * hash_create( const int size )
{
	if( size < 1 )
		return NULL;

	struct HashTable * hash = ALLOC( struct HashTable, 1 );
	if( hash == NULL )
		return NULL;

	hash->size = size;
	hash->used = 0;
	hash->values = ALLOC( struct HashVal, hash->size );

	return hash;
}



int main()
{
	printf( "%d\n", hash_func( "oe", 50, 0 ) );
	return 0;
}
