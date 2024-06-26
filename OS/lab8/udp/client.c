#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#define SIZE 128


int pipefd[2];
int socketFD;
struct sockaddr_un serverAddr;
int serverSize;
struct sockaddr_un clientAddr;


void* proc_get(void* flag)
{
    int* flag1 = (int*)flag;
    char msg[SIZE];

    while(*flag1)
    {
        int res = recvfrom(socketFD, msg, sizeof msg, 0, (struct sockaddr *)&serverAddr, &serverSize);
        if(res != -1)
        {
            printf("--RECEIVED ANSWER: %s\n", msg);
        }
        sleep(1);
    }

    pthread_exit((void*)0);

}



void* proc_ans(void* flag)
{
    int* flag2 = (int*)flag;
    int num = 1;
    while(*flag2)
    {
        char ans[SIZE];
        char* msg = "REQUEST";
        char str[128];
        int res;
        snprintf(str, sizeof str, "%s %d", msg, num);
        if((res = sendto(socketFD, str, strlen(str), 0, (struct sockaddr *)&serverAddr, sizeof serverAddr)) != -1)
        {
            printf(" %s ", clientAddr.sun_path);
            printf("%s has been sent\n", str);
        }
        else
        {
            printf("no connection...\n");
        }
        num++;
        sleep(1);
    }

    pthread_exit((void*)0);

}


int main()
{

    socketFD = socket(AF_UNIX, SOCK_DGRAM, 0);
    if(socketFD == -1)
    {
        perror("socket");
        return errno;
    }

    fcntl(socketFD, F_SETFL, O_NONBLOCK);
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, "server_socket.soc\0");


    clientAddr.sun_family = AF_UNIX;
    strcpy(clientAddr.sun_path, "client_socket.soc\0");



    int optval = 1;
    setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);


    if(bind(socketFD, (struct sockaddr *)&clientAddr, sizeof serverAddr) == -1)
    {
        perror("bind");
        return errno;
    }

    int flag1 = 1;
    int flag2 = 1;
    pthread_t id_read, id_ans;

    int res;
    if((res = pthread_create(&id_read, NULL, proc_get, &flag1)) != 0)
    {
        printf("pthread_create read: %s\n", strerror(res));
        return res;
    }

    if((res = pthread_create(&id_ans, NULL, proc_ans, &flag2)) != 0)
    {
        printf("pthread_create write: %s\n", strerror(res));
        return res;
    }

    if(getchar())
    {
        flag1 = 0;
        flag2 = 0;
    }

    pthread_join(id_read, NULL);
    pthread_join(id_ans, NULL);

    if(close(socketFD) == -1)
    {
        perror("close");
        return errno;
    }
    return 0;
}
