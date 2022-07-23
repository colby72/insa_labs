#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	//char* new = strcat(strcat(argv[1], "="), argv[2]);
	char put[256];
	strcat(put, argv[1]);
	strcat(put, "=");
	strcat(put, argv[2]);
	putenv(put);
	exit(EXIT_SUCCESS);
}
