#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>


void* proc1(void* flag)
{
    fputs("--поток 1 начал работу--\n",stdout);
    int* flag1 = (int*)flag;
    while(*flag1)
    {
        printf("1\n");
        sleep(1);

    }
    fputs("--поток 1 закончил работу--\n",stdout);
    pthread_exit((void*)1);
}

void* proc2(void* flag)
{
    fputs("--поток 2 начал работу--\n",stdout);
    int* flag2 = (int*)flag;
    while(*flag2)
    {
        printf("2\n");
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

    if(pthread_create(&id1, NULL, proc1, &flag1) != 0)
    {
        perror("error creating thread1");
        return 0;
    }
    if(pthread_create(&id2, NULL, proc2, &flag2) != 0)
    {
        perror("error creating thread2");
        return 0;
    }

    if(getchar())
    {
        flag1 = 0;
        flag2 = 0;
    }

    if((ret_val = pthread_join(id1, (void**)&exit_code1)) != 0)
    {
        printf("ошибка ожидания потока 1: %s\n", strerror(ret_val));
        return 0;
    }
    else
    {
        printf("Код возврата потока 1: %p\n", exit_code1);
    }

    if((ret_val = pthread_join(id2, (void**)&exit_code2)) != 0)
    {
        printf("ошибка ожидания потока 2: %s\n", strerror(ret_val));
        return 0;
    }
    else
    {
        printf("Код возврата потока 2: %p\n", exit_code2);
    }

    fputs("--программа закончила работу--\n", stdout);
    return 0;

}
