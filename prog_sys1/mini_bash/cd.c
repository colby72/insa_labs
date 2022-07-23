#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	if (argc==1) {
		perror("Achtung ! Too few arguments !\n");
		exit(EXIT_FAILURE);
	}
	if (argc>2) {
		perror("Achtung ! Too many arguments were given !\n");
		exit(EXIT_FAILURE);
	}
	if ((chdir(argv[1]))<0) {
		perror(" Cant't change directory !\n");
		printf("%s ", argv[1]);
		switch (errno) {
			case EIO: printf("EIO\n");
			case ENOTDIR: printf("ENOTDIR\n");
			default: printf("Unknown error !\n");
		}
	}
	return EXIT_SUCCESS;
}
