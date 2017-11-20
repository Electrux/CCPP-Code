#include <stdio.h>

#define MAX 10

int arr[MAX] = {10,20,30,40,50,60,70,80,90,100};

int binarysearch(int begin, int end, int data)
{
	if(begin > end) return -1;
	
	int mid = (begin + end) / 2;
	
	if(arr[mid] == data) return mid;
	
	if(arr[mid] < data)
		begin = mid + 1;
	else
		end = mid - 1;
	
	return binarysearch(begin, end, data);
}

int main()
{
	int beg = 0,
		end = MAX - 1,
		mid = (beg+end)/2,
		data, pos;

	printf("Enter what to search: ");
	scanf("%d", &data);

	//START BINARY SEARCH

	pos = binarysearch(begin, end, data);

	if(pos == -1)
	{
		printf("\nElement not found in the array.");
	}
	else
	{
		printf("\nElement found in array at %d position.\n", pos);
	}

	return 0;
}
