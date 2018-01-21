#ifndef DISPLAYFUNCS_HPP
#define DISPLAYFUNCS_HPP

#include <string>

void MoveOutputCursorBack();

// This function displays OneLiners.
// Basically, OneLiners are fleeting outputs which are to be erased after they
// are displayed. These are always displayed in between square brackets.
void DisplayOneLinerString( const std::string & str );

// This fetches the length of everything written uptil the point of call,
// on output, on the current single line ( before newline ).
// Once a newline is encountered, the counter is reset to 0.
int GetLastDispLen();

void DisplayData( const std::string & data );

#endif // DISPLAYFUNCS_HPP