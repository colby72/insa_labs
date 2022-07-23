#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	if (argc==1) {
		perror("No arguments were given !");
		exit(EXIT_FAILURE);
	}
	for (int i=1; i<argc; i++) {
		if ((mknod(argv[i], S_IFREG|S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IROTH, 0))<0) {
			perror("Achtung ! Can't create file ");
			printf("%s", argv[i]);
			switch (errno) {
				case EEXIST: printf("EEXIST\n"); break;
				case EACCES: printf("EACCES\n"); break;
				case EDQUOT: printf("EDQUOT\n"); break;
				case EFAULT: printf("EFAULT\n"); break;
				// some other errors to manage
				default: printf("error unknown !\n"); break;
			}
		}
	}
	return EXIT_SUCCESS;
}
