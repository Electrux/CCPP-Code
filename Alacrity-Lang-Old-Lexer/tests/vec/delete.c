/*
  Copyright (c) 2018, Electrux
  All rights reserved.
  Using the BSD 3-Clause license for the project,
  main LICENSE file resides in project's root directory.

  Please read that file and understand the license terms
  before using or altering the project.
*/

#include <stdio.h>

#include "src/vec.h"

#ifndef TEST_DEBUG
#define OUT_LOC stdout
#else
#define OUT_LOC stderr
#endif

int main()
{
	vec_t * strs = vec_create( -1, NULL );
	const char * test = "Hello world";
	for( int i = 0; i < 10; ++i ) {
		vec_add( strs, test );
	}

	fprintf( OUT_LOC, "Entered data, count = %d\n", vec_count( strs ) );

	fprintf( OUT_LOC, "Deleting at 7th position\n" );
	vec_del_at( strs, 8 );

	fprintf( OUT_LOC, "=> New size = %d\n", vec_count( strs ) );

	vec_destroy( & strs );
	return 0;
}
