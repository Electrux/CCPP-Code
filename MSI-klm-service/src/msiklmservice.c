#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

int main()
{
	pid_t pid;

	pid = fork();
	
	if(pid < 0) exit(0);		//Kill because it failed.
	else if(pid != 0)
	{
		printf("Killing parent...\n");
		exit(0);	//Kill parent.
	}
	else if(pid == 0)
	{
		FILE *file;
		file = fopen("/etc/msi-klm/config.ini", "r");

		char data[200];

		fgets(data, sizeof(data), file);

		fclose(file);

		char str[400];

		strcpy(str, "sudo msiklm ");

		strcat(str, data);
		while(1)
		{	
			system(str);
			sleep(60);
		}
	}

	return 0;
}
