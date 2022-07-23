#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
	char buff[256];
	if (argc!=2) {
		exit(0);
	}
	printf("%p\n", buff);
	strcpy(buff, argv[1]);
	printf("%s\n", buff);
	return 0;
}
