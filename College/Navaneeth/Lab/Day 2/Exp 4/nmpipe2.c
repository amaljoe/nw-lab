//Navaneeth Venu, 44, S6CS2
//MBT19CS084
//Exp 4-2

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<ctype.h>

void main()
{

		printf("\n Process 2\n");
		int fd,fd1,i,let=0,sp=0,line=1,vow=0;
		
		mkfifo("f.txt",0666);
		
		char recvv[50],recv[50];
		
		fd=open("f.txt",O_RDONLY);
		read(fd,recv, sizeof(recv));
		
		printf("\n recieved content: %s",recv);
		close(fd);
		
		fd1=open("f1.txt",O_WRONLY);
		
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
		
		printf("\n Calculated \n Sending.. \n");
		sprintf(recvv,"Line %d \n Words %d \n Characters %d \n Vowels %d \n",line,sp,let,vow);
		//printf("\n Line: %d \n Words: %d \n Characters: %d \n Vowels: %d \n",line,sp,let,vow);
		
		write(fd1,recvv,sizeof(recvv)+1);
		close(fd1);

}

/*O/P:

 recieved content: im testing.
 Calculated 
 Sending..*/


