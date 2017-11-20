#include "../include/Core.hpp"

void applybresmpcircle( GraphicsEngine &core,
		    int r,
		    int x_start,
		    int y_start )
{
	int x = 0,
		y = r;
	int d = 3 - 2 * r;

       	while ( y >= x ) {
		core.displaycirclepoints( x_start, y_start, x, y );

		x++;

		if ( d > 0 ) {
			y--;
			d = d + 4 * ( x - y ) + 10;
		}
		else {
			d = d + 4 * x + 6;
		}
	}
}

int main()
{
	GraphicsEngine core;

	core.initgraph();

	applybresmpcircle( core, 200, 500, 500 );

	core.closegraph();

	return 0;
}
