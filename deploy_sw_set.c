#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<ctype.h>

#define SWNUM 20
#define CTRLNUM 3

char sw_ID[SWNUM][50], ctrl[CTRLNUM][50];
void exec_tcpdump(int sw_ctrl_port[][SWNUM]);
void implement_sw(int i, char *sw_ID_clone, char *ctrl_clone,  char *l2_ctrl_clone, int sw_ctrl_port[][SWNUM], int layer )
{
	int j; 
	int port;
	pid_t set_c1_pid, netstat_pid;

	set_c1_pid = fork();
	if ( set_c1_pid < 0 )
	{
		fprintf(stderr,"Error in set-controller\n");
	}
	else if ( set_c1_pid == 0 ) 
	{
		fprintf(stderr,"set-controller %d\n", i);
		if( layer == 1 )
		{
			char * argv2[] = {"ovs-vsctl", "set-controller", sw_ID_clone, ctrl_clone, 0 };	//fprintf(stderr ,"%s, %s\n", ctrl_clone, sw_ID_clone ); 
			execvp(argv2[0], argv2);
		}
		else if( layer == 3 )
		{
			char l1ctrl[100], l1sw_ID[100];
			char * argv2[] = {"ovs-vsctl", "set-controller", sw_ID_clone, ctrl_clone, l2_ctrl_clone, 0 };	//fprintf(stderr ,"%s, %s\n", ctrl_clone, sw_ID_clone ); 
			execvp(argv2[0], argv2);
		}
	}      
	else
	{
		wait(NULL);
		fprintf(stderr,"End of set-controller %d\n", i);

		netstat_pid = fork();
		if ( netstat_pid < 0 )
		{
			fprintf(stderr,"Error in netstat\n");
		}
		else if ( netstat_pid == 0 ) 
		{
			fprintf(stderr,"Netstat\n");
			char * argv2[] = {"python", "netstat.py", 0 };
			execvp(argv2[0], argv2);
		} 
		else
		{
			wait(NULL);
			fprintf(stderr,"Finish grep netstat\n");
			//sleep(1);
			char input[1000];
			char *DTIP = "192.168.1.30", *port_inc_str, *port_str;
			char *pa_bool ;
			int there_is_DTIP = 0;

			FILE *net_fp;
			net_fp = fopen("netstat.txt", "r");
			if( net_fp == NULL )
			{
				fprintf(stderr, "Open netstat.txt fail\n"); 
				exit(0);
			}
			while( fgets( input, sizeof(input) , net_fp ) )
			{									//printf("input = %s", input );
				
				//** Parse port from doc **
				port_inc_str = strtok( input, " " );
				while( port_inc_str != NULL )
				{
					if( strstr( port_inc_str, DTIP) != NULL )
					{			
						there_is_DTIP = 1;				//printf("%s find!\n", port_inc_str );
						break;
					}
					else
						port_inc_str = strtok( NULL, " " );
				}								// printf("%s\n", port_inc_str );
				if( there_is_DTIP == 1 )
				{
					there_is_DTIP = 0;
					port_str = strtok( port_inc_str, ":" );
					port_str = strtok( NULL, ":" );				// printf("port = %s\n", port_str );
					port = atoi( port_str );
					//** END of parsing **
				
					//** Compare result with table to see if recorded or not. If not, record. **
					int has_same = 0;
					for( j = 0 ; j < i ; j++ )
					{
						if( port == sw_ctrl_port[layer][j] )
						{
							has_same = 1;
							break;
						}
					}
					if( layer == 3 )
					{
						// additonal check layer 1
						for( j = 0 ; j < SWNUM ; j++ )
						{
							if( port == sw_ctrl_port[layer-2][j] )
							{
								has_same = 1;
								break;
							}
						}
					}
					if( has_same == 0 )
					{
						sw_ctrl_port[layer][i] = port;
						break;
					}
				}
				
			}
			fclose(net_fp);
			//** End of record sw's 1st connection port **
		}
	}
}

int main(int argc, char *argv[] )
{
	char input[1000];
	char *sw_ctrl, *temp;	
	int sw_ctrl_port[4][SWNUM];

	FILE *rsetfp = fopen("set.txt", "r"), *rctrl_fp = fopen("ctrl_set.txt", "r"), *rsw_fp = fopen("sw_set.txt", "r");

	int line=0, i=0, j=0;

	//** Import sw-ctrl sets  **
	while( EOF !=  fscanf(rsetfp, "%s", input ) )
	{
		sw_ctrl = strtok( input, "," );
		while( sw_ctrl != NULL )
		{
			sw_ctrl_port[line][i] = atoi( sw_ctrl );
			i++;
			sw_ctrl = strtok( NULL, "," );
		}
		bzero(input,999);
		i=0;
		line+=2;
	}
	//** END **

	//** Import ctrl info	
	i=0;
	while( EOF !=  fscanf(rctrl_fp, "%s", input ) )
	{
		strcpy( ctrl[i], input );	printf("%s ", ctrl[i]);
		bzero(input,999);
		i++;
	}					printf("\n");
	//** END **

	//** Import ctrl info	
	i=0;
	while( EOF !=  fscanf(rsw_fp, "%s", input ) )
	{
		strcpy( sw_ID[i], input );	printf("%s ", sw_ID[i]);
		bzero(input,999);
		i++;
	}					printf("\n");
	//** END **

	//** print set **
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d ", sw_ctrl_port[0][i] );	
	printf("\n");
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d ", sw_ctrl_port[2][i] );	
	printf("\n");
	//** END **

	
	//** Implement switch set **
	char sw_ID_clone[100], l1_ctrl_clone[100], l2_ctrl_clone[100];
	for( i = 0 ; i < SWNUM ; i++ )
	{	
		//** Set switch's 1st controller **
		strcpy( l1_ctrl_clone , ctrl[ sw_ctrl_port[0][i] - 1 ] ); // ** sw_ctrl mapping is 1,2,3 but array index is 0,1,2
		strcpy( sw_ID_clone, sw_ID[i] );
		implement_sw( i, sw_ID_clone, l1_ctrl_clone, "\0"  ,sw_ctrl_port, 1  );
		//** End of set sw[i]'s 1st controller **
	}

	for( i = 0 ; i < SWNUM ; i++ )
	{
		//** Set switch's 2nd controller ** 
		strcpy( l2_ctrl_clone , ctrl[ sw_ctrl_port[2][i] - 1 ] ); // ** sw_ctrl mapping is 1,2,3 but array index is 0,1,2
		strcpy( l1_ctrl_clone , ctrl[ sw_ctrl_port[0][i] - 1 ] ); // ** sw_ctrl mapping is 1,2,3 but array index is 0,1,2
		strcpy( sw_ID_clone, sw_ID[i] );
		implement_sw( i, sw_ID_clone, l1_ctrl_clone, l2_ctrl_clone, sw_ctrl_port, 3 );
		//** End of set sw[i]'s 2nd controller **		
	}
	//** End of set sws' controller **
	
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d\t", sw_ctrl_port[0][i] );
	printf("\n");
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d\t", sw_ctrl_port[1][i] );
	printf("\n");
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d\t", sw_ctrl_port[2][i] );
	printf("\n");
	for( i = 0 ; i < SWNUM ; i++ )
		printf("%d\t", sw_ctrl_port[3][i] );
	printf("\n");
	printf("done\n");

	exec_tcpdump(sw_ctrl_port);
	return 0;
}

void exec_tcpdump( int sw_ctrl_port[][SWNUM] )
{
	int i;
	char argv[SWNUM][100];
	

	sprintf(argv[0], "sudo");
	sprintf(argv[1], "./tcpdump.sh");
	for( i = 0 ; i < SWNUM+2 ; i++ )
	{
		 sprintf(argv[i+2], "%d", sw_ctrl_port[1][i]); 
	}

	//** Testing
	printf("In func\n");
	i=0;
	while( i < SWNUM+2 ) // argv[0] is file name
	{
		printf("%d %s\n", i, argv[i] );
		i++;
	}
	printf("\n");
	//** End of testing

	pid_t td_pid;
	td_pid = fork();
	if( td_pid < 0 )
	{
		fprintf(stderr, "Fork tcpdump error\n");
	}
	else if( td_pid == 0 )
	{
		fprintf(stderr, "tcpdump ports.\n");
		char * argv2[] = {argv[0], argv[1], argv[2], argv[3], argv[4], argv[5]
				, argv[6], argv[7], argv[8], argv[9], argv[10], argv[11]
				, argv[12], argv[13], argv[14], argv[15], argv[16], argv[17]
				, argv[18], argv[19], argv[20], argv[21], NULL};
		execve("/usr/bin/sudo", argv2, NULL );
	}
	else
	{
		wait(NULL);
		fprintf(stderr, "End of tcpdump\n");
	}
 
}








