/*

Creator:	Electrux
Date:		06/05/17

*/

#include <stdio.h>
#include <string.h>
#include "Base.h"


//Gets the count of occurrences of word in the text.
/*
Parameters:
	char * :	pointer to the text.
	char * :	the word which needs to be counted in the text.
*/
int CountWordOccurrences(char * text, char *word);

//Gets the length of string (including the null terminator if counted from zero).
/*
Parameters:
	char * :	the string of which the length is to be found.
*/
int getstringlength(char *str);

int main()
{
	int wordcount;
	char word[30];

	printf("Enter the word to count in the text: ");
	scanf("%s", word);

	wordcount = CountWordOccurrences(text, word);

	printf("The word %s occurred %d times.\n", word, wordcount);

	//Hold on before u exit!!!
	getchar();
	getchar();

	//Letter to OS: All went OK dude! We cool here :P
	return 0;
}

int CountWordOccurrences(char *text, char *word)
{
	int i = 0, j;

	int count = 0;

	int found;

	int textlen = getstringlength(text);
	int wordlen = getstringlength(word);

	//For the loop condition, we could use "text[i] != '\0'" as well instead of comparing with textlen.
	while (i < textlen)
	{
		//If the sum of current position of counter and wordlength goes greater to that of text length,
		//that means it is no longer possible to find the word in text because the word length exceeds the number
		//of characters remaining in the text.
		if (i + wordlen > textlen)
			break;

		found = 0;

		//In loop condition, we could also use "word[j] != '\0'" instead of using wordlen.
		for (j = 0; j < wordlen; j++)
		{
			if (text[i + j] == word[j])
			{
				found = 1;
			}
			else
			{
				found = 0;
				break;
			}
		}
		if (found == 1)
		{
			count++;
			i += wordlen;
		}
		else
			i++;
	}
	return count;
}

int getstringlength(char *str)
{
	int len = 0;

	while (str[len] != '\0') len++;

	return len;
}