#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
void main()
{
	printf("Client Side\n");
	
	char buffer[50];
	int sockfd;
	
	struct sockaddr_in addr1,addr2;
	
	
	//CREATE LOCAL ADDRESS
	addr2.sin_family=AF_INET;
	addr2.sin_addr.s_addr=INADDR_ANY;
	addr2.sin_port=3008;
	
	//CREATE A SOCKET (Communication endpoint)
	sockfd=socket(AF_INET,SOCK_STREAM,0);
		
	connect(sockfd,(struct sockaddr *)&addr2,sizeof(addr2));

	do
	{
		printf("\nEnter message to send to Server\n");
		scanf("%s",buffer);
		send(sockfd,buffer,sizeof(buffer),0);
		printf("\nMessage sent to Server\n");
		recv(sockfd,buffer,sizeof(buffer),0);
		printf("\nRecieved from Server : %s\n",buffer);
	}
	while(strcmp(buffer,"stop")!=0);
	
	close(sockfd);
}	
