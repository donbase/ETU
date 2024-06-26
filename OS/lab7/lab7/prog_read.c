#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <mqueue.h>
#define SIZE 2048
#define MQ_SIZE 1024
#define MQ_MAXMSG 10

mqd_t  mq_id;

void* proc(void* flag)
{
    int* flag1 = (int*)flag;
    char buf[SIZE];
    while(*flag1)
    {
        memset(buf, 0, SIZE);
        if(mq_receive(mq_id, buf, SIZE, NULL) == -1)
        {
            perror("mq_receive");
        }

        printf("read: %s\n",buf);
        sleep(1);
    }

    pthread_exit((void*)0);
}


int main()
{

    int* exit_code;
    pthread_t id1;
    struct mq_attr attr;
    attr.mq_msgsize = MQ_SIZE;
    attr.mq_maxmsg = MQ_MAXMSG;


    // opening message queue
    mq_id = mq_open("/my_mq", O_RDONLY|O_CREAT|O_NONBLOCK, 0660, &attr);
    if(mq_id == -1)
    {
        perror("mq_open");
        return errno;
    }

    int ret;
    int flag1 = 1;

    //pthread creating
    if((ret = pthread_create(&id1, NULL, proc, &flag1)) != 0)
    {
        printf("pthread_create: %s\n", strerror(ret));
        return ret;
    }

    // signal to stop thread
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

    if(mq_close(mq_id) == -1)
    {
        perror("mq_close");
        return errno;
    }

    if(mq_unlink("/my_mq") == -1)
    {
        perror("mq_unlink");
        return errno;
    }

    return 0;
}



