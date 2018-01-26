#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#define BUFLEN 4096

char *my_itoa(int num, char *str)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}


int main(int argc, char *argv[]) 
{
	int k=0;
	char *partaddr;
	char * netaddr[4];
	char netname[BUFLEN];
	FILE * fp;
	char cmd[100]={};
	int i=0;
	char sym;
	char buf[BUFLEN];

	if (argc < 2) { 
		return 1;
	} else  {	
		//netaddr=argv[1];
		partaddr = strtok (argv[1],"."); // 
		
		while (partaddr != NULL) {
			netaddr[i] = partaddr;
 			partaddr = strtok (NULL,".");
			i++;
		}	
 		for (k=1; k<=254; k++){
		char nod[4];
		my_itoa(k,nod);
		memset(cmd,0,100);
		strcat(cmd,"nmblookup ");
		strcat(cmd,"-A ");
		strcat(cmd,netaddr[0]);
		strcat(cmd,".");
		strcat(cmd,netaddr[1]);
		strcat(cmd,".");
		strcat(cmd,netaddr[2]);
		strcat(cmd,".");

		strcat(cmd,nod);


		
		fp=popen(cmd, "r");
		if (fp==NULL) {
		exit(1);
		} else {
				fscanf(fp,"%*s%*s%*s%*s%*s%s",netname);
				
				if (strcmp(netname, "No") != 0) {
					printf("%s.%s.%s.%s - ",netaddr[0],netaddr[1],netaddr[2],nod);
					printf ("%s\n",netname);
				}

		pclose(fp);
			}

	}
}

	return 0;
}
