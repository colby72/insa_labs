#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char put[256] = "";
	strcat(put, argv[1]);
	strcat(put, "=");
	strcat(put, argv[2]);
	if ((putenv(put))!=0) {
		perror("Achtung ! putenv fail !\n");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
