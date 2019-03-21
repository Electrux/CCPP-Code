#ifndef ALLOC_H
#define ALLOC_H

#include <stdlib.h>

#include "core.h"

static inline void * alalloc( const size_t sz )
{
	void * tmp = malloc( sz );
	if( tmp == NULL ) {
		ABORT( ALLOC_FAIL, "malloc failed: possibly out of memory" );
	}
	return tmp;
}

static inline void * alrealloc( void * ptr, const size_t sz )
{
	void * tmp = realloc( ptr, sz );
	if( tmp == NULL ) {
		ABORT( ALLOC_FAIL, "realloc failed: possibly out of memory" );
	}
	return tmp;
}

static inline void alfree( void * ptr )
{
	if( ptr != NULL ) free( ptr );
}

static inline void alfree_null( void ** ptr )
{
	if( * ptr != NULL ) free( ptr );
	* ptr = NULL;
}

static inline void realloc_on_full( void ** buffer, const int i, const int const_len, int * multiplier )
{
	if( i >= ( const_len * ( * multiplier ) ) - 1 ) {
		* multiplier *= 2;
		* buffer = alrealloc( * buffer, const_len * ( * multiplier ) );
	}
}

#endif // ALLOC_H
