//Navaneeth Venu, 44, S6CS2

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>

void main()
{
	printf("DNS Lookup: \n");
	printf("Client Prgram\n");
	
	struct sockaddr_in server, client;
	int c_skt,addrlen;
	addrlen=sizeof(server);
	char b_send[100],b_recieve[100];
	
	c_skt = socket(AF_INET,SOCK_DGRAM,0);
	
	//CREATE LOCAL ADDRESS
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=INADDR_ANY;
	server.sin_port=3003;
	
	strcpy(b_send,"");
	while(1)
	{
		printf("\nEnter Cannonical Address: ");
		scanf("%s",b_send);
		sendto(c_skt,b_send,sizeof(b_send),0,(struct sockaddr*)&server,addrlen);
		recvfrom(c_skt,b_recieve,sizeof(b_recieve),0,NULL,NULL);
		printf("%s \n",b_recieve);
	
	}
}
