%{
#include "parser.tab.h"

extern int yylex();
int line_num = 1;
%}
%option noyywrap
%%

\n			{ ++line_num; return TOK_NEWL; }
[ \t]			;
[0-9]+			{ yylval.sval = strdup( yytext ); return TOK_NUM; }
"0b"[0-1]+		{ yylval.sval = strdup( yytext ); return TOK_BIN; }
"0o"[0-7]+		{ yylval.sval = strdup( yytext ); return TOK_OCT; }
"0x"[0-9a-fA-F]+	{ yylval.sval = strdup( yytext ); return TOK_HEX; }
[0-9]+\.[0-9]+		{ yylval.sval = strdup( yytext ); return TOK_FLT; }

"(.*?)"			{ yylval.sval = strdup( yytext ); return TOK_STR; }

"struct"		{ return TOK_STRUCT; }
"return"		{ return TOK_RETURN; }
"continue"		{ return TOK_CONTINUE; }
"break"			{ return TOK_BREAK; }
"extern"		{ return TOK_EXTERN; }
[_a-zA-Z0-9]+		{ yylval.sval = strdup( yytext ); return TOK_IDEN; }


"="			{ return TOK_ASSN; }

"+"			{ return TOK_ADD; }
"-"			{ return TOK_SUB; }
"*"			{ return TOK_MUL; }
"/"			{ return TOK_DIV; }
"%"			{ return TOK_MOD; }
"+="			{ return TOK_ADD_ASSN; }
"-="			{ return TOK_SUB_ASSN; }
"*="			{ return TOK_MUL_ASSN; }
"/="			{ return TOK_DIV_ASSN; }
"%="			{ return TOK_MOD_ASSN; }
"++"			{ return TOK_INC; } // ++
"--"			{ return TOK_DEC; } // --
"**"			{ return TOK_POW; } // **

"&&"			{ return TOK_AND; }
"||"			{ return TOK_OR; }
"!"			{ return TOK_NOT; }
"=="			{ return TOK_EQ; }
"<"			{ return TOK_LT; }
">"			{ return TOK_GT; }
"<="			{ return TOK_LE; }
">="			{ return TOK_GE; }
"!="			{ return TOK_NE; }

"&"			{ return TOK_BAND; }
"|"			{ return TOK_BOR; }
"~"			{ return TOK_BNOT; }
"^"			{ return TOK_BXOR; }
"&="			{ return TOK_BAND_ASSN; }
"|="			{ return TOK_BOR_ASSN; }
"~="			{ return TOK_BNOT_ASSN; }
"^="			{ return TOK_BXOR_ASSN; }

"?"			{ return TOK_QUEST; }

"<<"			{ return TOK_LSHIFT; }
">>"			{ return TOK_RSHIFT; }
"<<="			{ return TOK_LSHIFT_ASSN; }
">>="			{ return TOK_RSHIFT_ASSN; }


"."			{ return TOK_DOT; }
".."			{ return TOK_TWODOTS; } // .. (range)
","			{ return TOK_COMMA; }
":"			{ return TOK_COLON; }
";"			{ return TOK_SEMICOL; }

"$"			{ return TOK_DOLLAR; } // $
"$$"			{ return TOK_TWODOLLAR; } // $$
"@"			{ return TOK_AT; } // @ - treat next string as var, get its val (num), use it instead of var

"<-"			{ return TOK_LARROW; } // <-
"->"			{ return TOK_RARROW; } // ->

"("			{ return TOK_LPAREN; }
")"			{ return TOK_RPAREN; }
"{"			{ return TOK_LBRACE; }
"}"			{ return TOK_RBRACE; }
"["			{ return TOK_LBRACK; }
"]"			{ return TOK_RBRACK; }
.			{ printf( "Invalid lex symbol: %s\n", yytext ); exit( -1 ); }

%%