project( "Ethereal Lang" ) {
	version( 0.1 )
	language( c, 11 )
	license( bsd3 )
	author( Electrux, "ElectruxRedsworth@gmail.com" )
}

builds.add_c_flags( "-march=native", "-O2", "-flto", "-fPIC", "-pedantic", "-Wall", "-Wextra", "-Wno-unused-parameter", "-D_DEFAULT_SOURCE" )

print( "Compiling src/parser.y ... " )
eval( "%{bison -d src/parser.y -b src/parser}" )
if( "${EXIT_STATUS}" == 0 ) {
	print( "{g}success{0}\n" )
} else {
	print( "{r}failed{0}\n" )
}

print( "Compiling src/lexer.l ... " )
eval( "%{flex -o src/lex.yy.c src/lexer.l}" )
if( "${EXIT_STATUS}" == 0 ) {
	print( "{g}success{0}\n" )
} else {
	print( "{r}failed{0}\n" )
}

builds( bin ) {
	sources( "src/lex.yy.c" )
	build( parser, "src/parser.tab.c" )
}