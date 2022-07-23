#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	FILE *f = fopen(argv[2], "r");
	fseek(f, 0, SEEK_END);
	char c;
	int begin = 1;
	long int n = strtol(argv[1], NULL, 10);
	while (n!=0) {
		if (fgetc(f)=='\n') n--;
		fseek(f, -1, SEEK_CUR);
		if (ftell(f)==0) {
			begin = 0;
			break;
		}
		fseek(f, -1, SEEK_CUR);
		if (ftell(f)==0) {
			begin = 0;
			break;
		}
	}
	if (begin!=0) {
		c = fgetc(f);
		c = fgetc(f);
	}
	while ((c=fgetc(f))!=EOF) {
		printf("%c", c);
	}
	fclose(f);
	return EXIT_SUCCESS;
}
