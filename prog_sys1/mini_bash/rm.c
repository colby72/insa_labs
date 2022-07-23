#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	if (argc==1) {
		perror("Achtung ! No file to delete was specified !\n");
		exit(EXIT_FAILURE);
	}
	for (int i=1; i<argc; i++) {
		if ((unlink(argv[i]))<0) {
			perror("Cant't delete file ");
			printf("%s\n", argv[i]);
			switch (errno) {
				case EBUSY: printf("EBUSY\n"); break;
				case ENOTDIR: printf("ENOTDIR\n"); break;
				// some other errors to manage as usual
				default: printf("Error unknown !\n"); break;
			}
		}
	}
	exit(EXIT_SUCCESS);
}
