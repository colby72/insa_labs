#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h> 
#define PATH_LEN 128

int main(int argc, char* argv[]) {
	if (argc>1) {
		perror("Achtung ! Too many arguments were given !\n");
		exit(EXIT_FAILURE);
	}
	char* pwd = malloc(PATH_LEN*sizeof(char));
	if ((getcwd(pwd, PATH_LEN))==NULL) {
		perror("Achtung ! ");
		switch (errno) {
			case EFAULT: printf("EFAULT\n");
			case ENAMETOOLONG: printf("Name too long\n");
			// other errors to add if I got time
			default: printf("Unknown error !\n");
		}
	}
	printf("%s\n", pwd);
	exit(EXIT_SUCCESS);
}
