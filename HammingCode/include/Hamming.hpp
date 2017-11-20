#include <vector>
#include <map>
#include <cmath>
#include <string>

const char parity_char_str[] = "P",
parity_char = 'P';

struct StringWithParityCount
{
	int pbits;
	std::string arr;
};


class HammingCode
{
	static std::string getparityvalues(StringWithParityCount &paritystr);
	static std::map<int, std::vector<int>> getoneplaces(StringWithParityCount &paritystr);
	static std::string getbin(int num, int bits);
	static std::string getrevbin(int num, int bits);
	static int getnumfrombin(std::string &num);

public:

	static StringWithParityCount encode(std::string &arr);
	static std::string decode(StringWithParityCount paritystr);
};

StringWithParityCount HammingCode::encode(std::string &arr)
{
	int size_str, net = 0;;
	StringWithParityCount paritystr;

	paritystr.arr = arr;
	paritystr.pbits = 0;
	
	size_str = paritystr.arr.length();


	net = paritystr.pbits + size_str + 1;
	while (std::pow(2, paritystr.pbits) < net)
	{
		++paritystr.pbits;
		net = paritystr.pbits + size_str + 1;
	}

	int pos, inc = 0;

	for (int i = 0; i < paritystr.pbits; ++i)
	{
		pos = std::pow(2, i) - 1;
		paritystr.arr.insert(size_str - pos + inc, parity_char_str);
		++inc;
	}

	std::string parityvals = getparityvalues(paritystr);
	auto val = parityvals.begin();
	for (auto it = paritystr.arr.rbegin(); it != paritystr.arr.rend(); ++it)
	{
		if (*it == 'P')
		{
			std::cout << "Parity " << *val << "\n";
			*it = *val;
			++val;
		}
	}
	return paritystr;
}


std::string HammingCode::decode(StringWithParityCount paritystr)
{
	std::string recvparityvals = getparityvalues(paritystr);
	char oneorzero = *recvparityvals.begin();
	bool isvalid = true;

	for (auto it = recvparityvals.begin(); it != recvparityvals.end(); ++it)
	{
		if (*it != oneorzero)
		{
			isvalid = false;
			break;
		}
	}

	if (isvalid == false)
	{
		int pos = getnumfrombin(recvparityvals);
		if (paritystr.arr[pos] == '1')
		{
			paritystr.arr[paritystr.arr.length() - pos] = '0';
		}
		else
		{
			paritystr.arr[paritystr.arr.length() - pos] = '1';
		}
		//std::cout << "The corrected code is: " << paritystr.arr << "\n";
	}
	else
	{
		//std::cout << "\nThe received hamming code " << paritystr.arr << " is correct!\n";
	}
	int pos, size_str = paritystr.arr.length() - 1, dec = 0;
	
	//std::cout << "Parity string: " << paritystr.arr << "\t\t" << "Parity Bits: " << paritystr.pbits << "\n";
	
	for (int i = 0; i < paritystr.pbits; ++i)
	{
		
		pos = std::pow(2, i) - 1;
		paritystr.arr.erase(size_str - pos + dec, 1);
		
		//std::cout << "Parity string: " << paritystr.arr << "\t\t";
		//std::cout << "Removing: " << size_str - pos + dec << "\n";
		
		size_str = paritystr.arr.length() - 1;
		++dec;
	}
	return paritystr.arr;
}

std::string HammingCode::getparityvalues(StringWithParityCount &paritystr)
{
	std::string finalpvals;
	std::map<int, std::vector<int>> positions = getoneplaces(paritystr);

	for (auto it = positions.begin(); it != positions.end(); ++it)
	{
		int sum = 0;
		char parrlocval, finalpval;
		for (auto nums = it->second.begin(); nums != it->second.end(); ++nums)
		{
			parrlocval = *(paritystr.arr.end() - *nums);
			if (parrlocval == '1')
			{
				++sum;
			}
		}

		finalpval = *(getrevbin(sum, paritystr.pbits).begin());
		//std::cout << "Sum = " << sum << " for " << it->first << " Finalpval = " << finalpval << "\n";
		finalpvals.push_back(finalpval);
	}
	return finalpvals;
}

std::map<int, std::vector<int>> HammingCode::getoneplaces(StringWithParityCount &paritystr)
{
	std::map<int, std::string> bins;
	std::map<int, std::vector<int>> positions;

	for (int i = 1; i <= (int)paritystr.arr.length(); ++i)
	{
		bins[i] = getrevbin(i, paritystr.pbits);
	}

	for (auto it = bins.begin(); it != bins.end(); ++it)
	{
		for (int i = 0; i < paritystr.pbits; ++i)
		{
			if (it->second[i] == '1')
			{
				positions[i].push_back(it->first);
			}
		}
	}

	return positions;
}

std::string HammingCode::getbin(int num, int bits)
{
	std::string temp, ret;
	int rem, tempbits = 0;
	while (num > 0)
	{
		rem = num % 2;
		temp += ('0' + rem);
		num /= 2;
	}
	while (tempbits < bits)
	{
		temp += '0';
		++tempbits;
	}
	for (auto it = temp.rbegin(); it != temp.rend(); ++it)
	{
		ret += *it;
	}
	return ret;
}

std::string HammingCode::getrevbin(int num, int bits)
{
	std::string ret;
	int rem, tempbits = 0;
	while (num > 0)
	{
		rem = num % 2;
		ret += ('0' + rem);
		num /= 2;
		++tempbits;
	}
	while (tempbits < bits)
	{
		ret += '0';
		++tempbits;
	}
	return ret;
}


int HammingCode::getnumfrombin(std::string &num)
{
	int sum = 0, counter = 0;
	for (auto it = num.begin(); it != num.end(); ++it)
	{
		if (*it == '1')
		{
			sum += std::pow(2, counter);
		}
		++counter;
	}
	return sum;
}
