%{
#include <stdio.h>
#include <stdlib.h>

// Declare stuff from Flex that Bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE * yyin;

void yyerror( const char * s );
%}

%union {
	// type value for when storing in string is not required
	int tval;
	char * sval;
};

%token <sval> TOK_NUM TOK_BIN TOK_OCT TOK_HEX TOK_FLT TOK_STR TOK_IDEN

//Keywords
%token <tval> TOK_STRUCT TOK_RETURN TOK_CONTINUE TOK_BREAK TOK_EXTERN

// Operators
%token <tval> TOK_ASSN
// Arithmetic
%token <tval> TOK_ADD TOK_SUB TOK_MUL TOK_DIV TOK_MOD
%token <tval> TOK_ADD_ASSN TOK_SUB_ASSN TOK_MUL_ASSN TOK_DIV_ASSN TOK_MOD_ASSN
// ++, --, **
%token <tval> TOK_INC TOK_DEC TOK_POW
// Logic
%token <tval> TOK_AND TOK_OR TOK_NOT TOK_EQ TOK_LT TOK_GT TOK_LE TOK_GE TOK_NE
// Bitwise
%token <tval> TOK_BAND TOK_BOR TOK_BNOT TOK_BXOR TOK_BAND_ASSN TOK_BOR_ASSN TOK_BNOT_ASSN TOK_BXOR_ASSN
// Conditional ( ? )
%token <tval> TOK_QUEST
// Others
%token <tval> TOK_LSHIFT TOK_RSHIFT TOK_LSHIFT_ASSN TOK_RSHIFT_ASSN

// Separators
%token <tval> TOK_SPC TOK_TAB TOK_NEWL TOK_DOT TOK_TWODOTS TOK_COMMA TOK_COLON TOK_SEMICOL
// Separating multiple statements on single line
// @ - treat next string as var, get its val (num), use it instead of var
%token <tval> TOK_DOLLAR TOK_TWODOLLAR TOK_AT
// For loops map keys
%token <tval> TOK_LARROW TOK_RARROW
// Parenthesis Braces Brackets
%token <tval> TOK_LPAREN TOK_RPAREN TOK_LBRACE TOK_RBRACE TOK_LBRACK TOK_RBRACK

%%
BASE
	: TOK_STR
	| TOK_IDEN
	| TOK_NUM
	| TOK_BIN
	| TOK_OCT
	| TOK_HEX
	| '(' EXPR ')'
	;

EXPR
	: BASE
%%

int main( int argc, char ** argv )
{
	if( argc < 2 ) {
		printf( "Usage: %s <source file>\n", argv[ 0 ] );
		return 1;
	}
	FILE * src_file = fopen( argv[ 1 ], "r" );
	if( !src_file ) {
		printf( "File: %s does not exist!\n", argv[ 1 ] );
		return 1;
	}

	yyin = src_file;
	yyparse();
	fclose( src_file );
	return 0;
}

void yyerror( const char * s )
{
	printf( "Parser error: %s\n", s );
	exit( -1 );
}