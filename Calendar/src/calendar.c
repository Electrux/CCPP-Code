#include <stdio.h>

static const char *today[7] = {
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday"
};

static const int monthoddnotleap[12] = {
	3,	//Jan
	0,	//Feb
	3,	//Mar
	2,	//Apr
	3,	//May
	2,	//Jun
	3,	//Jul
	3,	//Aug
	2,	//Sep
	3,	//Oct
	2,	//Nov
	3	//Dec
};

static const int monthoddleap[12] = {
	3,	//Jan
	1,	//Feb
	3,	//Mar
	2,	//Apr
	3,	//May
	2,	//Jun
	3,	//Jul
	3,	//Aug
	2,	//Sep
	3,	//Oct
	2,	//Nov
	3	//Dec
};

void getDate(int *day, int *month, int *year);
int checkleap(int yr);
int checkcentury(int yr);
int getOddDayToMD(int month, int day, int isleap);
int getOddToYear(int yr);

int main()
{
	int year, day, month;
	int tot_odd;
	getDate(&day, &month, &year);
	tot_odd = getOddToYear(year);
	if(checkleap(year))
	{
		tot_odd += getOddDayToMD(month, day, 1);
	}
	else
	{
		tot_odd += getOddDayToMD(month, day, 0);
	}
	tot_odd %= 7;
	printf("\nThe day is: %s\n", today[tot_odd]);
	return 0;
}

void getDate(int *day, int *month, int *year)
{
	printf("Enter day: ");
	scanf("%d", day);
	printf("Enter month: ");
	scanf("%d", month);
	printf("Enter year: ");
	scanf("%d", year);
}

int checkleap(int yr)
{
	if((yr % 100 == 0 && yr % 400 == 0) || (yr % 100 != 0 && yr % 4 == 0))
	{
		return 1;
	}
	return 0;
}

int checkcentury(int yr)
{
	if(yr % 100 == 0) return 1;
	else return 0;
}

int getOddDayToMD(int month, int day, int isleap)
{
	int i, tot = 0;
	for(i = 0; i < month - 1; ++i)
	{
		if(isleap)
		{
			tot += monthoddleap[i];
		}
		else
		{
			tot += monthoddnotleap[i];
		}
	}
	tot += day % 7;
	return tot;
}

int getOddToYear(int yr)
{
	yr--; //Check till the previous year of given year
	if(checkleap(yr) && checkcentury(yr)) return 0;
	int totalodd = 0, centuryodd = 0;
	yr = (yr) % 400;
	centuryodd = ((yr) / 100) * 5;
	yr = (yr) % 100;
	totalodd = (yr) + ((yr) / 4);
	totalodd += centuryodd;
	return totalodd;
}