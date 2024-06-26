#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#define SIZE 128

int pipefd[2];
int socketFD;
struct sockaddr_un clientAddr;
int clientSize;

void* proc_get(void* flag)
{
    int* flag1 = (int*)flag;
    char msg[SIZE];

    while(*flag1)
    {
        int res = recvfrom(socketFD, msg, sizeof msg, 0, (struct sockaddr*)&clientAddr, &clientSize);
        if(res != -1)
        {
            write(pipefd[1], msg, sizeof msg);
            printf("%s from %s RECEIVED\n", msg, clientAddr.sun_path);
        }
    }

    pthread_exit((void*)0);

}



void* proc_ans(void* flag)
{
    int* flag2 = (int*)flag;
    char msg[SIZE];
    while(*flag2)
    {
        char ans[SIZE*2];
        int res = read(pipefd[0], msg, sizeof msg);
        if(res > 0)
        {
            char name[10];
            getdomainname(name, sizeof name);
            snprintf(ans, sizeof ans, "%s: %s", msg, name);
            sendto(socketFD, ans, sizeof ans, 0, (struct sockaddr *)&clientAddr, sizeof clientAddr);
        }
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
    struct sockaddr_un serverAddr;
    serverAddr.sun_family = AF_UNIX;
    strcpy(serverAddr.sun_path, "server_socket.soc\0");

    int optval = 1;
    setsockopt(socketFD, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    if(bind(socketFD, (struct sockaddr *)&serverAddr, sizeof serverAddr) == -1)
    {
        perror("bind");
        return errno;
    }

    if(pipe(pipefd) == -1)
    {
        perror("pipe");
        return errno;
    }

    fcntl(pipefd[0], F_SETFL, O_NONBLOCK);

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

    if(close(socketFD) != 0)
    {
        perror("close");
        return errno;
    }

    return 0;
}
