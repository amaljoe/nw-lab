//Navaneeth Venu, 44, S6CS2

#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

struct
{
	char to[45], from[45], sub[45], msg[200];
} email;

void main()
{
	printf("SMTP Program\nClient Side\n");
	
	char domain1[500], domain2[500];
	int sockfd;
	
	struct sockaddr_in client,server;
	
	
	//CREATE LOCAL ADDRESS
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3008;
	
	//CREATE A SOCKET (Communication endpoint)
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	//INITIATE SOCKETY CONNECTION AND TEST ERROR CONDITIONS
	int errno = connect(sockfd,(struct sockaddr *)&server,sizeof(server));
	if(errno == -1){
		printf("\nConnection Failed.\n");
		return;
	}
	else
		printf("\nConnection Established\n");
		


	while(1)
	{
		strcpy(email.to,"\n");
		strcpy(email.from,"\n");
		//GET FIELDS (TO AND FROM ARE MANDATORY)
		while(strcmp(email.to,"\n")==0)
		{
			printf("\nEnter Recipient Email:");
			scanf("%s", email.to);
		}
		
		while(strcmp(email.from,"\n")==0)
		{
			printf("Enter Sender Email:");
			scanf("%s", email.from);
		}
		
		printf("Enter Subject:");
		scanf("%s", email.sub);
		
		printf("Enter Message:");
		scanf("%s", email.msg);
		
		//printf("%s %s %s %s",email.to,email.from,email.sub,email.msg);
		
		send(sockfd,email.to,sizeof(email.to),0);
		send(sockfd,email.from,sizeof(email.from),0);
		send(sockfd,email.sub,sizeof(email.sub),0);
		send(sockfd,email.msg,sizeof(email.msg),0);
		
		//printf("%s %s %s %s",email.to,email.from,email.sub,email.msg);
		
		recv(sockfd, domain1, sizeof(domain1), 0);
		recv(sockfd, domain2, sizeof(domain2), 0);
		printf("\n\nDomain Name of Sender Address: %s\n", domain1);
		printf("\n\nDomain Name of Recipient Address: %s\n", domain2);
	}
	
	close(sockfd);
}	
