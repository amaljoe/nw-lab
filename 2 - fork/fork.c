#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 50

int main()
{
    int n, arr[MAX];
    printf("Enter n:\n");
    scanf("%d", &n);
    printf("Enter elements of array:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
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
        wait(NULL);
        printf("Ascending order(from parent process):\n");
        for (int i = 0; i < n; i++)
        {
            printf("%d, ", arr[i]);
        }
        printf("\n");
        return 0;
    }
    else
    {
        // child process
        printf("Descending order(from child process):\n");
        for (int i = n - 1; i >= 0; i--)
        {
            printf("%d, ", arr[i]);
        }
        printf("\n");
        return 0;
    }
}