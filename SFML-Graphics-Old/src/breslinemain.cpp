#include "../include/Core.hpp"

void applybresline( GraphicsEngine &core,
	       int x1,
	       int y1,
	       int x2,
	       int y2 )
{
	int dx = x2 - x1;
	int dy = y2 - y1;

	float m = ( dx == 0 ) ? 1.0 : dy / ( float )dx;

       	float tot_err = 0.0;
	
	while ( x1 != x2 || y1 != y2 ) {
		core.putpixel( x1, y1 );

		tot_err += m;

		if ( tot_err >= 0.5 ) {
			y1++;
			tot_err--;
		}

		if ( dx != 0 )
			x1++;
	}

	core.putpixel( x2, y2 );
}

int main()
{
	GraphicsEngine core;

	core.initgraph();

	applybresline( core, 100, 100, 200, 200 );

	core.closegraph();
	
	return 0;
}
