#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <wchar.h>

typedef struct _str {
	unsigned long long count[128], total;
} data;

void *find(void *_file)
{
	char *__file = (char *)_file;
	FILE *file = fopen(__file, "r");
	if(file == NULL)
	{
		return NULL;
	}
	wint_t ch;
	data *dat = (data*)malloc(sizeof(data));
	for(int p = 0; p < 128; ++p)
	{
		dat->count[p] = 0;
	}
	dat->total = 0;
	while((ch = fgetwc(file)) != EOF)
	{
		dat->count[ch]++;
		dat->total++;
	}
	fclose(file);
	return dat;
}

int main(int argc, char *argv[])
{
	unsigned long long count[128] = {}, total = 0;
	int tot_files = argc - 1;
	if(tot_files == 0)
	{
		printf("Usage: %s <file 1> <file 2> <file 3> .... <file n>\n", argv[0]);
		return 0;
	}
	time_t start, end;
	double diff_time;
	time(&start);
	/**/
	pthread_t thread[tot_files];
	for(int i = 0; i < tot_files; ++i)
	{
		pthread_create(&thread[i], NULL, find, argv[i + 1]);
	}
	for(int i = 0; i < tot_files; ++i)
	{
		void *ret;
		pthread_join(thread[i], &ret);
		if(ret != NULL)
		{
			for(int p = 0; p < 128; ++p)
			{
				count[p] += ((data *)ret)->count[p];
			}
			total += ((data *)ret)->total;
		}
		free(ret);
	}
	/*
	data *dat[tot_files];
	for(int i = 0; i < tot_files; ++i)
	{
		dat[i] = (data *)find(argv[i + 1]);
		for(int p = 0; p < 128; ++p)
		{
			count[p] += dat[i]->count[p];
		}
		total += dat[i]->total;
	}

	for(int i = 0; i < tot_files; ++i)
	{
		free(dat[i]);
	}
	/**/
	time(&end);
	diff_time = difftime(end, start);
	for(int i = 0; i < 128; ++i)
	{
		printf("%d = %llu\n", i, count[i]);
	}
	printf("Total: %llu\tTime: %.3f\n", total, diff_time);
	return 0;
}
