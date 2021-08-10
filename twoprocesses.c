#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

static int iglob = 1;

int main()
{

    int errsv = 0;
    pid_t pid;

    int num_proc = 0;
    
    printf("Function main() PID = %d, PPID = %d\n", getpid(), getppid());

    errno = 0;

    switch (pid = fork())
    {
        case -1:
        {
            errsv = errno;
            perror("Error in fork");
            printf("errno = %d\n", errsv);
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            printf("fork() pid = %d. Child process PID = %d, parent process PPID = %d\n",
                    pid, getpid(), getppid());
            num_proc = getpid();
            iglob += 15;

            break;
        }
        default:
        {
            printf("fork() pid = %d. Parent process PID = %d, parent process PPID = %d\n",
                    pid, getpid(), getppid());
            num_proc = getpid();
            iglob += 5;
            
            sleep(5);

            break;
        }
    }
    
    if (0 == pid)
    {
        printf("Child ");
    }
    else
    {
        printf("Parent ");
    }
    printf("exit from switch(pid = fork()) PID = %d  pid = %d  num_proc = %d  iglob = "
            "%d\n", getpid(), pid, num_proc, iglob);

    return 0;
}

