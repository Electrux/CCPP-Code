#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "../include/SpellingTree.hpp"


int main()
{
	SpellTree checker;

	/*
	std::string word = "Hello";
	
	checker.AddWord( word );

	for( auto ch : word )
		std::cout << std::boolalpha << checker.CheckWhileAddingCharacter( ch )
			  << "\n";

	std::cout << checker.CheckWhileErasingCharacter() << "\n";
	std::cout << checker.CheckWhileAddingCharacter( 'o' ) << "\n";

	std::cout << std::boolalpha << "\n\nWord Exists ( "
		  << word << " )"
		  << " : " << checker.CheckWord( word )
		  << "\n";
	*//*!< Testing 1 */

	std::fstream file;

	file.open( "words.txt", std::ios::in );

	std::string word;

	while( std::getline( file, word ) )
		checker.AddWord( word );

	file.close();

	SpellTree::ReturnValue ret;
	
	for( auto ch : std::string( "hellopapsd" ) ) {

		ret = checker.CheckWhileAddingCharacter( ch );

		std::cout << std::boolalpha
			  << "Checking for : "
			  << ret.checkstr << "\t"
			  << ", Result : " << ret.result
			  << "\n";
	}
	
	return 0;
}
