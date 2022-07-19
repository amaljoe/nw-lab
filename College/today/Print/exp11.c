// Amal Joe R S, Roll No. 64, CS2
// Experiment 11

// CLIENT 1
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("FTP: Client Program 1..\n");
	char buffer[500] = "";
	char fileName[40];
	do {
		int sskt = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in addr1;
		addr1.sin_family = AF_INET;
		addr1.sin_port =  3000;
		addr1.sin_addr.s_addr = INADDR_ANY;
		int errno = connect(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
		if(errno == -1) {
			perror("ERROR");
			return;
		}
		printf("\nEnter filename:");
		scanf("%s", fileName);
		send(sskt, fileName, sizeof(fileName), 0);
		recv(sskt, buffer, sizeof(buffer), 0);
		printf("Server Response:\n%s", buffer);
		if(strcmp(buffer,"File Doesn't Exist") != 0) {
			char writeFilePath[100] = "client1/";
			strcat(writeFilePath,fileName);
			printf("\nWriting response to file: %s", writeFilePath);
			FILE *f = fopen(writeFilePath,"w");
			fprintf(f,"%s",buffer);
			fclose(f);
		}
		printf("\n");
		close(sskt);
	} while(strcmp(buffer,"stop"));
}

/*
OUTPUT
FTP: Client Program 1..

Enter filename:hello.txt
Server Response:
hey

Writing response to file: client1/hello.txt

Enter filename:hey.txt
Server Response:
File Doesn't Exist
*/

// CLIENT 2
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("FTP: Client Program 2..\n");
	char buffer[500] = "";
	char fileName[40];
	do{
		int sskt = socket(AF_INET, SOCK_STREAM, 0);
		struct sockaddr_in addr1;
		addr1.sin_family = AF_INET;
		addr1.sin_port =  3000;
		addr1.sin_addr.s_addr = INADDR_ANY;
		int errno = connect(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
		if(errno == -1) {
			perror("ERROR");
			return;
		}
		printf("\nEnter filename:");
		scanf("%s", fileName);
		send(sskt, fileName, sizeof(fileName), 0);
		recv(sskt, buffer, sizeof(buffer), 0);
		printf("Server Response:\n%s", buffer);
		if(strcmp(buffer,"File Doesn't Exist") != 0) { 
			char writeFilePath[100] = "client2/";
			strcat(writeFilePath,fileName);
			printf("\nWriting response to file: %s", writeFilePath);
			FILE *f = fopen(writeFilePath,"w");
			fprintf(f,"%s",buffer);
			fclose(f);
		}
		printf("\n");
		close(sskt);
	} while(strcmp(buffer,"stop"));
}

/*
FTP: Client Program 2..

Enter filename:hello.txt
Server Response:
hey

Writing response to file: client2/hello.txt

Enter filename:hey.txt
Server Response:
File Doesn't Exist
*/

// SERVER
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("FTP: Server Program..\n\n");
	char buffer[500] = "";
	int sskt = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr1, addr2;
	int addr2_size = sizeof(addr2);
	addr1.sin_family = AF_INET;
	addr1.sin_port =  3000;
	addr1.sin_addr.s_addr = INADDR_ANY;
	bind(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
	listen(sskt, 10);
	do {
		int cskt = accept(sskt, (struct sockaddr *) &addr2, (&addr2_size));
		recv(cskt, buffer, sizeof(buffer) , 0);
		printf("Client Request: %s\n", buffer);
		pid_t id = fork();
		if(id == 0)
		{
			if(strcmp(buffer,"stop") == 0) break;
			FILE *f = fopen(buffer,"r");
			if(f == NULL) send(cskt, "File Doesn't Exist", sizeof(buffer) , 0);
			else {
				fscanf(f, "%[^EOF]%*c", buffer);
				send(cskt, buffer, sizeof(buffer) , 0);
			}
			fclose(f);
			close(cskt);		
			break;
		}
		else if(id < 0) {
			printf("Fork Failed\n");
		}
		close(cskt);	
	} while(strcmp(buffer,"stop"));
	close(sskt);
}

/*
OUTPUT
FTP: Server Program..

Client Request: hello.txt
*/
