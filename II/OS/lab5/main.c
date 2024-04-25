#include <stdio.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

//sem_t *sem;

int main(){
  //  FILE *file;
  //  sem = sem_open("/my_sem", O_CREAT, S_IRWXU, 1);
  //  file = fopen("hello.txt", "a");
    fd_set rfds;
    FD_SET(0, &rfds);    
    struct timespec ts = {3, 0};

    while(1){
//	sem_wait(sem);  
  /*      for(int i = 0; i < 10; i++){
            fprintf(file, "1");
            fprintf(stdout, "1");
	    fflush(file);
	    fflush(stdout);
	    sleep(1);
	}
	*/

//	sem_post(sem);
	int n = pselect(1, &rfds, NULL, NULL, &ts, NULL);
	printf("=%d=\n", n);

  //      if(n)
//	    break;
    }
    


 //   fclose(file);
   // sem_close(sem);
   // sem_unlink("/my_sem");
    return 0;
}
