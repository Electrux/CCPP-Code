#include "base.h"

const char * VarTypeStrs[ VAR_LAST_ ] = {
	"VAR_STR",
	"VAR_FLT",
	"VAR_INT",
	"VAR_BOOL",
	"VAR_VEC",
	"VAR_BLOCK",
	"VAR_FUNC",
	"VAR_NONE",
	"VAR_EXCEPT",
};

bool var_dec_ref( var_t ** var )
{
	if( ( * var )->ref_count == 1 ) {
		free( ( * var )->data );
		free( ( * var ) );
		* var = NULL;
		return;
	}
	--( * var )->ref_count;
}
