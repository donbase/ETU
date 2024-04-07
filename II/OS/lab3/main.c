#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int main(){

	char name[2];
	getdomainname(name, 2);
	printf("%s\n", name);



	return 0;
}
