/*
	M ASWIN KISHORE
	41 S6 CS2
	EXP10 : Distance Vector Routing
*/

#include<stdio.h>
#include<limits.h>

#define N 20
#define INFINITY 10000

struct NODE
{
	int dist[N];
	int from[N];
}node[N];


void main()
{
	int cost[N][N], i, j, k, nodes, count = 0;
	printf("Enter the no. of nodes:");
	scanf("%d",&nodes);
	printf("Enter the cost matrix : \n");
	for(i = 0; i < nodes; i++)
	{
		for(j = 0; j < nodes; j++)
		{
			scanf("%d",&cost[i][j]);
			
			if(i != j && cost[i][j] == 0)
				cost[i][j] = INFINITY;
			
			node[i].dist[j] = cost[i][j];
			node[i].from[j] = j;
		}
	}
	
	do
	{
		count = 0;
		for(i = 0; i < nodes; i++)
		{
			for(j = 0 ; j < nodes; j++)
			{
				for(k = 0; k < nodes; k++)
				{
					if(node[i].dist[j] > cost[i][k] + node[k].dist[j])
					{
						node[i].dist[j] = node[i].dist[k] + node[k].dist[j];
						node[i].from[j] = k;
						count++;
					}
				}
			}
		}
	
	}while(count != 0);
	
	for(i = 0; i < nodes; i++)
	{
		printf("\n\nRouting Table for node: %d\n", i+1);
		printf("%-5s | %-10s | %-10s\n", "To", "Next Hop", "Distance");
		printf("--------------------------------------\n");
		
		for(j = 0; j < nodes; j++)
		{
			printf("%-5d | %-10d | %-10d\n", j+1, node[i].from[j] + 1, node[i].dist[j]);
		}
	}
	
	printf("\n\n");
	
}

/*
INPUT

4
0 2 3 0
2 0 1 3
3 1 0 4
0 3 4 0
*/

/*
OUTPUT

Enter the no. of nodes:4
Enter the cost matrix : 
0 2 3 0
2 0 1 3
3 1 0 4
0 3 4 0


Routing Table for node: 1
To    | Next Hop   | Distance  
--------------------------------------
1     | 1          | 0         
2     | 2          | 2         
3     | 3          | 3         
4     | 2          | 5         


Routing Table for node: 2
To    | Next Hop   | Distance  
--------------------------------------
1     | 1          | 2         
2     | 2          | 0         
3     | 3          | 1         
4     | 4          | 3         


Routing Table for node: 3
To    | Next Hop   | Distance  
--------------------------------------
1     | 1          | 3         
2     | 2          | 1         
3     | 3          | 0         
4     | 4          | 4         


Routing Table for node: 4
To    | Next Hop   | Distance  
--------------------------------------
1     | 2          | 5         
2     | 2          | 3         
3     | 3          | 4         
4     | 4          | 0  

*/
