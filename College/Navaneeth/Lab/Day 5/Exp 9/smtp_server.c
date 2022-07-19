#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

void validate(char mail[], char domainType[100], char domain[]);


struct
{
	char to[45], from[45], sub[45], message[200];
} email;

void main()
{
	printf("SMTP Program\nServer Side\n");
	
	char buffer[50], domain1[50]="", domain2[50]="";
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
	
	while(1)
	{
	     printf("\nConnection Established.\n");
	     
	     //RECIEVE FROM SOCKET
	     recv(newsocket, email.to, sizeof(email.to) , 0);
	     recv(newsocket, email.from, sizeof(email.from) , 0);
	     recv(newsocket, email.sub, sizeof(email.sub) , 0);
	     recv(newsocket, email.message, sizeof(email.message) , 0);
	     printf("\n\nClient Request Mail\nTo: %s\nFrom: %s\nSubject: %s\nMessage: %s\n", email.to, email.from, email.sub, email.message);
	     
	     
	     validate(email.to,"Sender",domain1);
	     send(newsocket, domain1, sizeof(domain1) , 0);
	     validate(email.from,"Receipient",domain2);
	     send(newsocket, domain2, sizeof(domain2) , 0);

	}
	
	close(newsocket);
	close(sockfd);
}

void validate(char mail[], char domainType[100], char domain[])
{

	int flag = 0, i=0,j=0;
	while(mail[i]!='\0')
	{
		if(flag==1)
		{
			domain[j]=mail[i];
			j++;
		}
		if(mail[i]=='@'&&flag==0)
		{
			flag=1;
		}
		i++;
		
	}
	domain[j]='\0';
	if((flag!=1)||(strcmp(domain,"")==0))
	{
		printf("Invalid %s Address\n",domainType);
		strcpy(domain,"Invalid");
	}

}   
	     
	     
	     
