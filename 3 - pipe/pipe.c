#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

#define MAX 50

int main()
{
    int fd1[2], fd2[2];
    if (pipe(fd1) < 0)
    {
        if (errno != EEXIST)
        {
            printf("Pipe 1 creation failed\n");
            return 1;
        }
    }
    if (pipe(fd2) < 0)
    {
        if (errno != EEXIST)
        {
            printf("Pipe 2 creation failed\n");
            return 1;
        }
    }
    pid_t pid = fork();
    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid > 0)
    {
        // parent process
        char filename[MAX];
        printf("Enter filename:\n");
        scanf("%s", filename);
        close(fd1[0]);
        write(fd1[1], filename, sizeof(filename));
        close(fd1[1]);
        return 0;
    }
    else
    {
        char buf[MAX];
        // child process
        close(fd1[1]);
        read(fd1[0], buf, sizeof(buf));
        close(fd1[0]);
        printf("Filename: %s\n", buf);
        return 0;
    }
}