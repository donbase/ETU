#include <stdio.h>
#include <sys/capability.h>
#include <errno.h>
#define SIZE 1024


int main(){

	cap_t P = cap_get_file("a.out");
        char *str = cap_to_text(P, NULL);
	printf("POSSIBILITIES BEFORE: %s\n", str);

	cap_free(str);

	P = cap_from_text("cap_dac_override=+eip");
	if(cap_set_file("a.out", P) == 0){
		printf("--POSSIBILITIES set succesfully--\n");
	}	
	else{
		perror("error cap_set");
		return errno;
	}
	return 0;

}
