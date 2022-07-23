#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	if (argc==1) {
		perror("Achtung ! No file to read is specified !\n");
		exit(EXIT_FAILURE);
	}
	if (argc>2) {
		perror("Achtung ! Too many arguments !\n");
		exit(EXIT_FAILURE);
	}
	FILE *f = fopen(argv[1], "r");
	fseek(f, 0, SEEK_SET);
	char c;
	while ((c=fgetc(f))!=EOF) {
		printf("%c", c);
	}
	fclose(f);
	return EXIT_SUCCESS;
}
