#ifndef PIXELMAP_HPP
#define PIXELMAP_HPP

#include <SFML/Graphics.hpp>

#define LOOP_COLORS

#ifdef LOOP_COLORS

// Use 1 for red, + blue, + green.
// Use 2 for red, then blue, then green.
// If COLOR_CYCLE is defined, color scheme 1
// & 2 will cycle between themselves.
// Use 3 for blue to teal.
#define INIT_COLOR_ALGO 3

//#define COLOR_CYCLE

#include <iostream>

#endif

class PixelMap : public sf::Drawable
{
	sf::Color color;

	int width, height;

#ifdef LOOP_COLORS

	int coloralgo;

	int whichcol;
	
#endif // LOOP_COLORS
	
	sf::Image pixmapimg;
	sf::Texture texture;
	sf::Sprite sprite;

	virtual void draw( sf::RenderTarget &target,
			   sf::RenderStates states ) const
	{
		target.draw( sprite, states );
	}

	void create( int width, int height )
	{
		this->width = width;
		this->height = height;

		color = sf::Color::White;

#ifdef LOOP_COLORS

		color.r = 0;
		color.g = 0;
		color.b = 0;
		color.a = 255;

		coloralgo = INIT_COLOR_ALGO;

		whichcol = 0;

#endif // LOOP_COLORS

		pixmapimg.create( width, height, sf::Color::Black );
		texture.loadFromImage( pixmapimg, sf::IntRect( 0, 0, width, height ) );
		sprite.setTexture( texture );
	}

#ifdef LOOP_COLORS

	void nextcolor()
	{
		if( coloralgo == 1 ) {

			if( color.b == 255 ) {
				if( color.g == 255 ) {
					if( color.r == 255 ) {
						color.r = 0;
						color.g = 0;
						color.b = 0;

#ifdef COLOR_CYCLE
						
						coloralgo = 2;

#endif // COLOR_CYCLE
						
					}
					else {
						color.r++;
					}
				}
				else {
					color.g++;
				}
			}
			else {
				color.b++;
			}
		}
		else if( coloralgo == 2 ) {

			if( whichcol == 0 ) {
				color.r++;

				if( color.r == 255 )
					whichcol = 1;
			}
			else if( whichcol == 1 ) {
				color.g++;

				if( color.g == 255 )
					whichcol = 2;
			}
			else if( whichcol == 2 ) {
				color.b++;

				if( color.b == 255 ) {
					whichcol = 0;
				
					color.r = 0;
					color.g = 0;
					color.b = 0;

#ifdef COLOR_CYCLE
					
					coloralgo = 1;

#endif // COLOR_CYCLE
					
				}
			}
		}
		else if( coloralgo == 3 ) {
			
			if( color.b == 255 ) {
				if( color.g == 255 ) {
					if( color.r == 255 ) {
						color.r = 0;
					}
					else {
						color.r++;
					}

					color.g = 0;
				}
				else {
					color.g++;
				}

				color.b = 0;
			}
			else {
				color.b++;
			}
			
		}
	}

#endif // LOOP_COLORS

public:

	PixelMap() {}

	PixelMap( int width, int height ) { this->create( width, height ); }

	void init( int width, int height ) { this->create( width, height ); }

	void setcolor( sf::Color color ) { this->color = color; }

	void putpixel( int pos_x, int pos_y )
	{
		if( pos_x >= width || pos_y >= height )
			return;

#ifdef LOOP_COLORS
		
		this->nextcolor();

#endif // LOOP_COLORS
		
		pixmapimg.setPixel( pos_x, pos_y, color );

	}

	void updateimage()
	{
		texture.loadFromImage( pixmapimg, sf::IntRect( 0, 0, width, height ) );
		sprite.setTexture( texture );
	}
};

#endif //PIXELMAP_HPP
