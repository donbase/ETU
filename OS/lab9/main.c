#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(){

	int FD = open("file.txt", O_RDONLY);
	if(FD == -1){
		perror("ERROR open file.txt");
		return errno;
	}

	printf("File has opened succesfully!\n");
	close(FD);

	return 0;
}
