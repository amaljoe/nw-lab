//ftp_server
//Navaneeth Venu 44 S6CS2 MBT19CS084

#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("FTP: Server Program\n\n");
	char buffer[500] = "";
	int sskt = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr1, addr2;
	int addr2_size = sizeof(addr2);
	
	addr1.sin_family = AF_INET;
	addr1.sin_port =  3000;
	addr1.sin_addr.s_addr = INADDR_ANY;
	
	bind(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
	listen(sskt, 10);
	
	do{
		//ACCEPT REQUEST
		int cskt = accept(sskt, (struct sockaddr *) &addr2, (&addr2_size));
		//RECEIVE CONTENTS IN BUFFER
		recv(cskt, buffer, sizeof(buffer) , 0);
		
		printf("Client Request: %s\n", buffer);
		
		pid_t id = fork();
		
		//CHILD PROCESS
		if(id == 0)
		{
			if(strcmp(buffer,"stop") == 0)
				break;

			FILE *f = fopen(buffer,"r");
			if(f == NULL)
				send(cskt, "File Doesn't Exist", sizeof(buffer) , 0);
			else
			{
				fscanf(f, "%[^EOF]%*c", buffer);//SCAN WITH SPACES
				send(cskt, buffer, sizeof(buffer) , 0);
			}
			
			fclose(f);
			close(cskt);		
			break;
		}
		
		//FORK FAILED
		else if(id < 0)
		{
			printf("Fork Failed\n");
		}
		
		close(cskt);
		
	}while(strcmp(buffer,"stop"));
	
	close(sskt);
	
}
