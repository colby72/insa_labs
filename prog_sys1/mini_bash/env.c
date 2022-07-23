#include <stdio.h>
#include <stdlib.h>
extern char **environ;

int main(int argc, char *argv[]) {
	if (argc==1) {
		char** envp = environ;
		while (*envp) printf("%s\n", *envp++);
	}
	if (argc>1) {
		int i=1;
		while (i<argc && getenv(argv[i])!=NULL) {
			if (getenv(argv[i]) != NULL) printf("%s=%s\n", argv[i], getenv(argv[i]));
			i++;
		}
	}
        exit(EXIT_SUCCESS);
}
