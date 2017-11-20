#include "../include/Core.hpp"

void applympcircle( GraphicsEngine &core,
		    int r,
		    int x_start,
		    int y_start )
{
	int x = r,
		y = 0,
		dx = 1,
		dy = 1,
		error = dx - r * 2;

	while ( x >= y ) {
		core.displaycirclepoints( x_start, y_start, x, y );

		if ( error <= 0 ) {
			y++;
			error += dy;
			dy += 2;
		}

		if ( error > 0 ) {
			x--;
			dx += 2;
			error += dx - r * 2;
		}
	}
}

int main()
{
	GraphicsEngine core;

	core.initgraph();

	applympcircle( core, 200, 500, 500 );

	core.closegraph();

	return 0;
}
