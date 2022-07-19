#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
void main()
{
printf("\n process 2 \n");
int fd,fd1,i,let=0,sp=0,line=0,vow=0;
mkfifo("f.txt",0666);
char send[50],recv[50];
fd=open("f.txt",0666);
read(fd,recv,sizeof(recv));
printf("\n recieved content: %s",recv);
close(fd);
fd1=open("f1.txt",0666);
for(i=0;i<strlen(recv);i++)
{
 if(isblank(recv[i]))
    sp++;
  if(isalnum(recv[i]))
 {
    let++;
    if(recv[i]=='a'|| recv[i]=='e'|| recv[i]== 'i'|| recv[i]=='o'|| recv[i]== 'u')
    {

     vow++;
    }
 }
 if(recv[i]=='.')
{
line++;
sp++;
}
}
printf("\n calculated \n sending.. \n");
printf("\n line %d \n word %d \n characters %d \n vowels %d \n",line,sp,let,vow);
write(fd1,send,strlen(send)+1);
close(fd1);

}


