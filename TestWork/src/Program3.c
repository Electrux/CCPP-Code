/*

Creator:	Electrux
Date:		08/05/17

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
	char *	:	pointer to the text.
	int		:	size of the text (in bytes).
	int *	:	pointer to the integer array (paraloc) which shall store the location of each paragraph.
	int		:	the size of the paraloc integer array.
*/
int GetParagraphs(char * text, int paraloc[][2], int locsize);


//Swaps paragraph j and k
/*
Parameters:
	char *		:	pointer to the text.
	int [][2]	:	integer array of every paragraph's start and end location. (Note that due to the working of C, it automatically passes as reference).
	int			:	the id of paragraph 1 to replace.
	int			:	the id of paragraph 2 to replace.
*/
int SwapParagraph(char * text, int paraloc[][2], int j, int k);

//Shifts the text from [from, to] towards right side taking to as end point.
/*
Parameters:
	char *	:	pointer to the text.
	int		:	the starting position (left side one).
	int		:	the ending position (right side one).
	int		:	the offset with which to shift.
*/
void ShiftTextRight(char * text, int from, int to, int offset);

//Shifts the text from [from, to] towards left side taking to - offset as end point.
/*
Parameters:
	char *	:	pointer to the text.
	int		:	the starting position (left side one).
	int		:	the ending position (right side one).
	int		:	the offset with which to shift.
*/
void ShiftTextLeft(char * text, int from, int to, int offset);

//Gets the length of the string (Excluding null terminator).
/*
Parameters:
	char *	:	pointer to the text.
*/
int GetStringLength(char * text);

int main()
{
	//Paraloc contains the location k in text[k] of each new paragraph in the text. (PAR)
	int paraloc[10][2];

	//Contains total number of paragraphs. (NPAR)
	int nump = GetParagraphs(text, paraloc, 10);

	//Divide the text in lines.
	numl = DivideInLines(text);

	//Display total number of paragraphs and total number of lines.
	printf("Total Paragraphs:%d\tTotal lines: %d\n\n\n", nump, numl);

	//Display all lines.
	for (int i = 0; i < numl; ++i)
	{
		printf("\tLine %d: %s\n", i + 1, line[i]);
	}

	printf("\n");

	for (int i = 0; i < nump; ++i)
	{
		printf("Paragraph %d location: %d %d\n", i + 1, paraloc[i][0], paraloc[i][1]);
	}

	printf("\n\n");

	printf("Original Text:\n%s\n\n\n", text);

	//Swap the paragraphs n1, n2 where n1 and n2 are ids of paragraphs from [0,n).
	SwapParagraph(text, paraloc, 1, 2);

	//Display the swapped text.
	printf("New Text:\n%s\n\n\n", text);

	//Print all the paragraph numbers and their locations.
	for (int i = 0; i < nump; ++i)
	{
		printf("Paragraph %d location: %d %d\n", i + 1, paraloc[i][0], paraloc[i][1]);
	}

	//Hold on before u exit!!!
	getchar();

	//Letter to OS: All went OK dude! We cool here :P
	return 0;
}

int GetParagraphs(char * text, int paraloc[][2], int locsize)
{
	int i = 0;

	int paralocctr = 0;

	paraloc[0][0] = 0;

	while (text[i] != '\0')
	{
		//Check if the end of text is met (Period and then a space) & the linecounter should be less than linecount or the line variable will exceed max capacity.
		//This is the first condition that MUST be checked.

		if (text[i] == '.' &&
			text[i + 1] == '\0')
		{
			//Set paragraph end location = i (Including fullstop)
			paraloc[paralocctr][1] = i;
			paralocctr++;
			break;
		}
		else if (text[i] == '.' &&
			text[i + 1] == ' ' &&
			text[i + 2] == ' ' &&
			text[i + 3] == ' ' &&
			text[i + 4] == ' ' &&
			text[i + 5] == ' ')
		{
			//Set the paragraph end location = i (Including fullstop)
			paraloc[paralocctr][1] = i;

			//Bypass the period and 5 spaces.
			i += 6;
			//i += 6 is the position where the next para starts.

			//Increment the paragraph location counter.
			paralocctr++;

			//Set the paragraph location = position which is = i
			paraloc[paralocctr][0] = i;

			//Check if no more paragraphs can be added to the array.
			if (paralocctr >= locsize) break;
		}
		else
			i++;
	}
	//Return the paralocation counter (which is actually the count of number of paragraphs).
	return paralocctr;
}

int SwapParagraph(char * text, int paraloc[][2], int j, int k)
{
	int diff;

	char temp[500];

	//Length of j and k paragraphs.
	int len1 = paraloc[j][1] - paraloc[j][0];
	int len2 = paraloc[k][1] - paraloc[k][0];

	if (len1 < len2)
	{
		//Difference between both lengths.
		diff = len2 - len1;
		
		//First take k in a temp var.
		for (int i = paraloc[k][0]; i <= paraloc[k][1]; ++i)
		{
			temp[i - paraloc[k][0]] = text[i];
		}

		//MUST do this after taking k in tempvar since this will modify locations of k as well.
		//Shift the entire paragraph to right from the ending of last paragraph to ending of 1st paragraph.
		ShiftTextRight(text, paraloc[j][1], paraloc[k][1], diff);

		//Initial location for the characters of paragraph k.
		int startlock = paraloc[k][0] + diff;

		//Put the paragraph j in paragraph k.
		for (int i = startlock; i <= startlock + len1; ++i)
		{
			text[i] = text[paraloc[j][0] + i - startlock];
		}
		
		//Put the paragraph k in paragraph j from temp.
		for (int i = paraloc[j][0]; i <= paraloc[j][0] + len2; ++i)
		{
			text[i] = temp[i - paraloc[j][0]];
		}
		
		//Adjust the location positions of paragraph j and k.

		//Add initial location of j + length of k to give final location of j.
		paraloc[j][1] = paraloc[j][0] + len2;

		//Add difference of lengths from initial location ok k because entire k has shifted right.
		paraloc[k][0] += diff;

		//Add initial location of k + length of j to give final location of k.
		paraloc[k][1] = paraloc[k][0] + len1;

		//Also shift all the locations between (j, k) to right because everything in between has also shifted right. (Here () means : NOT inclusive)
		for (int i = j + 1; i < k; ++i)
		{
			paraloc[i][0] += diff;
			paraloc[i][1] += diff;
		}

		//NOTE: Now, these lengths (len1, len2) are also reversed hence should no longer be used.
	}
	else if(len1 > len2)
	{
		//Difference between both lengths.
		diff = len1 - len2;

		//First take j in a temp var.
		for (int i = paraloc[j][0]; i <= paraloc[j][1]; ++i)
		{
			temp[i - paraloc[j][0]] = text[i];
		}

		//Shift the entire paragraph to left from the ending of first paragraph to ending of 2nd paragraph.
		ShiftTextLeft(text, paraloc[j][1], paraloc[k][1], diff);

		//Initial location for characters of paragraph k.
		int startlock = paraloc[k][0] - diff;

		//Put the paragraph k in paragraph j.
		for (int i = paraloc[j][0]; i <= paraloc[j][0] + len2; ++i)
		{
			text[i] = text[startlock + i - paraloc[j][0]];
		}

		//Put the paragraph j in paragraph k from temp.
		for (int i = startlock; i <= startlock + len1; ++i)
		{
			text[i] = temp[i - startlock];
		}

		//NOTE: Here, both loops above require startlock. That is because, when we move k in j we need relative position of k to move from(including offset/diff)
		//and in second loop we move j in k from temp we need relative position of k to move in.
		//But in the RightShift case, we move first j in k which requires relative position of k
		//and in the second loop, we move k in j using temp which does not require k at all therefore no use for startlock.
		//On the contrary, we use paraloc[j] twice in the RightShift case and once in the LeftShift case.
		//Therefore,	RightShift case - 2x paraloc[j], 1x startlock,
		//and,			LeftShift  case - 2x startlock, 1x paraloc[j].

		//Adjust the location positions of paragraph j and k.

		//Add initial location of j + length of k to give final location of j.
		paraloc[j][1] = paraloc[j][0] + len2;
		
		//Subtract difference of lengths from initial location ok k because entire k has shifted left.
		paraloc[k][0] -= diff;

		//Add initial location of k + length of j to give final location of k.
		paraloc[k][1] = paraloc[k][0] + len1;

		//Also shift all the locations between (j, k) to left because everything in between has also shifted left.
		for (int i = j + 1; i < k; ++i)
		{
			paraloc[i][0] -= diff;
			paraloc[i][1] -= diff;
		}

		//NOTE: Now, these lengths (len1, len2) are also reversed hence should no longer be used.
	}
	else
	{
		//First take j in a temp var.
		for (int i = paraloc[j][0]; i <= paraloc[j][1]; ++i)
		{
			temp[i - paraloc[j][0]] = text[i];
		}

		//Put the paragraph k in paragraph j.
		for (int i = paraloc[j][0]; i <= paraloc[j][0] + len2; ++i)
		{
			text[i] = text[paraloc[k][0] + i - paraloc[j][0]];
		}


		//Put the paragraph j in paragraph k from temp.
		for (int i = paraloc[k][0]; i <= paraloc[k][0] + len1; ++i)
		{
			text[i] = temp[i - paraloc[k][0]];
		}

		//NOTE: We dont have to change location positions of j and k here because both the lengths are same.
	}
}

void ShiftTextRight(char * text, int from, int to, int offset)
{
	int i;
	int len = GetStringLength(text);

	//Move everything from the end to initial using offset.
	//Note that we dont use to + offset here because it will cause everything on the right till offset to be overwritten, which we don't want.
	//This overwrites the end position with offset values instead of shifting everything to the right.
	for (i = to; i >= from + offset; --i)
	{
		//Move eveything from i - offset to i.
		text[i] = text[i - offset];
	}
}

void ShiftTextLeft(char * text, int from, int to, int offset)
{
	int i;
	int len = GetStringLength(text);

	//Move everything from the initial to end.
	//We do use from - offset here because we actually need to decrease space on the left to give space on the right.
	//We actually SHIFT everything to the left.
	for (i = from - offset; i <= to - offset; ++i)
	{
		text[i] = text[i + offset];
	}
}

int GetStringLength(char * text)
{
	int len = 0;

	while (text[len] != '\0') len++;

	//Not include \0
	return len - 1;
}