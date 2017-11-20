//
// Created by Electrux Redsworth on 9/19/17.
//

#ifndef PROJECTCREATOR_SFMLDEFAULTMAIN_HPP
#define PROJECTCREATOR_SFMLDEFAULTMAIN_HPP

#include <string>

const std::string SFMLDEFAULTMAIN = "#include <SFML/Graphics.hpp>\n"
	"\n"
	"int main(int argc, char **argv)\n"
	"{\n"
	"       sf::RenderWindow window( sf::VideoMode(800, 600), \"SFML Default\" );\n"
	"       sf::Event event;\n"
	"\n"
	"       while( window.isOpen() )\n"
	"       {\n"
	"               while( window.pollEvent( event ) )\n"
	"               {\n"
	"                       if( event.type == sf::Event::Closed )\n"
	"                               window.close();\n"
	"                       if( event.type == sf::Event::KeyPressed )\n"
	"                               if( event.key.code == sf::Keyboard::Escape )\n"
	"                                       window.close();\n"
	"               }\n"
	"\n"
	"               window.clear();\n"
	"               window.display();\n"
	"       }\n"
	"\n"
	"       return 0;\n"
	"}\n";

#endif //PROJECTCREATOR_SFMLDEFAULTMAIN_HPP
