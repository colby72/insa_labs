#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUFF 4096

int main(int argc, char** argv) {
	if (argc!=3) {
		perror("Achtung! Two arguments exactly are expected!\n");
		exit(EXIT_FAILURE);
	}
	FILE *fsrc, *fdst;
	char buffer[BUFF];
	int c;
	fsrc = fopen(argv[1], "r");
	fdst = fopen(argv[2], "w");
	while ((fread(buffer, sizeof(char), BUFF, fsrc) )) {
		fwrite(buffer, sizeof(char), BUFF, fdst);
	}
	fclose(fsrc);
	fclose(fdst);
        return EXIT_SUCCESS;
}
