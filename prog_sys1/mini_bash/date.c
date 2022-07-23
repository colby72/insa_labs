#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	time_t t = time(NULL);
	struct tm *tmp = localtime(&t);
	if (tmp==NULL) {
		perror("Achtung ! Localtime error !\n");
		exit(EXIT_FAILURE);
	}
	char time[50] = "";
	if ((strftime(time, sizeof(time), "%a %d %b %H:%M:%s %Z %Y", tmp))==0) {
		perror ("Achtung ! strftime failure\n");
		exit(EXIT_FAILURE);
	}
	printf("%s\n", time);
	exit(EXIT_SUCCESS);
}
