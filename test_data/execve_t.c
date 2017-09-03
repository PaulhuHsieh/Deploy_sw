#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>

int main()
{
	int i;
	char argv[3][100];
	sprintf(argv[0], "sudo");
	sprintf(argv[1], "./test.sh");
	sprintf(argv[2], "123");

	pid_t td_pid;
	td_pid = fork();
	if( td_pid < 0 )
	{
		fprintf(stderr, "Fork tcpdump error\n");
	}
	else if( td_pid == 0 )
	{
		fprintf(stderr, "tcpdump ports.\n");
		char * argv2[] = {"sudo", "./test.sh", "123", NULL};
		execve("/usr/bin/sudo", argv2, NULL );
	}
	else
	{
		wait(NULL);
		fprintf(stderr, "End of tcpdump\n");
	}
}
