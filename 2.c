#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


typedef struct id_proc
{
    int parent;
    pid_t pid;
    pid_t ppid;
} id_proc;

struct id_proc tree_proc[6] = {
    {-1}, {0}, {1}, {0}, {3}, {3}
};

int main()
{
    int errsv = 0;
    pid_t pid;

    int num_proc = 0;
    int i = 0;
    
    tree_proc[0].pid = getpid();
    tree_proc[0].ppid = getppid();

    printf("Function main() PID = %d, PPID = %d\n", tree_proc[0].pid, tree_proc[0].ppid);

    errno = 0;

    pid = fork();
    pid = fork();
    
        switch (pid)
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
                printf("fork() pid = %d. Child process PID = %d, parent process PPID = "
                        "%d\n", pid, getpid(), getppid());
                num_proc = getpid();
                break;
            }
            default:
            {
                printf("fork() pid = %d. Parent process PID = %d, parent process PPID = "
                        "%d\n", pid, getpid(), getppid());
                num_proc = getpid();
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

        printf("exit from switch(pid = fork()) PID = %d  pid = %d  num_proc = %d\n",
                getpid(), pid, num_proc);
    
    return 0;
}

