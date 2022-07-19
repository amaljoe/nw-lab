#include<stdio.h>
#include<limits.h>

#define N 20
#define inf 9000

struct Node
{
	int dist[N];
	int from[N];
}node[N];


void main()
{
	int cost[N][N], i, j, k, nodes, count = 0;
	printf("\nEnter no. of nodes:");
	scanf("%d",&nodes);
	printf("\nEnter cost matrix (use 0 for infinities): \n");
	for(i = 0; i < nodes; i++)
	{
		for(j = 0; j < nodes; j++)
		{
			scanf("%d",&cost[i][j]);
			
			if(i != j && cost[i][j] == 0)
				cost[i][j] = inf;
			
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
		printf("\n\nRouting Table for Node: %d\n", i+1);
		printf("%s | %s | %s\n", "To", "Next Hop", "Distance");
		printf("-----------------\n");
		
		for(j = 0; j < nodes; j++)
		{
			printf("%d | %d | %d\n", j+1, node[i].from[j] + 1, node[i].dist[j]);
		}
	}
	
	printf("\n\n");
	
}
