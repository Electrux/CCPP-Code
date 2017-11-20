#include <SFML/Graphics.hpp>
#include "../include/Core.hpp"

int main(int argc, char **argv)
{
	GraphicsEngine core;

	core.initgraph();

	core.setpixelcolor( sf::Color::White );

	core.putpixel( 100, 200 );

	core.line( 100, 100, 100, 200 );

	core.closegraph();

	return 0;
}
