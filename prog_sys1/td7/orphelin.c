#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
	printf("[%d] Here I am\n", getpid());
	pid_t current = fork();
	if (current==-1) {
		perror("Creation processus fail");
		exit(EXIT_FAILURE);
	}
	printf("[%d] I'm born\n", getpid());
	printf("[%d] My father is %d\n", getpid(), getppid());
	return EXIT_SUCCESS;
}
