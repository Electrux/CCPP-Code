#include <iostream>
#include "../include/Letters.hpp"

int main()
{
	std::string text;
	
	const int width = 100,
		gap = 30;
	
	GraphicsEngine core;

	std::cout << "Enter text: ";
	std::getline( std::cin, text );
	
	core.initgraph();

	int x = 100, y = 100;

	int i = 0;
	int chardist = width + gap;

	for( auto ch : text ) {
		
		DrawLetter( core, x + i++ * chardist, y, width, ch );

		if( x + ( i + 1 ) * chardist >= ( int )core.windowsize().x ) {

			i = 0;
			y += chardist;
		}
	}
	
	/*
	C( core, x + i++ * chardist, y, width );
	H( core, x + i++ * chardist, y, width );
	I( core, x + i++ * chardist, y, width );
	R( core, x + i++ * chardist, y, width );
	A( core, x + i++ * chardist, y, width );
	G( core, x + i++ * chardist, y, width );
	*/
	
	core.closegraph();

	return 0;
}
