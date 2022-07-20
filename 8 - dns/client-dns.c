#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 50

int main()
{
    char buf[MAX];
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_family = AF_INET;
    addr.sin_port = 3008;
    int len = sizeof(addr);
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    while (1)
    {
        printf("\nEnter site address: ");
        scanf("%s", buf);
        sendto(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, len);
        recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &len);
        printf("Received from server: %s\n", buf);
    }
    return 0;
}