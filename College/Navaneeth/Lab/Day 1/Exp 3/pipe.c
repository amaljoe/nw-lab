//Navaneeth Venu, 44, S6CS2
//MBT19CS084
//Exp 3

#include<stdio.h>
#include<unistd.h>

void main()
{

	FILE *fp;
	int ret1,ret2;
	char rdbuff[100],wrbuff[100],fname[20];
	int pipefd1[2],pipefd2[2];
	
	printf("\nEnter the fname:");
	scanf("%s",fname);
	
	//create pipes
	ret1=pipe(pipefd1);
	if(ret1<0)
	{
		printf("Pipe 1 creation failed!");
	}
	ret2=pipe(pipefd2);
	if(ret2<0)
	{
		printf("Pipe 2 creation failed!");
	}
	
	//fork
	pid_t pid=fork();
	
	//ifChild
	if(pid==0)
	{
		printf("\nChild Process Created!");
		
		sleep(3);
		
		close(pipefd1[1]);//stop pipe write of 1
		read(pipefd1[0],rdbuff,sizeof(rdbuff));//start pipe read of 1
		
		fp=fopen(rdbuff,"r");
		fgets(wrbuff,sizeof(wrbuff),fp);
		fclose(fp);
		
		printf("\n\nThe contents of the file read by child process:\n");
		printf("%s",wrbuff);
		close(pipefd2[0]);//stop pipe read of 2
		write(pipefd2[1],wrbuff,sizeof(wrbuff));//start pipe write of 2
	}
	//ifParent
	else if(pid>0)
	{
		printf("\nParent Process Created!");
		
		close(pipefd1[0]);//stop pipe read of 1
		write(pipefd1[1],fname,sizeof(fname));//start pipe write of 1

		printf("\n\nThe name of the file created by parent process: %s\n", fname);
		
		sleep(5);
		
		close(pipefd2[1]);//stop pipe write of 2
		read(pipefd2[0],rdbuff,sizeof(rdbuff));//start pipe read of 2
	}
	else
	{
		printf("\nFork failed!");
	}
}
