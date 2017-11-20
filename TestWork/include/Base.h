//15 lines which can be held for now
#define MAX_LINE 15

//81 characters to incorporate the string terminator. 
#define MAX_CHAR 500

//Base problem static variable. 15 total lines possible (For now).
static char line[MAX_LINE][MAX_CHAR];

//This is the variable which contains the preface as per question.
static char text[] = "This is line 1. This is line 2.     This is paragraph 2.     This is line 4. This is line 5.     This is paragraph 4.";

//Stores the total number of lines (Note that each new paragraph must also be treated as a new line.
int numl = 0;

//Slices and dices the entire text in lines and returns number of lines
/*
Parameters:
char * :	pointer to the text.
*/
int DivideInLines(char * text)
{
	//Our dear standard counter.
	int i = 0;

	//This is a counter for the line and will be returned as number of lines used.
	int linectr = 0;

	//This is the variable to show the number of paragraphs.
	int numpara = 0;

	//This is a temporary variable to keep storing text and when a line is finished, throw the text in line variable.
	char templine[MAX_CHAR];

	//Counter for templine.
	int templinectr = 0;

	//Slice and dice the text in lines.
	while (text[i] != '\0')
	{
		//Check if the end of text is met (Period and then a space) & the linecounter should be less than linecount or the line variable will exceed max capacity.
		//This is the first condition that MUST be checked.
		if (text[i] == '.' &&
			text[i + 1] == '\0' &&
			linectr < MAX_LINE)
		{
			//We have to manually put a string terminator at the end of templine.
			templine[templinectr] = '\0';

			//Copy the templine to line.
			strcpy(line[linectr], templine);

			//Reset the temp line counter.
			templinectr = 0;

			//Increment the linecounter.
			linectr++;
		}
		//Check for the 5 spaces of new paragraph. It will also be prefixed by a fullstop anyway.
		//This condition MUST be after the end of text condition so as to prevent invalid memory access by the i + {1,2,3,4,5} checks.
		else if (text[i] == '.' &&
			text[i + 1] == ' ' &&
			text[i + 2] == ' ' &&
			text[i + 3] == ' ' &&
			text[i + 4] == ' ' &&
			text[i + 5] == ' ' &&
			linectr < MAX_LINE)
		{
			//We have to manually put a string terminator at the end of templine.
			templine[templinectr] = '\0';

			//Copy the templine to line.
			strcpy(line[linectr], templine);

			//Reset the temp line counter.
			templinectr = 0;

			//Increment the linecounter.
			linectr++;

			//To bypass the period and next 5 spaces. 5 jumps here and 1 by loop (i++) (for the 1 period and 5 spaces).
			i += 5;
		}
		//Check for a simple new line. This MUST be after the new paragraph check because this check also satisfies the new paragraph check.
		//Hence we need to be sure that it is just a new line and not a new paragraph.
		else if (text[i] == '.' &&
			text[i + 1] == ' ' &&
			linectr < MAX_LINE)
		{
			//We have to manually put a string terminator at the end of templine.
			templine[templinectr] = '\0';

			//Copy the templine to line.
			strcpy(line[0], templine);

			//Reset the temp line counter.
			templinectr = 0;

			//Increment the linecounter.
			linectr++;

			//To bypass the period and space. 1 here and 1 by loop (i++) (for the 1 period and 1 space).
			i++;
		}
		//Well there is no new line... Just add the text to templine and increment counter.
		else
		{
			templine[templinectr] = text[i];

			templinectr++;
		}
		i++;
	}

	//Return the total lines.
	return linectr;
}

