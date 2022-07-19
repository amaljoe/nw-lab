// Amal Joe R S, Roll No. 64, CS2
// Experiment 9

// CLIENT
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct {
	char to[45], from[45], sub[45], message[200];
} email;

void main() {
	printf("SMTP..\n");
	printf("Client Program..\n");
	char buffer[500] = "";
	int sskt = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr1;
	
	addr1.sin_family = AF_INET;
	addr1.sin_port =  3000;
	addr1.sin_addr.s_addr = INADDR_ANY;
	
	int errno = connect(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
	if(errno == -1) {
		printf("\nXXX Connection Failed XXX\n");
		return;
	}
	else {
		printf("\n*** Connection Established ***\n");
	}
	while(1) {	
		if(strcmp(email.to,"") == 0) {
			printf("\nEnter Reciepient Email:");
			scanf("%s", email.to);
		}
		printf("Enter Sender Email:");
		scanf("%s", email.from);
		printf("Enter Subject:");
		scanf("%s", email.sub);
		printf("Enter Message:");
		scanf("%s", email.message);
		send(sskt, email.to, sizeof(email.to) , 0);
		send(sskt, email.from, sizeof(email.from) , 0);
		send(sskt, email.sub, sizeof(email.sub) , 0);
		send(sskt, email.message, sizeof(email.message) , 0);
		recv(sskt, buffer, sizeof(buffer), 0);
		printf("\n\nDomain Name: %s\n\n", buffer);
	};
	
	close(sskt);
}

/*
OUTPUT

SMTP..
Client Program..

*** Connection Established ***

Enter Reciepient Email:amaljoe88@gmail.com
Enter Sender Email:amaljoe@accubits.com
Enter Subject:hello
Enter Message:goodmorning

Domain Name: gmail

Enter Sender Email:navaneeth@gmail.com
Enter Subject:hey
Enter Message:goodevening

Domain Name: gmail
*/


// SERVER
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

struct {
	char to[45], from[45], sub[45], message[200];
} email;

void main() {
	printf("SMTP..\n");
	printf("Server Program..\n");
	char buffer[500] = "", domainName[50] = "";
	int sskt = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in addr1, addr2;
	int addr2_size = sizeof(addr2);
	addr1.sin_family = AF_INET;
	addr1.sin_port =  3000;
	addr1.sin_addr.s_addr = INADDR_ANY;
	bind(sskt,(struct sockaddr *) &addr1, sizeof(addr1));
	listen(sskt, 5);
	int cskt = accept(sskt, (struct sockaddr *) &addr2, (&addr2_size));
	printf("\n*** Connection Established ***\n");
	while(1) {
		recv(cskt, email.to, sizeof(email.to) , 0);
		recv(cskt, email.from, sizeof(email.from) , 0);
		recv(cskt, email.sub, sizeof(email.sub) , 0);
		recv(cskt, email.message, sizeof(email.message) , 0);
		printf("\n\nClient Request Mail\nTo: %s\nFrom: %s\nSubject: %s\nMessage: %s\n", email.to, email.from, email.sub, email.message);
		char *domain = strrchr(email.to, '@');
		if(domain == NULL) {
			send(cskt, "INVALID TO ADDRESS", sizeof(buffer) , 0);
		}
		else {
			strcpy(buffer, domain);
			strcpy(buffer, index(buffer, buffer[1]));
			int len = -1;
			
			for(int i = 0; i < strlen(buffer); i++) {
				if(buffer[i] == '.') {
					len = i;
					break;
				}
			}
			if(len == -1) {
				send(cskt, "INVALID TO ADDRESS", sizeof(buffer) , 0);
			}
			else {
				strncpy(domainName, buffer, len);
				send(cskt, domainName, sizeof(domainName) , 0);
			}
		}
	}
	close(sskt);
	close(cskt);
}

/*
OUTPUT

SMTP..
Server Program..

*** Connection Established ***


Client Request Mail
To: amaljoe88@gmail.com
From: amaljoe@accubits.com
Subject: hello
Message: goodmorning


Client Request Mail
To: amaljoe88@gmail.com
From: navaneeth@gmail.com
Subject: hey
Message: goodevening
*/
