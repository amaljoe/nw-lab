// Amal Joe R S, Roll No. 64, CS2
// Experiment 8

// CLIENT
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	printf("DNS LOOKUP..\n");
	printf("Client Program..\n");
	char domain[45] = "";
	char recieve[60] = "";
	int sskt =  socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	addr.sin_family = AF_INET;
	addr.sin_port =  3002;
	addr.sin_addr.s_addr = INADDR_ANY;
	while(1)
	{
		printf("\nEnter a site address: ");
		scanf("%[^\n]%*c", domain);
		sendto(sskt, domain, sizeof(domain), 0, (struct sockaddr *) &addr, sizeof(addr));
		recvfrom(sskt, recieve, sizeof(recieve), 0, (struct sockaddr *) &addr, &addrlen);
		printf("IP: %s\n", recieve);
	}
}

/*
OUPUT

DNS LOOKUP..
Client Program..

Enter a site address: www.google.com
IP: 196.178.3.45

Enter a site address: www.facebook.com
IP: 167.53.45.12

Enter a site address: www.stackoverflow.com
IP: NO IP FOUND
*/


// SERVER
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


void main()
{
	printf("DNS LOOKUP..\n");
	printf("Server Program..\n");
	char recievedDomain[45] = "", ip[40], domain[40], defaultMessage[] = "NO IP FOUND";
	FILE *f;
	int sskt =  socket(AF_INET, SOCK_DGRAM, 0), found;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port =  3002;
	addr.sin_addr.s_addr = INADDR_ANY;
	int addrlen = sizeof(addr);
	bind(sskt,(struct sockaddr *) &addr, sizeof(addr));
	while(1)
	{
		recvfrom(sskt, recievedDomain, sizeof(recievedDomain) , 0, (struct sockaddr *) &addr, &addrlen);
		printf("Client DNS Request: %s\n", recievedDomain);
		f = fopen("dns.txt","r");
		found = 0;	
		while(fscanf(f,"%s%s", domain, ip) != EOF) {
			if(strcasecmp(domain, recievedDomain) == 0) {
				found = 1;
				sendto(sskt, ip, sizeof(ip), 0, (struct sockaddr *) &addr, sizeof(addr));
				break;
			}
		}
		if(found == 0) {
			sendto(sskt, defaultMessage, sizeof(defaultMessage) , 0, (struct sockaddr *) &addr, sizeof(addr));
		}
		fclose(f);
	}
}

/*
OUTPUT

DNS LOOKUP..
Server Program..
Client DNS Request: www.google.com
Client DNS Request: www.facebook.com
Client DNS Request: www.stackoverflow.com
*/

/*
DNS.txt

www.google.com	196.178.3.45
www.facebook.com	167.53.45.12
www.gmail.com	120.52.88.12
*/
