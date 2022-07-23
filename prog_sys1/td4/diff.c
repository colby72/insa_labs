#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char** argv) {
	FILE *f1 = fopen(argv[1], "r");
	FILE *f2 = fopen(argv[2], "r");
	char c1, c2;
	while (((c1=fgetc(f1))!=EOF) && ((c2=fgetc(f2))!=EOF)) {
		if (c1!=c2) {
			printf("%s different from %s\n", argv[1], argv[2]);
			return EXIT_SUCCESS;
		}
	}
	if (!(fgetc(f1)==EOF) || !(fgetc(f2)==EOF)) {
		printf("%s different from %s\n", argv[1], argv[2]);
		return EXIT_SUCCESS;
	}
	printf("%s same as %s\n", argv[1], argv[2]);
	fclose(f1);
	fclose(f2);
	return EXIT_SUCCESS;
}
