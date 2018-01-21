#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../include/Colors.hpp"

#include "../include/DisplayFuncs.hpp"

static int one_liner = 0;
static int last_disp_len = 0;

const std::string RESET = COLORS[ "O" ];

int GetTermWidth()
{
	winsize w;

	ioctl( STDOUT_FILENO, TIOCGWINSZ, & w );
	// To accomodate \n, max column usable is ws_col - 1
	return w.ws_col - 1;
}

void MoveOutputCursorBack()
{
	for( int i = 0; i < one_liner; ++i )
		std::cout << "\b \b";

	std::cout.flush();

	one_liner = 0;
}

int GetLastDispLen()
{
	return last_disp_len;
}

void DisplayOneLinerString( const std::string & str )
{
	if( str.empty() )
		return;

	MoveOutputCursorBack();

	int term_width = GetTermWidth();
	int disp_len = GetLastDispLen();

	std::string output = str;

	if( disp_len >= term_width ) {
		// the size to work with is:
		// term_width -> total size to work with
		// - current_disp_len -> already used by previous displayed line
		if( term_width - disp_len < 0 )
			return;

		output = output.substr( 0, term_width - disp_len );
	}

	if( !output.empty() && * output.begin() == ' ' )
		output.erase( output.begin() );

	output = "{BC}" + output + "{O}";
	one_liner = SubstituteColors( output );

	std::cout << output << RESET;
	std::cout.flush();
}

void DisplayData( const std::string & data )
{
	if( data.find( '\n' ) != std::string::npos )
		one_liner = 0;

	if( data == "\n" ) {
		std::cout << "\n" << RESET;
		std::cout.flush();

		last_disp_len = 0;

		return;
	}

	std::string output = data;

	last_disp_len = SubstituteColors( output );

	std::cout << output << RESET;
	std::cout.flush();
}