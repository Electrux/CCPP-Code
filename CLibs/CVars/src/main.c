#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/vars.h"

int main()
{
	struct Vars * vars = init_vars();

	var_add( vars, "hello", "hi" );
	var_add( vars, "kudos", "something" );

	vars_print( vars );
	printf( "\n" );

	var_del( vars, "kudos" );
	// to show that it won't crash
	var_del( vars, "adios" );
	var_del( vars, "hello" );
	// again, to show that empty list won't crash
	var_del( vars, "yo" );

	vars_print( vars );

	delete_vars( vars );

	return 0;
}
