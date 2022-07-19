#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 50

int main()
{
    char buffer[MAX];
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 3008;
    addr.sin_family = AF_INET;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    connect(sock, (struct sockaddr *)&addr, sizeof(addr));
    printf("Connected to server successfully!\n");
    while (1)
    {
        printf("\nEnter a message(or stop): ");
        scanf("%s", buffer);
        if (strcmp(buffer, "stop") == 0)
            break;
        write(sock, buffer, sizeof(buffer));
        read(sock, buffer, sizeof(buffer));
        if (strcmp(buffer, "stop") == 0)
            break;
        printf("Reply from server: %s\n", buffer);
    }
    close(sock);
    return 0;
}