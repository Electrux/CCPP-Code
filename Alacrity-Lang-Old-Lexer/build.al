project( "Alacrity-Frontend" ) {
	version( 0.1 )
	language( c, 11 )
	license( bsd3 )
	author( Electrux, "ElectruxRedsworth@gmail.com" )
}

builds.add_c_flags( "-march=native", "-O2", "-flto", "-fPIC", "-pedantic", "-Wall", "-Wextra", "-Wno-unused-parameter" )

if( "${OS}" == OS_LINUX ) {
	builds.add_c_flags( "-D_GNU_SOURCE" )
}

use_lib( pthread )
use_lib( dl )

builds( bin ) {
	sources( "src/(.*)\.c" )
	build( al, "src/main.c" )
}

# Vector tests
builds( test ) {
	add_c_inc_dirs( "-I." )
	sources( "src/vec.c" )
	build( vec_insert,	"tests/vec/insert.c" )
	build( vec_destroy,	"tests/vec/delete.c" )
	build( vec_get,		"tests/vec/get.c" )
	build( vec_count, 	"tests/vec/count.c" )
	build( vec_all, 	"tests/vec/all.c" )
	runtests()
}