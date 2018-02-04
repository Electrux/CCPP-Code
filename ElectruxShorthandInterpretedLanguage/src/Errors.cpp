#include <string>

#include "../include/Errors.hpp"

std::string ErrorToStr( ErrorTypes errtype )
{
	if( errtype < 0 || errtype >= LAST )
		return ErrorStrings[ LAST ];

	return ErrorStrings[ errtype ];
}
