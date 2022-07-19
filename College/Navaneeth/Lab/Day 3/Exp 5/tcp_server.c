#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>


void main()
{
	printf("Server Side\n");
	
	char buffer[50];
	int sockfd,newsocket;
	
	struct sockaddr_in addr1,addr2;
	
	//CREATE LOCAL ADDRESS
	addr1.sin_family=AF_INET; //IPv4 Internet protocols
	addr1.sin_addr.s_addr=INADDR_ANY;
	addr1.sin_port=3008;
	
	int s=sizeof(struct sockaddr_in);
	
	//CREATE A SOCKET (Communication endpoint)
	sockfd=socket(AF_INET,SOCK_STREAM,0); //
	//BIND SOCKET (Bind name to a socket)
	bind(sockfd,(struct sockaddr*)&addr1,sizeof(addr1));
	//LISTEN FOR REQUESTS
	listen(sockfd,5);
	//ACCEPT REQUEST
	newsocket=accept(sockfd,(struct sockaddr*)&addr2,(&s));
	
	do
	{
	     printf("\nConnection Established.\n");
	     printf("\nRecieving message from Client:\n");
	     
	     //RECIEVE MESSAGE (from socket)
	     recv(newsocket,buffer,sizeof(buffer),0);
	     printf("%s",buffer);
	     
	     printf("Enter a message to send to Client:\n");
	     scanf("%s",buffer);
	     
	     //SEND A MESSAGE (on Socket)    
	     send(newsocket,buffer,sizeof(buffer),0);

	}
	while(strcmp(buffer,"stop")!=0);
	
	close(newsocket);
	close(sockfd);
}     
	     
	     
	     
