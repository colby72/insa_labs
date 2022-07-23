#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

int main(int argc, char* argv[]) {
	pid_t status;
	printf("[%d] Je vais engendrer\n", getpid());
	status = fork();
	switch (status) {
		case -1:
			perror("Creation processus");
			exit(EXIT_FAILURE);
		case 0:
			printf("[%d] Je viens de naitre\n", getpid());
			printf("[%d] Mon pere est %d\n", getpid(), getppid());
			break;
		default:
			printf("[%d] J'ai engendre\n", getpid());
			printf("[%d] Mon fils est %d\n", getpid(), status);
	}
	printf("[%d] Je termine\n", getpid());
	return EXIT_SUCCESS;
}
