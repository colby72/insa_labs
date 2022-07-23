#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv) {
	FILE *dat = fopen("note.dat", "rb");
	fclose(dat);
	return EXIT_SUCCESS;
}
