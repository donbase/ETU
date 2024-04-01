#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <semaphore.h>

sem_t sem;
struct timespec tp;


void* proc1(void* flag){
	fputs("--поток 1 начал работу--\n",stdout);
	int* flag1 = (int*)flag;
	while(*flag1){
		
		while(1){
			clock_gettime(CLOCK_REALTIME, &tp);
			tp.tv_sec += 1;
			int rv = sem_timedwait(&sem, &tp);
			if(!rv){
				fputs("--proc1 захватил семафор--\n", stdout);
				break;
			}
			}
		

		for(int i = 0; i < 10; i++){
			printf("1\n");
			sleep(1);
		}
		if(sem_post(&sem) == -1){
			perror("ошибка освобождение семафора proc1");	
			exit(0);
		}
		else fputs("--proc1 освободил семафор--\n", stdout);
		sleep(1);
		
	}
	fputs("--поток 1 закончил работу--\n",stdout);
	pthread_exit((void*)1);
}

void* proc2(void* flag){
	fputs("--поток 2 начал работу--\n",stdout);
	int* flag2 = (int*)flag;
	while(*flag2){

		while(1){
			clock_gettime(CLOCK_REALTIME, &tp);
			tp.tv_sec += 1;
			int rv = sem_timedwait(&sem, &tp);
			if(!rv){
				fputs("--proc2 захватил семафор--\n", stdout);
				break;
			}
		}
		


		
		for(int i = 0; i < 10; i++){
			printf("2\n");
			sleep(1);
		}
		if(sem_post(&sem) == -1){
			perror("ошибка освобождение семафора proc2");
			exit(0);
		}
		else fputs("--proc2 освободил семафор--\n", stdout);
		sleep(1);
	}
	fputs("--поток 2 закончил работу--\n",stdout);
	pthread_exit((void*)2);
}


int main(){
	fputs("--программа начала работу--\n",stdout);
	int flag1 = 1;
	int flag2 = 1;

	pthread_t id1, id2;
	int ret_val;
	int* exit_code1;
	int* exit_code2;

	int ret;
	


	if(sem_init(&sem, 0, 1) == -1){
		perror("Ошибка инициализации неименованного семафора");
		return 0;

	}
		
	if((ret = pthread_create(&id1, NULL, proc1, &flag1)) != 0){
		printf("ошибка создания потока 1: %s\n", strerror(ret));
		return 0;
	}
	if(ret = (pthread_create(&id2, NULL, proc2, &flag2)) != 0){
		printf("ошибка создания потока 2: %s\n", strerror(ret));
		return 0;
	}

	if(getchar()){
		flag1 = 0;
		flag2 = 0;
	}

	if((ret_val = pthread_join(id1, (void**)&exit_code1)) != 0){
		printf("ошибка ожидания завершения потока 1: %s\n", strerror(ret_val));
		return 0;
	}
	else{
		printf("Код возврата потока 1: %p\n", exit_code1);
	}

	if((ret_val = pthread_join(id2, (void**)&exit_code2)) != 0){
		printf("ошибка ожидания завершения потока 2: %s\n", strerror(ret_val));
		return 0;
	}
	else{
		printf("Код возврата потока 2: %p\n", exit_code2);
	}
	
	if(sem_destroy(&sem) == -1){
		perror("Ошибка удаления семафора");
		return 0;
	}
	
	fputs("--программа закончила работу--\n", stdout);	
	return 0;

}
