#include <string>
#include <vector>

class Stack
{
	std::vector< std::string > stack;

public:

	void Push( const std::string & val );

	std::string Pop();

	std::string GetLast();

	std::string GetVal( int loc );

	size_t Size();
};
