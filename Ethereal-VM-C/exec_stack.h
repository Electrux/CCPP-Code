#ifndef VM_EXEC_STACK_H
#define VM_EXEC_STACK_H

#include <stdbool.h>

#include "vec.h"
#include "vars/base.h"

inline void exec_stack_push_back( vec_t * vec, var_t * val )
{
	vec_add( vec, & val );
	var_inc_ref( val );
}

inline var_t * back( vec_t * vec )
{
	return * ( var_t ** )vec_get_data( vec, vec_count( vec ) - 1 );
}

inline void exec_stack_pop_back( vec_t * vec )
{
	var_t ** data = ( var_t ** )vec_get_data( vec, vec_count( vec ) - 1 );
	var_dec_ref( data );
	vec_pop_back( vec );
}

inline int exec_stack_size( vec_t * vec )
{
	return vec_count( vec );
}

inline bool exec_stack_empty( vec_t * vec )
{
	return vec_count( vec ) == 0;
}

void exec_stack_del_func( const void * data );

#endif // VM_EXEC_STACK_H