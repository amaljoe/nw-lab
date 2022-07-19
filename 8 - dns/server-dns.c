#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 50

int main()
{
    FILE *dns = fopen("dns.txt", "r");

    char buf[MAX];
    char site[MAX];
    char ip[MAX];
    char notfound[] = "IP not found";
    struct sockaddr_in addr;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = 3008;
    addr.sin_family = AF_INET;
    int len = sizeof(addr);
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    bind(sock, (struct sockaddr *)&addr, len);
    while (1)
    {
        recvfrom(sock, buf, sizeof(buf), 0, (struct sockaddr *)&addr, &len);
        printf("Client DNS request: %s\n", buf);
        int found = 0;
        while (fscanf(dns, "%s %s", site, ip) != EOF)
        {
            if (strcasecmp(buf, site) == 0)
            {
                found = 1;
                sendto(sock, ip, sizeof(ip), 0, (struct sockaddr *)&addr, len);
                break;
            }
            sendto(sock, ip, sizeof(ip), 0, (struct sockaddr *)&addr, len);
        }
        if (!found)
        {
            sendto(sock, notfound, sizeof(notfound), 0, (struct sockaddr *)&addr, len);
        }
    }
    return 0;
}