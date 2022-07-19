#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
void main()
{

printf("\n process 3 \n");
int fd1;
char recvv[50];
fd1=open("f.txt",0666);
read(fd1,recvv,sizeof(recvv));
close(fd1);
puts(recvv);

}
