/*

		Creator:	Electrux
		Date:		05/05/17

*/

#include <stdio.h>
#include <string.h>
#include "Base.h"

/*
	NOTE:
		Each line will be checked for by delimiting the text with a period and a space after it (example: Line ends here. A new line begins)

*/


//Gets the location of each paragraph and returns the total paragraph count.
/*
	Parameters:
	char * :	pointer to the text.
	int :		size of the text (in bytes).
	int * :		pointer to the integer array (paraloc) which shall store the location of each paragraph.
	int :		the size of the paraloc integer array.
*/
int GetParagraphs(char * text, int *paraloc , int locsize);


int main()
{
	//Paraloc contains the location k in text[k] of each new paragraph in the text. (PAR)
	int paraloc[10];

	//Contains total number of paragraphs. (NPAR)
	int nump = GetParagraphs(text, paraloc, 10);

	//Divide the text in lines.
	numl = DivideInLines(text);

	printf("Total Paragraphs:%d\tTotal lines: %d\n\n\n", nump, numl);

	//Display all lines.
	for (int i = 0; i < numl; ++i)
	{
		printf("\tLine %d: %s\n", i + 1, line[i]);
	}

	printf("\n\n");
	
	for (int i = 0; i < nump; ++i)
	{
		printf("Paragraph %d location: %d\n", i + 1, paraloc[i]);
	}

	//Hold on before u exit!!!
	getchar();

	//Letter to OS: All went OK dude! We cool here :P
	return 0;
}

int GetParagraphs(char * text, int * paraloc, int locsize)
{
	int i = 0;

	int paralocctr = 1;

	paraloc[0] = 0;

	while (text[i] != '\0')
	{
		//Check if the end of text is met (Period and then a space) & the linecounter should be less than linecount or the line variable will exceed max capacity.
		//This is the first condition that MUST be checked.

		if (text[i] == '.' &&
			text[i + 1] == '\0')
		{
			break;
		}
		else if (text[i] == '.' &&
					text[i + 1] == ' ' &&
					text[i + 2] == ' ' &&
					text[i + 3] == ' ' &&
					text[i + 4] == ' ' &&
					text[i + 5] == ' ')
		{
			//Bypass the period and 5 spaces.
			i += 6;
			//i += 6 is the position where the next para starts.

			//Set the paragraph location = position which is = i
			paraloc[paralocctr] = i;

			//Increment the paragraph location counter.
			paralocctr++;

			//Check if no more paragraphs can be added to the array.
			if (paralocctr >= locsize) break;
		}
		else
			i++;
	}
	return paralocctr;
}
