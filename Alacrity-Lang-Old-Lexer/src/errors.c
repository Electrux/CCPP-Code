#include "errors.h"

const char * strerr( Errors code )
{
	switch( code ) {
	case ALLOC_FAIL:
		return "memory allocation failed";
	case LEX_FAIL:
		return "lexical analyzer failed";
	case PARSE_FAIL:
		return "parser failed";
	case FAIL: // fall through
	default:
		return "unknown error";
	}
}
