#include<stdlib.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>
#include<fcntl.h>
#include<time.h>

int sock_to_connect_serv( char *IP, char *port );
int main(int argc, char *argv[] )
{
	int sock, rc, wc, i;
	char *temp = malloc(sizeof(char)*1000), input[2][100];
	FILE *fp = fopen("set.txt", "r");
	
	if(argv[1] == NULL || argv[2] == NULL )
	{
		printf("Usage: ./<appname> <server ip> <server port>\n");
		exit(EXIT_FAILURE);
	}
	
	i=0;
	while( EOF != fscanf( fp, "%s", input[i] ) )
	{
		printf("%s\n", input[i] );
		sprintf(input[i], "%s\n", input[i] );
		i++;
	} sleep(5);	
	
	sock = sock_to_connect_serv( argv[1], argv[2] );
	
	int val = fcntl(sock, F_GETFL, 0), hello = 0, n;
	fcntl(sock, F_SETFL, val | O_NONBLOCK);
	while(1)
	{
		if( ( n = read(sock, temp, 999) ) > 0 )
		{	
			printf("%s\n",temp);
		}
		if( hello == 0 )
		{
			char to_serv_msg[1000];
			snprintf( to_serv_msg, sizeof(to_serv_msg), "Hello server!\n" );
			write(sock, to_serv_msg, strlen(to_serv_msg) );
			bzero(to_serv_msg, 1000);
			strcpy( to_serv_msg, input[0] );
			write(sock, to_serv_msg, strlen(to_serv_msg) );
			bzero(to_serv_msg, 1000);
			strcpy( to_serv_msg, input[1] );
			write(sock, to_serv_msg, strlen(to_serv_msg) );	
			bzero(to_serv_msg, 1000);
			fprintf(stdout, "Finish write set to server\n");
			hello = 1;
		}
		if(strstr( temp, "Disconnect") != NULL)
		{	
			bzero(temp, 999);
			char clsConMsg[40];
			snprintf(clsConMsg, sizeof(clsConMsg), "Client disconnect\n");
			write(sock, clsConMsg, strlen(clsConMsg));
			printf("Close connection\n");
			close(sock);
			break;
		}
	}
	printf("Shutting down client...\n");
	return 0;
}

int sock_to_connect_serv( char *IP, char *port )
{
	int sock;
	struct sockaddr_in server;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		fprintf(stderr, "Could not create socket.\n");
		exit(EXIT_FAILURE);
	}
	else 
	{	fprintf(stdout, "Socket created,\n");	}
	
	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_family = AF_INET;
	server.sin_port = htons((u_short)atoi(port));

	if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		fprintf(stderr, "Connect failed, error.\n");
		exit(EXIT_FAILURE);
	}
	else
	{	fprintf(stdout, "Conneted to server.\n");	}
	
	return sock;
}




