#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
void main()
{
printf("\n process 1 \n");
mkfifo("f.txt",0666);
int fd;
char send[50];
fd=open("f.txt",0666);
scanf("%s",send);
getchar();
write(fd,send,strlen(send)+1);
close(fd);
}







































