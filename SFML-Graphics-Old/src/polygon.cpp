#include <SFML/Graphics.hpp>

#include "../include/Core.hpp"

int main()
{
	GraphicsEngine engine;

	engine.initgraph( 1920, 1080 );

	std::vector< sf::Vector2i > polygonpoints;

	// Polygon / Pentagon ( if last point is used )
	/*
	polygonpoints.push_back( { 10, 10 } );
	polygonpoints.push_back( { 1000, 150 } );
	polygonpoints.push_back( { 1000, 600 } );
	polygonpoints.push_back( { 400, 450 } );
	polygonpoints.push_back( { 200, 300 } );

	engine.polygon( polygonpoints, true );
	
	polygonpoints.clear();
	*/
	
	// X shape
	polygonpoints.push_back( { 120, 100 } );
	polygonpoints.push_back( { 360, 100 } );
	polygonpoints.push_back( { 600, 400 } );
	polygonpoints.push_back( { 840, 100 } );
	polygonpoints.push_back( { 1080, 100 } );
	polygonpoints.push_back( { 720, 500 } );
	polygonpoints.push_back( { 1080, 900 } );
	polygonpoints.push_back( { 840, 900 } );
	polygonpoints.push_back( { 600, 600 } );
	polygonpoints.push_back( { 360, 900 } );
	polygonpoints.push_back( { 120, 900 } );
	polygonpoints.push_back( { 480, 500 } );
	
	engine.polygon( polygonpoints, true );

	//engine.createandgetlinepoints( 1000, 150, 1000, 600 );

	engine.closegraph();
	
	return 0;
}
