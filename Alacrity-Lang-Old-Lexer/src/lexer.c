#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "core.h"
#include "altypes.h"
#include "alloc.h"
#include "vec.h"
#include "lexer.h"

/* Some helpful macros across the lexer.c file */
#define PREV( input ) ( i <= 0 ? 0 : input[ i - 1 ] )
#define PREV_PTR( input ) ( * i <= 0 ? 0 : input[ ( * i ) - 1 ] )
#define CURR( input ) input[ i ]
#define CURR_PTR( input ) input[ * i ]
#define NEXT( input ) ( ( i < input##_len - 1 ) ? input[ i + 1 ] : 0 )
#define NEXT_PTR( input ) ( ( * i < input##_len - 1 ) ? input[ ( * i ) + 1 ] : 0 )
#define NEXT_IS( input, is ) ( i < input##_len - 1 && input[ i + 1 ] == is )
#define NEXT_PTR_IS( input, is ) ( * i < input##_len - 1 && input[ ( * i ) + 1 ] == is )
#define INC_PTR( i ) ++( * i )
// for get_operator() exclusively
#define SET_OP_TYPE_BRK( tok_val ) op_type = tok_val; break

const char * TokStrs[ __LAST ] = {
	"NUM",
	"BIN",
	"OCT",
	"HEX",
	"FLT",

	"STR",
	"IDEN",

	//Keywords
	"STRUCT",
	"RETURN",
	"CONTINUE",
	"BREAK",
	"EXTERN",

	// Operators
	"ASSN",
	// Arithmetic
	"ADD",
	"SUB",
	"MUL",
	"DIV",
	"MOD",
	"ADD_ASSN",
	"SUB_ASSN",
	"MUL_ASSN",
	"DIV_ASSN",
	"MOD_ASSN",
	"INC", // ++
	"DEC", // --
	"POW", // **
	// Logic
	"AND",
	"OR",
	"NOT",
	"EQ",
	"LT",
	"GT",
	"LE",
	"GE",
	"NE",
	// Bitwise
	"BAND",
	"BOR",
	"BNOT",
	"BXOR",
	"BAND_ASSN",
	"BOR_ASSN",
	"BNOT_ASSN",
	"BXOR_ASSN",
	// Conditional ( ? )
	"QUEST",
	// Others
	"LSHIFT",
	"RSHIFT",
	"LSHIFT_ASSN",
	"RSHIFT_ASSN",

	// Separators
	"SPC",
	"TAB",
	"NEWL",
	"DOT",
	"TWODOTS", // .. (range)
	"COMMA",
	"COLON",
	"SEMICOL",
	// Separating multiple statements on single line
	"DOLLAR", // $
	"TWODOLLAR", // $$
	"AT", // @ - treat next string as var, get its val (num), use it instead of var
	// For loops, map keys
	"LARROW", // <-
	"RARROW", // ->
	// Parenthesis, Braces, Brackets
	"LPAREN",
	"RPAREN",
	"LBRACE",
	"RBRACE",
	"LBRACK",
	"RBRACK",
};

void token_del_func( const void * data )
{
	const token_t * tok = data;
	if( tok->_heap_alloc ) free( tok->data );
}

status_t _tokenize_line( const char * line, const int line_num, const int line_len, vec_t * toks );
char * get_name( const char * input, int * i, const int input_len );
int classify_str( const char * str );
status_t get_num( const char * input, const int line_num, int * i, const int input_len, int * num_type );
char * get_const_str( const char * input, const int line_num, int  * i, const int input_len );
int get_operator( const char * input, const int line_num, int  * i, const int input_len );

status_t tokenize( const vec_t * lines )
{
	int line_count = vec_count( lines );
	vec_t * toks = vec_create( sizeof( token_t ), token_del_func );

	int err = OK;

	bool add_ending_double_dollar = true;

	for( int i = 0; i < line_count; ++i ) {
		const char * line = vec_get_data( lines, i );
		const int line_len = strlen( line );
		if( line_len < 1 || line[ 0 ] == '\n' ) continue;
		status_t res = _tokenize_line( line, i + 1, line_len, toks );
		if( res.code != OK ) { err = res.code; goto fail; }
		// add line break character ($) for each line of code
		if( line[ line_len - 2 ] == '$' ) {
			add_ending_double_dollar = false;
			continue;
		}
		token_t tok = { -1, -1, TOK_DOLLAR, false, NULL };
		vec_add( toks, & tok );
	}

	// add $$ at the end of code for ease
	if( vec_count( toks ) > 0 && add_ending_double_dollar ) {
		token_t tok = { -1, -1, TOK_TWODOLLAR, false, NULL };
		vec_add( toks, & tok );
	}

	return ( status_t ){ OK, toks };
fail:
	vec_destroy( & toks );
	return ( status_t ){ err, NULL };
}

status_t _tokenize_line( const char * line, const int line_num, const int line_len, vec_t * toks )
{
	int i = 0;
	int err = OK;

	static bool comment_block = false;

	while( i < line_len ) {
		if( isspace( CURR( line ) ) ){ ++i; continue; }

		if( CURR( line ) == '*' && NEXT_IS( line, '/' ) ) {
			if( !comment_block ) {
				fprintf( stdout,
					"lex error on line %d(%d): encountered multi line comment terminator '*/' "
					"in non commented block\n",
					line_num, i + 1 );
				err = LEX_FAIL;
				break;
			}
			i += 2;
			comment_block = false;
			continue;
		}

		if( comment_block ) { ++i; continue; }

		if( CURR( line ) == '/' && NEXT_IS( line, '*' ) ) {
			i += 2;
			comment_block = true;
			continue;
		}

		if( CURR( line ) == '#' ) break;

		// strings
		if( isalpha( CURR( line ) ) || CURR( line ) == '_' ) {
			char * str = get_name( line, & i, line_len );
			// check if string is a keyword
			int kw_or_iden = classify_str( str );
			token_t tok = { line_num, i + 1, kw_or_iden, true, str };
			vec_add( toks, & tok );
			continue;
		}

		// numbers
		if( isdigit( CURR( line ) ) ) {
			int num_type = TOK_NUM;
			status_t res = get_num( line, line_num, & i, line_len, & num_type );
			if( res.code != OK ) {
				err = res.code;
				break;
			}
			token_t tok = { line_num, i + 1, num_type, true, res.data };
			vec_add( toks, & tok );
			continue;
		}

		// const strings
		if( CURR( line ) == '\"' || CURR( line ) == '\'' ) {
			char * str = get_const_str( line, line_num, & i, line_len );
			if( str == NULL ) {
				err = LEX_FAIL;
				break;
			}
			token_t tok = { line_num, i + 1, TOK_STR, true, str };
			vec_add( toks, & tok );
			continue;
		}

		// operators
		int op_type = get_operator( line, line_num, & i, line_len );
		if( op_type < 0 ) {
			err = LEX_FAIL;
			break;
		}
		token_t tok = { line_num, i + 1, op_type, false, NULL };
		vec_add( toks, & tok );
	}

	return ( status_t ){ err, NULL };
}

char * get_name( const char * input, int * i, const int input_len )
{
	char * buf = alalloc( sizeof( char ) * MAX_STR_LEN );
	int buf_inc_times = 1;
	int j = 0;
	buf[ j++ ] = input[ ( * i )++ ];
	while( * i < input_len ) {
		if( !isalnum( CURR_PTR( input ) ) && CURR_PTR( input ) != '_' ) break;
		buf[ j++ ] = input[ ( * i )++ ];
		realloc_on_full( ( void ** ) & buf, j, MAX_STR_LEN, & buf_inc_times );
	}
	buf[ j ] = '\0';
	return buf;
}

int classify_str( const char * str )
{
	if( strcmp( str, "struct" ) == 0 ) return TOK_STRUCT;
	else if( strcmp( str, "return" ) == 0 ) return TOK_RETURN;
	else if( strcmp( str, "continue" ) == 0 ) return TOK_CONTINUE;
	else if( strcmp( str, "break" ) == 0 ) return TOK_BREAK;
	else if( strcmp( str, "extern" ) == 0 ) return TOK_EXTERN;

	return TOK_IDEN;
}

status_t get_num( const char * input, const int line_num, int * i, const int input_len, int * num_type )
{
	char * buf = alalloc( sizeof( char ) * MAX_STR_LEN );
	int buf_inc_times = 1;
	int j = 0;
	int first_digit_at = * i;

	bool success = true;
	int dot_encountered = -1;

	while( * i < input_len && is_valid_num_char( CURR_PTR( input ) ) ) {
		const char c = CURR_PTR( input );
		switch( c ) {
		case '0':
		case '1':
			break;
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if( * num_type == TOK_BIN ) {
				fprintf( stdout,
					"lex error on line %d(%d): encountered non bin character '%c' "
					"when the number being retrieved (from column %d) was in bin mode\n",
					line_num, ( * i ) + 1, CURR_PTR( input ), first_digit_at + 1 );
				success = false;
			}
			if( * num_type == TOK_OCT ) {
				fprintf( stdout,
					"lex error on line %d(%d): encountered non oct character '%c' "
					"when the number being retrieved (from column %d) was in oct mode\n",
					line_num, ( * i ) + 1, CURR_PTR( input ), first_digit_at + 1 );
				success = false;
			}
			break;
		case 'o':
		case 'O':
			if( * i == first_digit_at + 1 ) {
				* num_type = TOK_OCT;
			} else {
				fprintf( stdout,
					"lex error on line %d(%d): encountered octal modifier character '%c' "
					"on other than second position while retrieving a number (from column %d)\n",
					line_num, ( * i ) + 1, CURR_PTR( input ), first_digit_at + 1 );
				success = false;
			}
			break;
		case 'x':
		case 'X':
			if( * i == first_digit_at + 1 ) {
				* num_type = TOK_HEX;
			} else {
				fprintf( stdout,
					"lex error on line %d(%d): encountered hex modifier character '%c' "
					"on other than second position while retrieving a number (from column %d)\n",
					line_num, ( * i ) + 1, CURR_PTR( input ), first_digit_at + 1 );
				success = false;
			}
			break;
		case 'A':
		case 'a':
		case 'B':
		case 'b':
			if( * i == first_digit_at + 1 ) {
				* num_type = TOK_BIN;
				break;
			}
			ATTR_FALLTHROUGH;
		case 'C':
		case 'c':
		case 'D':
		case 'd':
		case 'E':
		case 'e':
		case 'F':
		case 'f':
			if( * num_type != TOK_HEX ) {
				fprintf( stdout,
					"lex error on line %d(%d): encountered hex/num modifier character '%c' "
					"when the number being retrieved (from column %d) was not in hex mode\n",
					line_num, ( * i ) + 1, CURR_PTR( input ), first_digit_at + 1 );
				success = false;
			}
			break;
		case '.':
			if( dot_encountered == -1 ) {
				dot_encountered = * i;
				* num_type = TOK_FLT;
			} else {
				fprintf( stdout,
					"lex error on line %d(%d): encountered dot(.) character "
					"when the number being retrieved (from column %d) already had one at column %d\n",
					line_num, ( * i ) + 1, first_digit_at + 1, dot_encountered + 1 );
				success = false;
			}
			break;
		default:
			fprintf( stdout,
				"lex error on line %d(%d): encountered invalid character '%c' "
				"while retrieving a number (from column %d)\n",
				line_num, ( * i ) + 1, CURR_PTR( input ), first_digit_at + 1 );
			success = false;
			
		}
		if( success == false ) {
			alfree( buf );
			return ( status_t ){ LEX_FAIL, NULL };
		}
		buf[ j++ ] = c; INC_PTR( i );
		realloc_on_full( ( void ** ) & buf, j, MAX_STR_LEN, & buf_inc_times );
	}
	buf[ j ] = '\0';
	return ( status_t ){ OK, buf };
}

char * get_const_str( const char * input, const int line_num, int  * i, const int input_len )
{
	char * buf = alalloc( sizeof( char ) * MAX_STR_LEN );
	int buf_inc_times = 1;
	int j = 0;
	const char quote_type = CURR_PTR( input );
	int starting_at = * i;
	// omit beginning quote
	INC_PTR( i );
	while( * i < input_len ) {
		if( CURR_PTR( input ) == quote_type && PREV_PTR( input ) != '\\' ) break;

		buf[ j++ ] = input[ ( * i )++ ];
		realloc_on_full( ( void ** ) & buf, j, MAX_STR_LEN, & buf_inc_times );
	}
	if( CURR_PTR( input ) != quote_type ) {
		fprintf( stdout,
			"lex error on line %d(%d): no matching quote for '%c' (column %d) found\n",
			line_num, ( * i ) + 1, quote_type, starting_at + 1 );
		alfree( buf );
		return NULL;
	}
	// omit ending quote
	INC_PTR( i );
	buf[ j ] = '\0';
	return buf;
}

int get_operator( const char * input, const int line_num, int  * i, const int input_len )
{
	int op_type = -1;
	switch( CURR_PTR( input ) ) {
	case '+':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '+' ) || NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				if( CURR_PTR( input ) == '+' ) op_type = TOK_INC;
				else if( CURR_PTR( input ) == '=' ) op_type = TOK_ADD_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK( TOK_ADD );
	case '-':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '-' ) || NEXT_PTR_IS( input, '=' ) || NEXT_PTR_IS( input, '>' ) ) {
				INC_PTR( i );
				if( CURR_PTR( input ) == '-' ) op_type = TOK_DEC;
				else if( CURR_PTR( input ) == '=' ) op_type = TOK_SUB_ASSN;
				else if( CURR_PTR( input ) == '>' ) op_type = TOK_RARROW;
				break;
			}
		}
		SET_OP_TYPE_BRK( TOK_SUB );
	case '*':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '*' ) || NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				if( CURR_PTR( input ) == '*' ) op_type = TOK_POW;
				else if( CURR_PTR( input ) == '=' ) op_type = TOK_MUL_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK( TOK_MUL );
	case '/':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_DIV_ASSN );
			}
		}
		SET_OP_TYPE_BRK( TOK_DIV );
	case '%':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_MOD_ASSN );
			}
		}
		SET_OP_TYPE_BRK( TOK_MOD );
	case '&':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '&' ) || NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				if( CURR_PTR( input ) == '&' ) op_type = TOK_AND;
				else if( CURR_PTR( input ) == '=' ) op_type = TOK_BAND_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK( TOK_BAND );
	case '|':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '|' ) || NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				if( CURR_PTR( input ) == '|' ) op_type = TOK_OR;
				else if( CURR_PTR( input ) == '=' ) op_type = TOK_BOR_ASSN;
				break;
			}
		}
		SET_OP_TYPE_BRK( TOK_BOR );
	case '~':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_BNOT_ASSN );
			}
		}
		SET_OP_TYPE_BRK( TOK_BNOT );
	case '=':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_EQ );
			}
		}
		SET_OP_TYPE_BRK( TOK_ASSN );
	case '<':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) || NEXT_PTR_IS( input, '-' ) || NEXT_PTR_IS( input, '<' ) ) {
				INC_PTR( i );
				if( CURR_PTR( input ) == '=' ) op_type = TOK_LE;
				else if( CURR_PTR( input ) ) op_type = TOK_LARROW;
				else if( CURR_PTR( input ) == '<' ) {
					if( * i < input_len - 1 ) {
						if( NEXT_PTR_IS( input, '=' ) ) {
							INC_PTR( i );
							SET_OP_TYPE_BRK( TOK_LSHIFT_ASSN );
						}
					}
					op_type = TOK_LSHIFT;
				}
				break;
			}
		}
		SET_OP_TYPE_BRK( TOK_LT );
	case '>':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) || NEXT_PTR_IS( input, '>' ) ) {
				INC_PTR( i );
				if( CURR_PTR( input ) == '=' ) op_type = TOK_GE;
				else if( CURR_PTR( input ) == '>' ) {
					if( * i < input_len - 1 ) {
						if( NEXT_PTR_IS( input, '=' ) ) {
							INC_PTR( i );
							SET_OP_TYPE_BRK( TOK_RSHIFT_ASSN );
						}
					}
					op_type = TOK_RSHIFT;
				}
				break;
			}
		}
		SET_OP_TYPE_BRK( TOK_GT );
	case '!':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_NE );
			}
		}
		SET_OP_TYPE_BRK( TOK_NOT );
	case '^':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '=' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_BXOR_ASSN );
			}
		}
		SET_OP_TYPE_BRK( TOK_BXOR );
	case '?':
		SET_OP_TYPE_BRK( TOK_QUEST );
	case ' ':
		SET_OP_TYPE_BRK( TOK_SPC );
	case '\t':
		SET_OP_TYPE_BRK( TOK_TAB );
	case '\n':
		SET_OP_TYPE_BRK( TOK_NEWL );
	case '.':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '.' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_TWODOTS );
			}
		}
		SET_OP_TYPE_BRK( TOK_DOT );
	case ',':
		SET_OP_TYPE_BRK( TOK_COMMA );
	case ':':
		SET_OP_TYPE_BRK( TOK_COLON );
	case ';':
		SET_OP_TYPE_BRK( TOK_SEMICOL );
	case '$':
		if( * i < input_len - 1 ) {
			if( NEXT_PTR_IS( input, '$' ) ) {
				INC_PTR( i );
				SET_OP_TYPE_BRK( TOK_TWODOLLAR );
			}
		}
		SET_OP_TYPE_BRK( TOK_DOLLAR );
	case '@':
		SET_OP_TYPE_BRK( TOK_AT );
	case '(':
		SET_OP_TYPE_BRK( TOK_LPAREN );
	case '[':
		SET_OP_TYPE_BRK( TOK_LBRACK );
	case '{':
		SET_OP_TYPE_BRK( TOK_LBRACE );
	case ')':
		SET_OP_TYPE_BRK( TOK_RPAREN );
	case ']':
		SET_OP_TYPE_BRK( TOK_RBRACK );
	case '}':
		SET_OP_TYPE_BRK( TOK_RBRACE );
	default:
		fprintf( stdout,
			"lex error on line %d(%d): unknown operator '%c' found\n",
			line_num, ( * i ) + 1, CURR_PTR( input ) );
		op_type = -1;
	}

	INC_PTR( i );
	return op_type;
}
