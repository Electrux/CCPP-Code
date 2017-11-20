#ifndef CORE_HPP
#define CORE_HPP

//#define DEBUG_INFO
//#define VERBOSE_DEBUG_INFO
#define CONTINUOUS_UPDATE

#ifdef DEBUG_INFO

#include <iostream>
#include <chrono>
#include <thread>

#endif

#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>

#include <cmath>

#include "PixelMap.hpp"

const static double PI = 3.14159;

class GraphicsEngine
{
	sf::RenderWindow window;
	sf::Event event;
	PixelMap pixmap;

#ifdef DEBUG_INFO

	int pixelcount;

#endif // DEBUG_INFO

	float getangle( int x1, int y1, int x2, int y2 ) { return ( float )std::atan2(y2 - y1, x2 - x1); }

	int round( float num ) { return ( num - ( int )num >= 0.5 ) ? num + 1 : num; }

	void pollevent()
	{
		while( window.pollEvent( event ) ) {
			
		       	if( event.type == sf::Event::Closed )
			       	window.close();

       			if( event.type == sf::Event::KeyPressed &&
			    event.key.code == sf::Keyboard::Escape )
	       			window.close();
		}
	}

public:

	GraphicsEngine()
	{

#ifdef DEBUG_INFO

		pixelcount = 0;

#endif // DEBUG_INFOx

	}

	void initgraph( int width = 1280,
			int height = 720,
			std::string title = "SFML Default" )
	{
		window.create( sf::VideoMode( width, height ), title );
		pixmap.init( width, height );
	}

	sf::Vector2u windowsize() { return window.getSize(); }

	void putpixel( int pos_x, int pos_y )
	{

#ifdef DEBUG_INFO

		pixelcount++;

#endif // DEBUG_INFO

		pixmap.putpixel( pos_x, pos_y );
	}

	void line( int x1, int y1, int x2, int y2 )
	{
		float angle = this->getangle( x1, y1, x2, y2 );

		float x_start = ( float ) x1;
		float y_start = ( float ) y1;

		float x_inc = std::cos( angle );
		float y_inc = std::sin( angle );

		while ( this->round( x_start ) != x2 || this->round( y_start ) != y2 ) {

			this->putpixel( ( int )x_start, ( int )y_start );

			x_start += x_inc;
			y_start += y_inc;

		}

		this->putpixel( x2, y2 );

#ifdef CONTINUOUS_UPDATE

		pixmap.updateimage();
		
		if( window.isOpen() ) {
			this->pollevent();
			this->show();
		}

#endif // CONTINUOUS_UPDATE

	}

	void polygon( std::vector< sf::Vector2i > polygonpoints,
		      bool fill = false )
	{
		std::vector< std::vector< sf::Vector2i > > lines;

		for( auto polypts = polygonpoints.begin();
		     polypts != polygonpoints.end();
		     ++polypts )
		{
			if( polypts == polygonpoints.end() - 1 )
				lines.push_back(
					this->createandgetlinepoints(
						polypts->x, polypts->y,
						polygonpoints.begin()->x,
						polygonpoints.begin()->y )
					);
			else
				lines.push_back(
					this->createandgetlinepoints(
						polypts->x, polypts->y,
						( polypts + 1 )->x,
						( polypts + 1 )->y )
					);
		}

#ifdef DEBUG_INFO

		std::cout << "Count: " << lines.size() << "\n";

#endif // DEBUG_INFO

		if( !fill ) return;
		
		std::vector< sf::Vector2i > side1,
			side2;

		if( lines.size() % 2 == 0 ) {
			for( int i = 0; i < ( int )lines.size() / 2; ++i )
				side1 = this->addvec( side1, lines[ i ] );

			for( int i = ( int )lines.size() / 2; i < ( int )lines.size(); ++i )
				side2 = this->addvec( side2, lines[ i ] );

			this->linetoline( side1, side2 );
		}
		else {
			for( int i = 0; i < ( ( int )lines.size() / 2 ); ++i )
				for( int j = ( ( int )lines.size() / 2 ) + 1; j < ( int )lines.size(); ++j )
					this->linetoline( lines[ i ], lines[ j ] );
		}

#ifdef DEBUG_INFO

		std::cout << "\nFinished!\n\n";

#endif // DEBUG_INFOx

	}

	void linetoline( std::vector< sf::Vector2i > line1,
			 std::vector< sf::Vector2i > line2 )
	{
		if( line1.empty() || line2.empty() ) {

#ifdef DEBUG_INFO

			std::cout << "Empty lines found ( they have no coordinates at all )..."
				  << " wont continue this.\n"
				  << "Line 1: " << line1.size() << "\t"
				  << "Line 2: " << line2.size() << "\n";

#endif // DEBUG_INFO

			return;
		}
		
		float ratio = line1.size() / ( float )line2.size();

#ifdef DEBUG_INFO

		std::cout << "Ratio is: " << ratio << "\n"
			  << "Line 1: " << line1.size() << "\t"
			  << "Line 2: " << line2.size() << "\n";

#endif // DEBUG_INFO

		if( ratio < 1 ) {
			float inc = 0.0;
			int ctr = 0;
			
			while( ctr < ( int )line2.size()
			       && ( int )inc < ( int )line1.size() ) {

				this->line( line2[ ctr ].x,
					    line2[ ctr ].y,
					    line1[ ( int )inc ].x,
					    line1[ ( int )inc ].y );

#ifdef DEBUG_INFO

#ifdef VERBOSE_DEBUG_INFO

				std::cout << "Line 2 x: " << line2[ ctr ].x << "\t"
					  << "Line 2 y: " << line2[ ctr ].y << "\t\t"
					  << "Line 1 x: " << line1[ ( int )inc ].x << "\t"
					  << "Line 1 y: " << line1[ ( int )inc ].y << "\n";

#endif // VERBOSE_DEBUG_INFO

				std::this_thread::sleep_for( std::chrono::nanoseconds( 500000 ) );

#endif // DEBUG_INFO

				inc += ratio;
				ctr++;
			}
		}
		else {
			float inc = 0.0;
			int ctr = 0;
			
			while( ctr < ( int )line1.size()
			       && ( int )inc < ( int )line2.size() ) {
				
				this->line( line1[ ctr ].x,
					    line1[ ctr ].y,
					    line2[ ( int )inc ].x,
					    line2[ ( int )inc ].y );

#ifdef DEBUG_INFO

#ifdef VERBOSE_DEBUG_INFO

				std::cout << "Line 2 x: " << line2[ ctr ].x << "\t"
					  << "Line 2 y: " << line2[ ctr ].y << "\t\t"
					  << "Line 1 x: " << line1[ ( int )inc ].x << "\t"
					  << "Line 1 y: " << line1[ ( int )inc ].y << "\n";

#endif // VERBOSE_DEBUG_INFO

				std::this_thread::sleep_for( std::chrono::nanoseconds( 500000 ) );

#endif // DEBUG_INFO

				inc += 1.0/ratio;
				ctr++;
			}
		}
	}

	std::vector< sf::Vector2i > createandgetlinepoints( int x1, int y1, int x2, int y2 )
	{
		std::vector< sf::Vector2i > temp;
		
		int diffx = ( x2 - x1 >= 0 ) ? x2 - x1 : x1 - x2;
		int diffy = ( y2 - y1 >= 0 ) ? y2 - y1 : y1 - y2;

		float x_start, y_start,
			x_end, y_end;

		if( diffx > diffy ) {
			x_start = ( x1 <= x2 ) ? x1 : x2;
			y_start = ( x1 <= x2 ) ? y1 : y2;

			x_end = ( x1 >= x2 ) ? x1 : x2;
			y_end = ( x1 >= x2 ) ? y1 : y2;
		}
		else {
			x_start = ( y1 <= y2 ) ? x1 : x2;
			y_start = ( y1 <= y2 ) ? y1 : y2;

			x_end = ( y1 >= y2 ) ? x1 : x2;
			y_end = ( y1 >= y2 ) ? y1 : y2;
		}

		float angle = this->getangle( x_start, y_start, x_end, y_end );

		float x_inc = std::cos( angle );
		float y_inc = std::sin( angle );

		while( this->round( x_start ) != x_end || this->round( y_start ) != y_end ) {

			this->putpixel( ( int )x_start, ( int )y_start );

			temp.push_back( { ( int )x_start, ( int )y_start } );

			x_start += x_inc;
			y_start += y_inc;
		}

		this->putpixel( x_end, y_end );
		temp.push_back( { ( int )x_end, ( int )y_end } );

		return temp;
	}

	void displaycirclepoints( int x_start,
				  int y_start,
				  int x,
				  int y,
				  int semicircle = -1 )
	{
		if( semicircle == 3 || semicircle == -1 ) {
			this->putpixel( x_start + x, y_start - y );
			this->putpixel( x_start + y, y_start - x );
			this->putpixel( x_start - x, y_start - y );
			this->putpixel( x_start - y, y_start - x );
		}
		
		if( semicircle == 2 || semicircle == -1 ) {
			this->putpixel( x_start + x, y_start + y );
			this->putpixel( x_start + y, y_start + x );
			this->putpixel( x_start - x, y_start + y );
			this->putpixel( x_start - y, y_start + x );
		}
		
		if ( semicircle == 1 || semicircle == -1 ) {
			this->putpixel( x_start + x, y_start + y );
			this->putpixel( x_start + x, y_start - y );
			this->putpixel( x_start + y, y_start + x );
			this->putpixel( x_start + y, y_start - x );
		}
		
		if ( semicircle == 0 || semicircle == -1 ) {
			this->putpixel( x_start - x, y_start + y );
			this->putpixel( x_start - x, y_start - y );
			this->putpixel( x_start - y, y_start + x );
			this->putpixel( x_start - y, y_start - x );
		}
	}

	void circle( int r,
		     int x_start,
		     int y_start,
		     int semicircle = -1 )
	{
		int x = r, y = 0,
			dx = 1, dy = 1,
			error = dx - r * 2;

		while ( x >= y ) {
			this->displaycirclepoints( x_start, y_start, x, y, semicircle );

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

	template < typename T >
	std::vector< T > addvec( const std::vector< T > &v1,
				 const std::vector< T > &v2 )
	{
		std::vector< T > temp = v1;
		
		for( auto v2val : v2 )
			temp.push_back( v2val );

		return temp;
	}

	void setpixelcolor( sf::Color color ) { pixmap.setcolor( color ); }

	void closegraph()
	{

#ifdef DEBUG_INFO

		std::cout << "\n\nTotal PutPixel Calls: " << pixelcount << "\n";

#endif // DEBUG_INFO
		
		pixmap.updateimage();
		
		while( window.isOpen() ) {
			this->pollevent();
			this->show();
		}
	}

	bool isopen() { return window.isOpen(); }

	void show()
	{
		window.clear();
		window.draw( pixmap );
		window.display();
	}
};

#endif // CORE_HPP
