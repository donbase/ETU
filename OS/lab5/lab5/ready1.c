#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

sem_t *sem;

int main(){
    FILE *file;
    if((sem = sem_open("/my_sem", O_CREAT, S_IRWXU, 1)) == SEM_FAILED){
	   perror("sem_open");
	   return errno;
    }

    if((file = fopen("hello.txt", "a")) == NULL){
    	perror("file_open");
	return errno;
    }
    fd_set rfds;
    
    struct timespec ts = {1, 0};

    while(1){
    FD_ZERO(&rfds);
    FD_SET(0, &rfds); 
	sem_wait(sem);  
        for(int i = 0; i < 10; i++){
            fprintf(file, "1");
            fprintf(stdout, "1");
	    fflush(file);
	    fflush(stdout);
	    sleep(1);
	    }
	sem_post(sem);
	int n;
	if(n = pselect(1, &rfds, NULL, NULL, &ts, NULL) == 1){
	break;
	}
	else if(n == -1){
	perror("pselect");
	return errno;
	}
    }
    


    if(fclose(file) != 0){
    	perror("close_file");
    }

    if(sem_close(sem) != 0){
    perror("sem_close");
    }
    if (sem_unlink("/my_sem") != 0){
	perror("sem_unlink");	    
    }
    return 0;
}
