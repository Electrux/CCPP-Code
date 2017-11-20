#include "../include/Core.hpp"

void applydda( GraphicsEngine &core,
	       int x1,
	       int y1,
	       int x2,
	       int y2 )
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	float m = dy / ( float )dx;

	float x_inc, y_inc;
	
	if ( m <= 1 ) {
		x_inc = 1.0;
		y_inc = m;
	}
	else {
		x_inc = 1 / m;
		y_inc = 1.0;
	}

	float x_start = ( float )x1;
	float y_start = ( float )y1;

	while ( x_start != x2 || y_start != y2 ) {
		core.putpixel( ( int )x_start, ( int )y_start );

		x_start += x_inc;
		y_start += y_inc;
	}

	core.putpixel( x2, y2 );
}

int main()
{
	GraphicsEngine core;

	core.initgraph();

	applydda( core, 100, 100, 200, 200 );

	core.closegraph();
	
	return 0;
}
