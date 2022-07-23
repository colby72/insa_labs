#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	char text[8] = "hello\n";
	ssize_t x = write(STDOUT_FILENO, text, -1);
	if ((int) x==-1) perror("Das funktioniert nicht !");
	return EXIT_SUCCESS;
}
