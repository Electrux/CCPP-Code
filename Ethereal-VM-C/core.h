#ifndef VM_CORE_H
#define VM_CORE_H

#include <stdbool.h>

#include "ret_codes.h"
#include "vec.h"

typedef enum
{
	POP_STACK,		// arg: int -> how many elements to remove from stack
	VAR_ADD_LAYER,		// arg: int -> how many layers to add
	VAR_REM_LAYER,		// arg: int -> how many layers to remove

	LOAD_CONST,		// arg: val -> the const to load
	LOAD_VAR,		// arg: str -> the variable name to load in stack

	STORE_NAME,		// arg: str -> the variable name in which to store value from stack
	UNSTORE_NAME,		// arg: str -> the variable name to remove from memory

	JUMP_ON_TRUE,		// arg: int -> index of the instructions vector to jump at
	JUMP_ON_FALSE,		// arg: int -> index of the instructions vector to jump at
	JUMP_NO_COND,		// arg: nil

	LOAD_DYN_MOD,		// arg: str -> the module to load (location)

	CALL_MOD_FUN,		// arg: int -> number of arguments after first value (func name) in stack
	CALL_FUNC,		// arg: int -> number of arguments after first value (func name) in stack
	FUNC_RETURN,		// arg: nil

	BLOCK_TILL,		// arg: int -> index of the instructions vector with block instruction
	ARGS_TILL,		// arg: int -> index of the instructions vector with last arg
	BUILD_FUNC,		// arg: nil

	BUILD_VECTOR,		// arg: int -> the number of elements to pick from the stack for building the vector
	SUBSCR_LOAD,		// arg: nil
	SUBSCR_STORE,		// arg: nil

	_LAST,
} InstructionCode;

extern const char * InstructionCodeStrs[ _LAST ];

typedef enum
{
	OPER_EMPTY,
	OPER_STR,
	OPER_FLT,
	OPER_INT,
	OPER_BOOL,

	_OPER_LAST,
} OperandType;

extern const char * OperandTypeStrs[ _OPER_LAST ];

typedef struct
{
	int type;
	bool manual_clear;
	const char * val;
} operand_t;

typedef struct
{
	int line;
	int col;
	InstructionCode opcode;
	operand_t operand;
} instruction_t;

void ins_deleter( void * _ins );

// vector< Instruction >
void get_prelude_modules( vec_t * vec );

inline void ins_add( vec_t * vec, const int line, const int col, const InstructionCode ins,
		const OperandType op_type, const bool manual_clear, const char * op_data )
{
	vec_add( vec, & ( instruction_t ){ line, col, ins, ( operand_t ){ op_type, manual_clear, op_data } } );
}

#endif // VM_CORE_H