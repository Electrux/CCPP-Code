#include <iostream>
#include <fstream>
#include <string>


const int BITS = 7;

std::string GetBinary(char ch);

static int spaces = 0;

int main(int argc, char **argv)
{
	std::string line,
				bin;

	std::string filename = "Main.cpp";

	std::fstream file;

	file.open(filename, std::ios::in);

	while (std::getline(file, line))
	{
		for (auto ch : line)
		{
			bin += GetBinary(ch);
			//bin += ' ';
			//spaces++;
		}

		if (file.eof()) break;

		bin += GetBinary('\r');
		//bin += " ";
		bin += GetBinary('\n');
		//bin += " ";
		//spaces += 2;
	}

	file.close();

	//Get the number of characters (bytes) by first removing total spaces from size, and then dividing by the number of bits used to represent each character.
	std::cout << bin << "\n\nSize: " << ((bin.size() - spaces) / BITS) << "\n";

	std::system("pause");

	return 0;
}

std::string GetBinary(char ch)
{

	std::string bin;

	int rem;

	int bits = 0;

	while (ch > 0)
	{
		rem = ch % 2;

		ch /= 2;

		bin += std::to_string(rem);
		
		++bits;
	}

	while (bits < BITS)
	{
		bin += std::to_string(0);
		++bits;
	}

	std::reverse(bin.begin(), bin.end());

	return bin;
}
