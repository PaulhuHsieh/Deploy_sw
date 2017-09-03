#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define SWNUM 20

int main()
{
	char input[1000];
	char *DTIP = "192.168.1.30", *port_inc_str, *port_str;
	char pa_str[100];
	char *pa_bool ;
	
	FILE *fp = fopen("netstat_fn_test.txt", "r");
	sprintf( pa_str, "%s:", DTIP);

	while( fgets( input, sizeof(input) , fp ) )
	{	// printf("input = %s", input );
	
		port_inc_str = strtok( input, " " );
		while( port_inc_str != NULL )
		{
			if( strstr( port_inc_str, pa_str) != NULL )
				break;
			else
				port_inc_str = strtok( NULL, " " );
		}	// printf("%s\n", port_inc_str );
		
		port_str = strtok( port_inc_str, ":" );
		port_str = strtok( NULL, ":" );
		printf("port = %s\n", port_str );
	}
	fclose(fp);
}
