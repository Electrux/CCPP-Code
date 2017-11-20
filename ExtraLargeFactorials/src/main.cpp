#include <iostream>
#include <vector>

void multiplyarraywith(std::vector<int> &arr, int num)
{
	int mult = 0;

	int len = ( int )arr.size();
	
	for(int i = 0; i < len; ++i)
	{
		mult = mult + arr[i] * num;

		arr[ i ] = mult % 10 ;

		mult /= 10;
	}

	while( mult > 0 )
	{
		arr.push_back( mult % 10 );

		mult /= 10;
	}
}

int main()
{
	std::vector<int> arr = { 1 };

	int factof;

	//std::cout << "Calculate factorial of: ";
	std::cin >> factof;

	for(int i = 2; i <= factof; ++i)
		multiplyarraywith(arr, i);

	for(std::vector<int>::reverse_iterator it = arr.rbegin(); it != arr.rend(); it++)
		std::cout << *it;

	std::cout << "\n";

	return 0;
}
