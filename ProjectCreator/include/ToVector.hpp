//
//  tovector.hpp
//  ProjectCreator
//
//  Created by Electrux Redsworth on 9/19/17.
//  Copyright © 2017 Electrux Redsworth. All rights reserved.
//

#ifndef tovector_hpp
#define tovector_hpp

#include <iostream>
#include <vector>

std::vector< std::string > ConvertToVector( int argc, const char **argv )
{
	std::vector< std::string > temp;

	for( int i = 0; i < argc; ++i )
		temp.push_back( std::string( argv[ i ] ) );

	return temp;
}

#endif /* tovector_hpp */
