#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	if (argc==1) {
		perror("Achtung ! No argument was given !\n");
		exit(EXIT_FAILURE);
	}
	if (argc>2) {
		perror("Achtung ! Too many arguments !\n");
		exit(EXIT_FAILURE);
	}
	FILE *f = fopen(argv[1], "r");
	int nbc = 0;
	int nbw = 0;
	int nbl = 0;
	fseek(f, 0, SEEK_SET);
	char c;
	while ((c=fgetc(f))!=EOF) {
		nbc++;
		if (c==' ') nbw++;
		if (c=='\n') {
			nbw++;
			nbl++;
		}
	}
	nbw--;
	fclose(f);
	printf("%d %d %d %s\n", nbl, nbw, nbc, argv[1]);
	exit(EXIT_SUCCESS);
}
