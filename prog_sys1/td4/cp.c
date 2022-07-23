#include <stdio.h>
#include <stdlib.h>

int copy(char* source, char* dest) {
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	if (argc<3) {
		printf("Too few arguments !!\n");
		return EXIT_FAILURE;
	}
	if (argc>3) {
		printf("Too many arguments !!\n");
		return EXIT_FAILURE;
	}
	copy(argv[1], argv[2]);
	return EXIT_SUCCESS;
}
