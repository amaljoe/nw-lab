#include<stdio.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>

void main()
{
printf("Server side\n");
char buffer[50];
int sockfd,newsocket;
struct sockaddr_in addr1,addr2;
addr1.sin_family=AF_INET;
addr1.sin_addr.s_addr=INADDR_ANY;
addr1.sin_port=3008;
int s=sizeof(struct sockaddr_in);
sockfd=socket(AF_INET,SOCK_STREAM,0);
bind(sockfd,(struct sockaddr*)&addr1,sizeof(addr1));
listen(sockfd,5);
newsocket=accept(sockfd,(struct sockaddr*)&addr2,(&s));
printf("Sending and Recieving messages from server and client\n");
do
{
printf("Connection Establishment\n");
printf("Recieving messages from client\n");
recv(newsocket,buffer,sizeof(buffer),0);
printf("%s",buffer);
printf("ENTER MESSAGE\n");
send(newsocket,buffer,sizeof(buffer),0);
}while(strcmp(buffer,"stop")!=0);
close(newsocket);
close(sockfd);
}
