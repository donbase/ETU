#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>




int main(int argc, char *argv[])
{
    fputs("--Father prog starts--\n", stdout);
    int rv;
    int status;

    for(int i = 0; i < argc; i++)
    {
        printf("Argument parent №%d: %s\n", i, argv[i]);
        sleep(1);
    }

    pid_t pid = fork();
    if(pid == 0)
    {
        char *env_list[] = {"MY_ENV_VAR1=HELLO!", "MY_ENV_VAR2=DANIS", NULL};
        rv = execle("prog1", "prog1", "ARG1", "ARG2", NULL, env_list);
        if(rv == -1)
        {
            perror("execle");
            return 0;
        }

    }
    else if(pid > 0)
    {
        printf("pid = %d\nparent pid(ppid) = %d\nchild pid = %d\n", getpid(), getppid(), pid);
        while((rv = waitpid(pid, &status, WNOHANG)) == 0)
        {
            usleep(500);
        }

        if(rv == -1)
        {
            perror("waitpid");
            return 0;
        }
        else
        {
            printf("Child process ended with code: %d\n", WEXITSTATUS(status));
        }
    }
    else
    {
        perror("fork");
        return 0;
    }



    fputs("--Father prog ends--\n", stdout);
    return 0;
}
