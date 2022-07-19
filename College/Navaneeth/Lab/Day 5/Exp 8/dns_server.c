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
	printf("Sever Program\n");
	
	//CREATE FILE POINTER
	FILE *fp;
	
	struct sockaddr_in server, client;
	int s_skt,addrlen;
	char b_receive[100],b_temp[100],b_send[100];
	
	//CREATE SOCKET
	s_skt= socket(AF_INET,SOCK_DGRAM,0);
	
	//CREATE LOCAL ADDRESS
	client.sin_family=AF_INET;
	client.sin_addr.s_addr=INADDR_ANY;
	client.sin_port=3003;
	
	//BIND NAME TO SOCKET
	bind(s_skt,(struct sockaddr*)&client, sizeof(client));
	addrlen=sizeof(client);
	
	while(1)
	{
		strcpy(b_send,"");
		strcpy(b_temp,"");

		
		//OPEN DNS FILE
		fp = fopen("dns.txt","r");
		
		//RECEIVE FROM SOCKET AND DISPLAY
		recvfrom(s_skt,b_receive,sizeof(b_receive),0,(struct sockaddr*)&client,&addrlen);
		printf("Client DNS Request: %s\n", b_receive);
		
		while(!feof(fp)) //FEOF RETURNS NON ZERO AT END OF FILE
		{
			fscanf(fp,"%s",b_temp);
			if(strcmp(b_temp,b_receive)==0)
			{
				fscanf(fp,"%s",b_send);
				break;
			}
		}
	
		
		//REPLACE MESSAGE BY DEFAULT VALUE
		if(strcmp(b_send,"")==0)
		{
			strcpy(b_send,"IP Not Found\n");
		}
		else
		{
			strcat(b_send,"\n");//APPENDING NEWLINE
		}
		
		
		//CLOSE FILE
		fclose(fp);
		
		//SEND TO SOCKET
		sendto(s_skt,b_send,sizeof(b_send),0,(struct sockaddr*)&client, addrlen);
	}
}
