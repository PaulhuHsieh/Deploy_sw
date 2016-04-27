#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SWNUM 20
#define CTRLNUM 3

int main(int argc, char *argv[] )
{
	char *sw_ID[SWNUM] = {"s1001", "s1002", "s1003", "s1004", 
				"s2001", "s2002", "s2003", "s2004",
				"s2005", "s2006", "s2007", "s2008",
				"s3001", "s3002", "s3003", "s3004",
				"s3005", "s3006", "s3007", "s3008" };
	char *ctrl[CTRLNUM] = { "tcp:192.168.1.10:6633", "tcp:192.168.1.11:6633", "tcp:192.168.1.12:6633"};
	int sw_ctrl_port[4][SWNUM];
	char *sw_ctrl, input[1000];	

	FILE *rsetfp = fopen("set.txt", "r");

	int line=0, i=0;
	while( EOF !=  fscanf(rsetfp, "%s", input ) )
	{
		sw_ctrl = strtok( input, "," );
		while( sw_ctrl != NULL )
		{
			sw_ctrl_port[line][i] = atoi( sw_ctrl );
			i++;
			sw_ctrl = strtok( NULL, "," );
		}
		i=0;
		line+=2;
	}
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d ", sw_ctrl_port[1][i] );	
	printf("\n");
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d ", sw_ctrl_port[3][i] );	
	printf("\n");
	
	for( i = 0 ; i < SWNUM ; i++ )
	{
				
	}	

	return 0;
}
