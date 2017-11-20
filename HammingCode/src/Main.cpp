#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include <vector>
#include <map>
#include "../include/Hamming.hpp"



int main()
{
	system("cls");

	std::string arr;
	StringWithParityCount paritystr;

	std::cout << "Enter the binary message: ";
	std::cin >> arr;
	
	paritystr = HammingCode::encode(arr);

	std::cout << "\nHamming Code: " << paritystr.arr << "\n\n";

	std::cout << "Receiver Side...\n\n";
	std::cout << HammingCode::decode(paritystr) << "\n\n";

	system("pause");
	return 0;
}

