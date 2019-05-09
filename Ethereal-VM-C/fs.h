#ifndef VM_FS_H
#define VM_FS_H

#include <stdbool.h>
#include <unistd.h>

inline bool fexists( const char * file_str )
{
	return access( file_str, F_OK ) != -1;
}

#endif // VM_FS_H