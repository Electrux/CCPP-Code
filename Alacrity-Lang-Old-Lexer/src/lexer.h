#ifndef LEXER_H
#define LEXER_H

#include "core.h"
#include "vec.h"

typedef enum
{
	TOK_NUM,
	TOK_BIN,
	TOK_OCT,
	TOK_HEX,
	TOK_FLT,

	TOK_STR,
	TOK_IDEN,

	//Keywords
	TOK_STRUCT,
	TOK_RETURN,
	TOK_CONTINUE,
	TOK_BREAK,
	TOK_EXTERN,

	// Operators
	TOK_ASSN,
	// Arithmetic
	TOK_ADD,
	TOK_SUB,
	TOK_MUL,
	TOK_DIV,
	TOK_MOD,
	TOK_ADD_ASSN,
	TOK_SUB_ASSN,
	TOK_MUL_ASSN,
	TOK_DIV_ASSN,
	TOK_MOD_ASSN,
	TOK_INC, // ++
	TOK_DEC, // --
	TOK_POW, // **
	// Logic
	TOK_AND,
	TOK_OR,
	TOK_NOT,
	TOK_EQ,
	TOK_LT,
	TOK_GT,
	TOK_LE,
	TOK_GE,
	TOK_NE,
	// Bitwise
	TOK_BAND,
	TOK_BOR,
	TOK_BNOT,
	TOK_BXOR,
	TOK_BAND_ASSN,
	TOK_BOR_ASSN,
	TOK_BNOT_ASSN,
	TOK_BXOR_ASSN,
	// Conditional ( ? )
	TOK_QUEST,
	// Others
	TOK_LSHIFT,
	TOK_RSHIFT,
	TOK_LSHIFT_ASSN,
	TOK_RSHIFT_ASSN,

	// Separators
	TOK_SPC,
	TOK_TAB,
	TOK_NEWL,
	TOK_DOT,
	TOK_TWODOTS, // .. (range)
	TOK_COMMA,
	TOK_COLON,
	TOK_SEMICOL,
	// Separating multiple statements on single line
	TOK_DOLLAR, // $
	TOK_TWODOLLAR, // $$
	TOK_AT, // @ - treat next string as var, get its val (num), use it instead of var
	// For loops, map keys
	TOK_LARROW, // <-
	TOK_RARROW, // ->
	// Parenthesis, Braces, Brackets
	TOK_LPAREN,
	TOK_RPAREN,
	TOK_LBRACE,
	TOK_RBRACE,
	TOK_LBRACK,
	TOK_RBRACK,

	__LAST,
} TokType;

extern const char * TokStrs[ __LAST ];

typedef struct {
	int line;
	int col;
	TokType type;
	bool _heap_alloc;
	char * data;
} token_t;

void token_del_func( const void * data );

status_t tokenize( const vec_t * lines );

#endif // LEXER_H
