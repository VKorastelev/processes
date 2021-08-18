#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

static int iglob = 1;

int get_e(pid_t pid);

int main()
{
    int errsv = 0;
    pid_t pid, ret_pid;
    int wstatus = 0;

    int num_proc = 0;
   
    printf("Process main() PID = %d (parent %d)\n\n",
            getpid(),
            getppid());

    switch (pid = fork())
    {
        case -1:
        {
            errsv = errno;
            perror("Error in fork()");
            printf("errno = %d\n", errsv);
            exit(EXIT_FAILURE);
        }
        case 0:
        {
            printf("pid = %d. Child process PID = %d, parent process PPID = %d\n",
                    pid,
                    getpid(),
                    getppid());

            num_proc = getpid();
            iglob += 15;

            get_e(num_proc);

            break;
        }
        default:
        {
            printf("pid = %d. Parent process PID = %d, parent process PPID = %d\n",
                    pid,
                    getpid(),
                    getppid());
            
            num_proc = getpid();
            iglob += 2;
            
            ret_pid = wait(&wstatus);

            if (-1 == ret_pid)
            {
                errsv = errno;
                perror("Error in wait");
                printf("errno = %d\n", errsv);
                exit(EXIT_FAILURE);
            }
            
            if (WIFEXITED(wstatus))
            {
                printf("Child pid = %d exited, WEXITSTATUS(wstatus) = %d\n",
                        pid,
                        WEXITSTATUS(wstatus));
            }
            else
            {
                printf("Child pid = %d exited, not WEXITSTATUS\n", pid);
            }

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
    printf("exit from switch PID = %d num_proc = %d iglob = %d\n",
            getpid(),
            num_proc,
            iglob);

    return 0;
}

int get_e(pid_t pid)
{
    int ch;

    printf("Click 'e' to exit the process PID = %d:", pid);

    do
    {
        ch = getchar();
    }
    while ('e' != ch && EOF != ch);

    if (EOF == ch)
    {
        puts("\nВвод из stdin прекращен (ввели EOF)\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
