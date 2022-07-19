//Navaneeth Venu, 44, S6CS2
//MBT19CS084
//Exp 2

#include<stdio.h>
#include<unistd.h>

void bubbleSort(int a[], int n);

void main()
{
	int a[5],n=0;
	printf("Enter Size of Array\n");
	scanf("%d",&n);
	printf("Enter Array\n");
	for(int i=0;i<n;++i)
	{
		scanf("%d",&a[i]);
	}
	bubbleSort(a,n);
	pid_t pid = fork();
	if(pid<0)
	{
		printf("Fork Failed\n");
	}
	else if(pid==0)
	{
		printf("\nChild Process: %d | Sorted Array (Desc):\n",pid);
		for(int i=n-1;i>=0;--i)
		{
			printf("%d ",a[i]);
		}
	}
	else
	{
		printf("\nParent Process: %d | Sorted Array (Asc):\n",pid);
		for(int i=0;i<n;++i)
		{
			printf("%d ",a[i]);
		}
	}
}

void bubbleSort(int a[], int n)
{
	int temp=0;
	for(int i=0;i<n-1;++i)
	{
		for(int j=i;j<n-i-1;++j)
		{
			if(a[j]>a[j+1])
			{
				temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
	}
}
