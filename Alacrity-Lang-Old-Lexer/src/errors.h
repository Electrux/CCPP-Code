#ifndef ERRORS_H
#define ERRORS_H

typedef enum {
	OK,
	FAIL,

	FILE_IO_ERR,

	ALLOC_FAIL,
	LEX_FAIL,
	PARSE_FAIL,
} Errors;

const char * strerr( Errors code );

#endif // ERRORS_H
