#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    fputs("--prog1 child starts--\n",stdout);
    printf("pid = %d\nppid = %d\n", getpid(), getppid());

    const char *name = getenv("MY_ENV_VAR1");
    printf("MY_ENV_VAR1 = %s\n", name);
    name = getenv("MY_ENV_VAR2");
    printf("MY_ENV_VAR2 = %s\n", name);


    for(int i = 0; i < argc; i++)
    {
        printf("Argument child №%d: %s\n", i, argv[i]);
        sleep(1);
    }

    fputs("--prog1 ends--\n",stdout);
    return 5;
}
