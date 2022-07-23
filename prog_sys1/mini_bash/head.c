#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	long int n = 10;
	if (argc==1) {
		perror("Achtung ! Too few arguments !\n");
		exit(EXIT_FAILURE);
	}
	else if (argc>3) {
		perror("Achtung ! Too many arguments !\n");
		exit(EXIT_FAILURE);
	}
	else if (argc==2) {
		n = 10;
	}
	else if (argc==3) {
		n = strtol(argv[1], NULL, 10);
	}
	FILE *f = fopen(argv[2], "r");
	fseek(f, 0, SEEK_SET);
	char c;
	while (((c=fgetc(f))!=EOF) && (n>0)) {
		if (c=='\n') n--;
		printf("%c", c);
	}
	fclose(f);
	exit(EXIT_SUCCESS);
}
