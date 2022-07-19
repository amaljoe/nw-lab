//Navaneeth Venu, 44, S6CS2
//MBT19CS084
//Exp 4-1

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

void main()
{
	
		printf("\n Process 1 \n");
		
		//create named pipe
		mkfifo("f.txt",0666);
		
		int fd;
		char send[50];
		
		fd=open("f.txt",0666);
		
		//user input
		scanf("%[^\n]s",send);
		getchar();
		
		write(fd,send,sizeof(send)+1);//write send to fd
		close(fd);
	
}

/*O/P:

 Process 3
Line 1 
 Words 2 
 Characters 9 
 Vowels 3*/



