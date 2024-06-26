#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <signal.h>
#define SIZE 64
#define LOCAL_DATA_SIZE 1024

sem_t *sem_write, *sem_read;
int  mem_id;
char *local_data;
key_t my_key;
pthread_t id1;
int* exit_code;

void* proc(void* flag)
{
    int* flag1 = (int*)flag;
    char buf[SIZE];
    while(*flag1)
    {
        if(getdomainname(buf, SIZE) == -1)
        {
            perror("\ngetdomainname");
            pthread_exit((void*)-1);
        }

        memcpy(local_data, buf, sizeof(buf));
        printf("write: %s\n", buf);

        if(sem_post(sem_write) == -1)
        {
            perror("\nsem_post proc(thread)");
            pthread_exit((void*)-1);
        }

        if(sem_wait(sem_read) == -1)
        {
            perror("\nsem_wait proc(thread)");
            pthread_exit((void*)-1);
        }
        sleep(1);
    }

    pthread_exit((void*)0);
}


void sig_handler(int signo)
{
    printf("\nget SIGINT; %d\n", signo);
    int ret;
    if((ret = pthread_join(id1, (void**)&exit_code)) != 0)
    {
        printf("sig_handler pthread_join: %s\n", strerror(ret));
    }

    if(shmdt(local_data) == -1)
    {
        perror("sig_handler shmdt");
    }

    if(shmctl(mem_id, IPC_RMID, NULL) == -1)
    {
        perror("sig_handler shmctl");
    }

    if(sem_close(sem_write) == -1)
    {
        perror("sig_handler sem_close write");
    }

    if(sem_close(sem_read) == -1)
    {
        perror("sig_handler sem_close read");
    }

    if(sem_unlink("/my_sem_read") == -1)
    {
        perror("sig_handler sem_unlink read");
    }


    if(sem_unlink("/my_sem_write") == -1)
    {
        perror("sig_handler sem_unlink write");
    }

    exit(0);
}


int main()
{
    signal(SIGINT, sig_handler);
    int ret;
//	setdomainname("some_name", 10); //execute with sudo

    if((sem_write = sem_open("/my_sem_write", O_CREAT, S_IRWXU, 0)) == SEM_FAILED)
    {
        perror("sem_open_write in main");
        return errno;
    }


    if((sem_read = sem_open("/my_sem_read", O_CREAT, S_IRWXU, 0)) == SEM_FAILED)
    {
        perror("sem_open_read in main");
        return errno;
    }


    int flag1 = 1;

    if((my_key = ftok("/tmp", 1)) == -1)
    {
        perror("ftok");
        return errno;
    }

    if((mem_id = shmget(my_key, LOCAL_DATA_SIZE, IPC_CREAT|0644)) == -1)
    {
        perror("shmget");
        return errno;
    }

    if((local_data = shmat(mem_id, NULL, 0)) == (char*)-1)
    {
        perror("shmat");
        return errno;
    }

    if((ret = pthread_create(&id1, NULL, proc, &flag1)) != 0)
    {
        printf("pthread_create: %s\n", strerror(ret));
        return ret;
    }


    // signal to stop
    if(getchar())
    {
        flag1 = 0;
    }



    // cleaning...
    if((ret = pthread_join(id1, (void**)&exit_code)) != 0)
    {
        printf("pthread_join in main: %s\n", strerror(ret));
        return ret;
    }

    if(shmdt(local_data) == -1)
    {
        perror("shmdt in main");
        return errno;
    }

    if(shmctl(mem_id, IPC_RMID, NULL) == -1)
    {
        perror("shmctl in main");
        return errno;
    }

    if(sem_close(sem_write) == -1)
    {
        perror("sem_close write in main");
        return errno;
    }

    if(sem_close(sem_read) == -1)
    {
        perror("sem_close read in main");
        return errno;
    }

    if(sem_unlink("/my_sem_read") == -1)
    {
        perror("sem_unlink read in main");
        return errno;
    }

    if(sem_unlink("/my_sem_write") == -1)
    {
        perror("sem_unlink write in main");
        return errno;
    }

    return 0;
}



