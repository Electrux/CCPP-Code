#ifndef CORE_H
#define CORE_H

#include <stdio.h>

#include "errors.h"

#ifdef _GNU_SOURCE
#define ATTR_FALLTHROUGH __attribute__ ( ( fallthrough ) )
#else
#define ATTR_FALLTHROUGH
#endif

/* Max length of any string, 5 to allow 4 chars, 1 null terminator */
/* It will be grown by internal functions */
#define MAX_STR_LEN 5

typedef struct {
	int code;
	void * data;
} status_t;

typedef enum {
	false,
	true,
} bool;

#define ABORT( err_code, err_msg ) \
fprintf( stdout, "error (%s) in %s(%d): " err_msg, strerr( err_code ), __FILE__, __LINE__ ); \
exit( err_code )

#endif // CORE_H
