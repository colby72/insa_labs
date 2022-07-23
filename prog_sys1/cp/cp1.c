#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFF 10

int main(int argc, char** argv) {
	int fdsrc = open(argv[1], O_RDONLY);
	int fddst = open(argv[2], O_WRONLY);
	char* buffer[BUFF];
	int nchar;
	while((nchar = read(fdsrc, buffer, BUFF))) {
		write(fddst, buffer, nchar);
	}
	close(fdsrc);
	close(fddst);
	return 0;
}
