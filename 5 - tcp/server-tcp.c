#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#define MAX 50

int main()
{
    char buffer[MAX];
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = 3008;
    int len = sizeof(addr);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int b = bind(sockfd, (struct sockaddr *)&addr, len);
    listen(sockfd, 5);
    printf("Waiting for client...\n");
    int newsock = accept(sockfd, (struct sockaddr *)&addr, &len);
    printf("Client connected successfully!\n");
    while (1)
    {
        read(newsock, buffer, sizeof(buffer));
        printf("\n\nMessage from client: %s\n", buffer);
        if (strcmp(buffer, "stop") == 0)
            break;
        printf("Enter a reply: ");
        scanf("%s", buffer);
        if (strcmp(buffer, "stop") == 0)
            break;
        write(newsock, buffer, sizeof(buffer));
    }
    close(sockfd);
    close(newsock);
    return 0;
}