#ifndef AL_TYPES_H
#define AL_TYPES_H

#include "core.h"

static inline bool is_valid_num_char( const char c )
{
	return ( c >= '0' && c <= '9' ) || ( c >= 'a' && c <= 'f' ) || ( c >= 'A' && c <= 'F' )
		|| c == '.' || c == '-' || c == '+' || c == 'o' || c == 'O' || c == 'x' || c == 'X';
}

#endif // AL_TYPES_H
