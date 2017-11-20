#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include "../include/INI_Parser.hpp"


int main()
{
	Electrux::INI_Parser ip;
	
	ip.LoadFromFile( "test.ini" );
	ip.DisplayAll();
	std::cout << "\n";
	
	ip.CreateSection( "test" );
	ip.SetDataString( "test", "test2", "test3" );
	ip.DisplayLastStatusString();
	
	ip.SaveToFile( "test.ini" );
	
	std::cout << "\n";
	return 0;
}