#include <iostream>
#include <string>
#include <cstdlib>

#include "../include/Init.hpp"

int Init()
{
	int retval = 0;

	std::cout << "Setting timedatectl to ntp... " << std::endl;
	retval = std::system( "timedatectl set-ntp true" );

	return retval;
}