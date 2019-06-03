#include <iostream>
#include <algorithm>

#include "../src/CmdParams.hpp"

int main()
{
	CmdParams params;
	params.Parse( { "hello", "hi", "-lol", "--yo=word", "--sup", "also_word" } );
#ifdef __DEBUG
	params.DispAll();
#endif
	assert( params.Args().size() == 3 );
	assert( params.Opts().size() == 4 );
	assert( std::find( params.Args().begin(), params.Args().end(), "wowzers" ) == params.Args().end() );
	assert( params.Opt( "l" ) == "_" );
	assert( params.Opt( "o" ) == "_" );
	assert( params.Opt( "na" ) == "" );
	assert( params.Opt( "l" ) == "_" );
	assert( params.Opt( "sup" ) == "_" );
	assert( params.Opt( "yo" ) == "word" );
	return 0;
}