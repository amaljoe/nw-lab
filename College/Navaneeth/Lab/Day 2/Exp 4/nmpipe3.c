//Navaneeth Venu, 44, S6CS2
//MBT19CS084
//Exp 4-3

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>

void main()
{
		printf("\n Process 3\n");
		int fd1;
		char recvv[50];
		fd1=open("f1.txt",O_RDONLY);
		read(fd1,recvv,sizeof(recvv));
		close(fd1);
		puts(recvv);

}


/*O/P:

 recieved content: im testing.
 Calculated 
 Sending..
 */
