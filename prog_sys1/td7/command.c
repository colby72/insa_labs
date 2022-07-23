#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	char* newargv;
	newargv[0] = argv[1];
	execve(argv[1], newargv);
	exit(EXIT_SUCCESS);
}
