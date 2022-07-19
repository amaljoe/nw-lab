#include <stdio.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

void main()
{
    printf("Client side\n");
    char buffer[50];
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr1, addr2;
    addr2.sin_family = AF_INET;
    addr2.sin_addr.s_addr = INADDR_ANY;
    addr2.sin_port = 3008;
    connect(sockfd, (struct sockaddr *)&addr2, sizeof(addr2));

    do
    {

        printf("Sending messages to server\n");
        scanf("%s", buffer);
        send(sockfd, buffer, sizeof(buffer), 0);
        recv(sockfd, buffer, sizeof(buffer), 0);

        printf("Recieving from server %s\n", buffer);

    } while (strcmp(buffer, "stop") != 0);

    close(sockfd);
}
