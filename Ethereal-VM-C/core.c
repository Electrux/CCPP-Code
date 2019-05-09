#include <stdlib.h>

#include "core.h"

const char * InstructionCodeStrs[ _LAST ] = {
	"POP_STACK",		// arg: int -> how many elements to remove from stack
	"VAR_ADD_LAYER",	// arg: int -> how many layers to add
	"VAR_REM_LAYER",	// arg: int -> how many layers to remove

	"LOAD_CONST",		// arg: val -> the const to load
	"LOAD_VAR",		// arg: str -> the variable name to load in stack

	"STORE_NAME",		// arg: str -> the variable name in which to store value from stack
	"UNSTORE_NAME",		// arg: str -> the variable name to remove from memory

	"JUMP_ON_TRUE",		// arg: int -> index of the instructions vector to jump at
	"JUMP_ON_FALSE",	// arg: int -> index of the instructions vector to jump at
	"JUMP_NO_COND",		// arg: nil

	"LOAD_DYN_MOD",		// arg: str -> the module to load (location)

	"CALL_MOD_FUN",		// arg: int -> number of arguments after first value (func name) in stack
	"CALL_FUNC",		// arg: int -> number of arguments after first value (func name) in stack
	"FUNC_RETURN",		// arg: nil

	"BLOCK_TILL",		// arg: int -> index of the instructions vector with block instruction
	"ARGS_TILL",		// arg: int -> index of the instructions vector with last arg
	"BUILD_FUNC",		// arg: nil

	"BUILD_VECTOR",		// arg: int -> the number of elements to pick from the stack for building the vector
	"SUBSCR_LOAD",		// arg: nil
	"SUBSCR_STORE",		// arg: nil
};

const char * OperandTypeStrs[ _OPER_LAST ] = {
	"OPER_EMPTY",
	"OPER_STR",
	"OPER_FLT",
	"OPER_INT",
	"OPER_BOOL",
};

void ins_deleter( void * _ins )
{
	instruction_t * ins = _ins;
	if( ins->operand.manual_clear ) free( ins->operand.val );
	free( ins );
}

void get_prelude_modules( vec_t * vec )
{
	ins_add( vec, -1, -1, LOAD_DYN_MOD, OPER_STR, false, "io" );
	/*ins_add( vec, -1, -1, LOAD_DYN_MOD, OPER_STR, false, "int" );
	ins_add( vec, -1, -1, LOAD_DYN_MOD, OPER_STR, false, "bool" );
	ins_add( vec, -1, -1, LOAD_DYN_MOD, OPER_STR, false, "str" );
	ins_add( vec, -1, -1, LOAD_DYN_MOD, OPER_STR, false, "vec" );*/
}
