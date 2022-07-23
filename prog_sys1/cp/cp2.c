#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFF 4096

int main(int argc, char** argv) {
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
	return 0;
}
