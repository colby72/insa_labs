#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	if (argc==1) {
		perror("Achtung ! No folder to create was specified !\n");
		exit(EXIT_FAILURE);
	}
	for (int i=1; i<argc; i++) {
		if ((mkdir(argv[i], S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IROTH))<0) {
			perror("Can't create folder ");
			printf("%s", argv[i]);
			switch (errno) {
				case EACCES: printf("EACCES\n"); break;
				case EEXIST: printf("EEXIST\n"); break;
				// some other errors to manage as usual
				default: printf("Unknown error !\n"); break;
			}
		}
	}
	exit(EXIT_SUCCESS);
}
