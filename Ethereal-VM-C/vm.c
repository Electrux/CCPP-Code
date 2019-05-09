#include <stdio.h>

#include "dylib.h"
#include "vars/base.h"
#include "exec_stack.h"
#include "vm.h"

int run( vec_t * instructions )
{
	int res = VM_OK;
	dy_init();
	// vector< var_t * >
	vec_t * exec_stack = vec_create( sizeof( void * ), exec_stack_del_func );

	//var_t * res_var = run_internal( )

end:
	vec_destroy( & exec_stack );
	dy_deinit();
	return res;
}