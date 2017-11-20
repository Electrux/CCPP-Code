#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include "INI_Parser.hpp"


int main()
{
	std::system("cls");

	Electrux::INI_Parser ini;
	/*
	ini.SetData("Yo", "OneS", "One");
	ini.SetData("Yo", "OneI", 1);
	ini.SetData("Yo", "OneF", 1.0f);

	ini.SaveFile("Test.ini");
	*/

	ini.ParseFile("UserOptions.ini");

	ini.DisplayAll();

	//ini.SetData("Yo", "OneS", "Two"); //Modifies already existing data.

	//ini.DisplayAll();

	std::system("pause");
	return 0;
}