#include "Core.hpp"

void DrawLetter( GraphicsEngine &, int, int, int, char );
void A( GraphicsEngine &, int, int, int );
void B( GraphicsEngine &, int, int, int );
void C( GraphicsEngine &, int, int, int );
void D( GraphicsEngine &, int, int, int );
void E( GraphicsEngine &, int, int, int );
void F( GraphicsEngine &, int, int, int );
void G( GraphicsEngine &, int, int, int );
void H( GraphicsEngine &, int, int, int );
void I( GraphicsEngine &, int, int, int );
void J( GraphicsEngine &, int, int, int );
void K( GraphicsEngine &, int, int, int );
void L( GraphicsEngine &, int, int, int );
void M( GraphicsEngine &, int, int, int );
void N( GraphicsEngine &, int, int, int );
void O( GraphicsEngine &, int, int, int );
void P( GraphicsEngine &, int, int, int );
void Q( GraphicsEngine &, int, int, int );
void R( GraphicsEngine &, int, int, int );
void S( GraphicsEngine &, int, int, int );
void T( GraphicsEngine &, int, int, int );
void U( GraphicsEngine &, int, int, int );
void V( GraphicsEngine &, int, int, int );
void W( GraphicsEngine &, int, int, int );
void X( GraphicsEngine &, int, int, int );
void Y( GraphicsEngine &, int, int, int );
void Z( GraphicsEngine &, int, int, int );

void DrawLetter( GraphicsEngine &core, int x, int y, int width, char letter )
{
	if( letter == 'A' || letter == 'a' )
		A( core, x, y, width );

	if( letter == 'B' || letter == 'b' )
		B( core, x, y, width );

	if( letter == 'C' || letter == 'c' )
		C( core, x, y, width );

	if( letter == 'D' || letter == 'd' )
		D( core, x, y, width );

	if( letter == 'E' || letter == 'e' )
		E( core, x, y, width );

	if( letter == 'F' || letter == 'f' )
		F( core, x, y, width );

	if( letter == 'G' || letter == 'g' )
		G( core, x, y, width );

	if( letter == 'H' || letter == 'h' )
		H( core, x, y, width );

	if( letter == 'I' || letter == 'i' )
		I( core, x, y, width );

	if( letter == 'J' || letter == 'j' )
		J( core, x, y, width );

	if( letter == 'K' || letter == 'k' )
		K( core, x, y, width );

	if( letter == 'L' || letter == 'l' )
		L( core, x, y, width );

	if( letter == 'M' || letter == 'm' )
		M( core, x, y, width );

	if( letter == 'N' || letter == 'n' )
		N( core, x, y, width );

	if( letter == 'O' || letter == 'o' )
		O( core, x, y, width );

	if( letter == 'P' || letter == 'p' )
		P( core, x, y, width );

	if( letter == 'Q' || letter == 'q' )
		Q( core, x, y, width );

	if( letter == 'R' || letter == 'r' )
		R( core, x, y, width );

	if( letter == 'S' || letter == 's' )
		S( core, x, y, width );

	if( letter == 'T' || letter == 't' )
		T( core, x, y, width );

	if( letter == 'U' || letter == 'u' )
		U( core, x, y, width );

	if( letter == 'V' || letter == 'v' )
		V( core, x, y, width );

	if( letter == 'W' || letter == 'w' )
		W( core, x, y, width );

	if( letter == 'X' || letter == 'x' )
		X( core, x, y, width );

	if( letter == 'Y' || letter == 'y' )
		Y( core, x, y, width );

	if( letter == 'Z' || letter == 'z' )
		Z( core, x, y, width );
}

void A( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y + width, x + width / 2, y );
	core.line( x + width / 2, y, x + width, y + width );
	core.line( x + 0.25 * width, y + width / 2, x + 0.75 * width, y + width / 2 );
}

void B( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );

	core.line( x, y, x + 0.55 * width, y );
	core.line( x, y + width / 2, x + 0.55 * width, y + width / 2 );
	core.line( x, y + width, x + 0.55 * width, y + width );
	
	core.circle( width / 4, x + 0.55 * width, y + width / 4, 1 );
	core.circle( width / 4, x + 0.55 * width, y + width * 3 / 4, 1 );
}

void C( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x + width / 2, y, x + width, y );
	core.line( x + width / 2, y + width, x + width, y + width );
	core.circle( width / 2, x + width / 2, y + width / 2, 0);
}

void D( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );

	core.line( x, y, x + width * 0.4, y );
	core.line( x, y + width, x + width * 0.4, y + width );

	core.circle( width / 2, x + width * 0.4, y + width / 2, 1 );
}

void E( GraphicsEngine &core, int x, int y, int width )
{
	F( core, x, y, width );
	
	core.line( x, y + width, x + width, y + width );

}

void F( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );

	core.line( x, y, x + width, y );
	core.line( x, y + width / 2, x + 0.8 * width, y + width / 2 );
}

void G( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x + width / 2, y, x + width, y );
	core.line( x + width / 2, y + width, x + width, y + width );
	core.line( x + width, y + width / 2, x + width, y + width );
	core.line( x + width / 2, y + width / 2, x + width, y + width / 2 );

	core.circle( width / 2, x + width / 2, y + width / 2, 0 );
}

void H( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );
	core.line( x + width, y, x + width, y + width );
	core.line( x, y + width / 2, x + width, y + width / 2 );
}

void I( GraphicsEngine &core, int x, int y, int width )
{
	T( core, x, y, width );
	
	core.line( x, y + width, x + width, y + width );
}

void J( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + 0.15 * width );
	core.line( x + width, y, x + width, y + 0.15 * width );
	
	core.line( x, y, x +  width, y );
	core.line( x + width / 2, y, x + width / 2, y + 0.75 * width );

	core.circle( width * 0.17, x + 0.33 * width, y + 0.75 * width, 2 );
}

void K( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x + 0.15 * width, y );
	core.circle( width * 0.075, x + 0.08 * width, y + 0.95 * width, 2 );
	
	core.line( x + 0.15 * width, y, x + 0.15 * width, y + 0.95 * width );

	core.line( x + 0.15 * width, y + width / 2, x + width, y );
	core.line( x + 0.15 * width, y + width / 2, x + width, y + width );
}

void L( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x + width * 0.15, y, x + width * 0.15, y + width );
	core.line( x + width * 0.15, y + width, x + width, y + width );
}

void M( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );
	core.line( x + width, y, x + width, y + width );

	core.line( x, y, x + width / 2, y + width / 2 );
	core.line( x + width, y, x + width / 2, y + width / 2 );
}

void N( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );
	core.line( x + width, y, x + width, y + width );

	core.line( x, y, x + width, y + width );
}

void O( GraphicsEngine &core, int x, int y, int width )
{
	core.circle( width / 2, x + width / 2, y + width / 2 );
}

void P( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width );

	// For the upper curved part of R.
	core.line( x, y, x + 0.55 * width, y );
	core.line( x, y + width / 2, x + 0.55 * width, y + width / 2 );
	core.circle( width / 4, x + 0.55 * width, y + width / 4, 1 );
}

void Q( GraphicsEngine &core, int x, int y, int width )
{
	O( core, x, y, width );

	core.line( x + width * 0.65, y + width * 0.65, x + width * 1.05, y + width * 1.05 );
}

void R( GraphicsEngine &core, int x, int y, int width )
{
	P( core, x, y, width );
	
	core.line( x, y + width / 2, x + 0.85 * width, y + width );
}

void S( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x + width * 0.50, y, x + width * 0.85, y );
	core.line( x + width * 0.85, y, x + width, y + width * 0.15 );

	core.line( x + width * 0.15, y + width, x + width * 0.5, y + width );
	core.line( x + width * 0.15, y + width, x, y + width * 0.85 );
	
	core.circle( width * 0.25, x + width / 2, y + width * 0.25, 0 );
	core.circle( width * 0.25, x + width / 2, y + width * 0.75, 1 );
}

void T( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x + width, y );
	core.line( x + width / 2, y, x + width / 2, y + width );
}

void U( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x, y + width / 2 );
	core.line( x + width, y, x + width, y + width / 2 );

	core.circle( width / 2, x + width * 0.5, y + width / 2, 2 );
}

void V( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x + width / 2, y + width );
	core.line( x + width, y, x + width / 2, y + width );
}

void W( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x + width * 0.25, y + width );
	core.line( x + width * 0.25, y + width, x + width / 2, y + width / 2 );

	core.line( x + width, y, x + width * 0.75, y + width );
	core.line( x + width / 2, y + width / 2, x + 0.75 * width, y + width );
}

void X( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x + width * 0.15, y, x + width * 0.85, y + width );
	core.line( x + width * 0.85, y, x + width * 0.15, y + width );

	core.line( x, y, x + width * 0.15, y );
	core.line( x + width, y, x + width * 0.85, y );
	
	core.line( x, y + width, x + width * 0.15, y + width );
	core.line( x + width, y + width, x + width * 0.85, y + width );
}

void Y( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x + width / 2, y + width / 2 );
	core.line( x + width, y, x + width / 2, y + width / 2 );

	core.line( x + width / 2, y + width / 2, x + width / 2, y + width );
}

void Z( GraphicsEngine &core, int x, int y, int width )
{
	core.line( x, y, x + width, y );
	core.line( x, y + width, x + width, y + width );

	core.line( x + width, y, x, y + width );

	core.line( x, y, x + width * 0.05, y + width * 0.15 );
	core.line( x + width, y + width, x + width * 0.95, y + width * 0.85 );
}
