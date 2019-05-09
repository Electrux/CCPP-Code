#ifndef VM_VARS_BASE_H
#define VM_VARS_BASE_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum
{
	VAR_STR,
	VAR_FLT,
	VAR_INT,
	VAR_BOOL,
	VAR_VEC,
	VAR_BLOCK,
	VAR_FUNC,
	VAR_NONE,
	VAR_EXCEPT,

	VAR_LAST_,
} VarType;

extern const char * VarTypeStrs[ VAR_LAST_ ];

typedef struct
{
	VarType type;
	size_t ref_count;
	void * data;
} var_t;

inline void var_inc_ref( var_t * var )
{
	++var->ref_count;
}

bool var_dec_ref( var_t ** var );

#endif // VM_VARS_BASE_H