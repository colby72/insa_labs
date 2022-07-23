#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void pr_pathconf(char *path, int name, char *message) {
	long lim = pathconf(path, name);
	if (lim<0) perror("erreur de pathconf\n");
	else {
		write(STDOUT_FILENO, &name, 256);
		write(STDOUT_FILENO, &lim, 256);
	}
}
int main(int argc, char* argv[]) {
	pr_pathconf(argv[1], argv[2], argv[3]);
	return EXIT_SUCCESS;
}
