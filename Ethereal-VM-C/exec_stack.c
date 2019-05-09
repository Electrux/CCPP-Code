#include "exec_stack.h"

void exec_stack_del_func( const void * data )
{
	var_dec_ref( ( var_t ** )data );
}