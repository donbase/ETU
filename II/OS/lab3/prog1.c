#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int pipefd[2];

void* proc1(void* flag)
{
    fputs("--поток 1 начал работу--\n",stdout);

    char buf[16];
    int* flag1 = (int*)flag;
    int count = 0;
    while(*flag1)
    {
        getdomainname(buf, 16);
        if(write(pipefd[1], buf, 16) == -1)
        {
            perror("ошибка записи канала");
            exit(0);
        }
        else
        {
            printf("write %d) %s\n ", count, buf);
            count++;
        }
        sleep(1);
    }
    fputs("--поток 1 закончил работу--\n",stdout);
    pthread_exit((void*)1);
}

void* proc2(void* flag)
{
    fputs("--поток 2 начал работу--\n",stdout);
    char buf[16];
    int* flag2 = (int*)flag;
    int count = 0;
    while(*flag2)
    {
        memset(buf, 0, sizeof(buf));
        if(read(pipefd[0], buf, 16) == -1)
        {
            perror("ошибка чтения канала");
            exit(0);
        }
        else
        {
            printf("read %d) ",count);
            printf("%s\n", buf);
            count++;
        }
        sleep(1);
    }
    fputs("--поток 2 закончил работу--\n",stdout);
    pthread_exit((void*)2);
}


int main()
{
    fputs("--программа начала работу--\n",stdout);
    int flag1 = 1;
    int flag2 = 1;

    pthread_t id1, id2;
    int ret_val;
    int* exit_code1;
    int* exit_code2;

    int ret;

    if(pipe(pipefd) == -1)
    {
        perror("ошибка создание канала");
        return 0;
    }


    if((ret = pthread_create(&id1, NULL, proc1, &flag1)) != 0)
    {
        printf("ошибка создания потока 1: %s\n", strerror(ret));
        return 0;
    }
    if(ret = (pthread_create(&id2, NULL, proc2, &flag2)) != 0)
    {
        printf("ошибка создания потока 2: %s\n", strerror(ret));
        return 0;
    }

    if(getchar())
    {
        flag1 = 0;
        flag2 = 0;
    }

    if((ret_val = pthread_join(id1, (void**)&exit_code1)) != 0)
    {
        printf("ошибка ожидания завершения потока 1: %s\n", strerror(ret_val));
        return 0;
    }
    else
    {
        printf("Код возврата потока 1: %p\n", exit_code1);
    }

    if((ret_val = pthread_join(id2, (void**)&exit_code2)) != 0)
    {
        printf("ошибка ожидания завершения потока 2: %s\n", strerror(ret_val));
        return 0;
    }
    else
    {
        printf("Код возврата потока 2: %p\n", exit_code2);
    }

    if(close(pipefd[0]) == -1)
    {
        perror("ошибка закрытия канала чтения");
        return 0;
    }
    if(close(pipefd[1] == -1))
    {
        perror("ошибка закрытия канала записи");
        return 0;
    }
    fputs("--программа закончила работу--\n", stdout);
    return 0;

}
