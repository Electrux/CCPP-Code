#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/vectors.h"

int main()
{
	struct StrVector * myvec = create_str_vector();

	vector_str_push( myvec, "hello" );
	vector_str_push( myvec, "second" );

	vector_str_print( myvec );
	printf( "\n" );
	vector_str_pop( myvec, NULL, 0 );
	vector_str_print( myvec );
	printf( "\n" );

	delete_str_vector( myvec );

	struct IntVector * myvec2 = create_int_vector();

	vector_int_push( myvec2, 5 );
	vector_int_push( myvec2, 6 );

	vector_int_print( myvec2 );
	printf( "\n" );

	vector_int_pop( myvec2, NULL );
	vector_int_pop( myvec2, NULL );

	vector_int_print( myvec2 );
	printf( "\n" );

	delete_int_vector( myvec2 );

	return 0;
}
