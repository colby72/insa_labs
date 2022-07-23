#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i=1;
	while (i<argc && getenv(argv[i])!=NULL) {
		if (getenv(argv[i]) != NULL) printf("%s=%s\n", argv[i], getenv(argv[i]));
		i++;
	}
	exit(EXIT_SUCCESS);
}
