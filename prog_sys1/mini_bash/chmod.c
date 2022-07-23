#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <errno.h>

int main (int argc, char* argv[]) {
	if (argc!=3) {
		perror("Achtung! Two arguments exactly are expected !\n");
		exit(EXIT_FAILURE);
	}
	long int n = strtol(argv[1], NULL, 10);
	int r = (int) n;
	/*switch(argv[1][0]) {
		case '4': chmod(argv[2], S_IRUSR); break;
		case '2': chmod(argv[2], S_IWUSR); break;
		case '1': chmod(argv[2], S_IXUSR); break;
		case '6': chmod(argv[2], S_IRUSR|S_IWUSR); break;
		case '5': chmod(argv[2], S_IRUSR|S_IXUSR); break;
		case '7': chmod(argv[2], S_IRUSR|S_IWUSR|S_IXUSR); break;
		case '3': chmod(argv[2], S_IWUSR|S_IXUSR); break;
		default: perror("Can't read user's rights !\n"); break;
	}
	switch(argv[1][1]) {
		case '4': chmod(argv[2], S_IRGRP); break;
		case '2': chmod(argv[2], S_IWGRP); break;
		case '1': chmod(argv[2], S_IXGRP); break;
		case '6': chmod(argv[2], S_IRGRP|S_IWGRP); break;
		case '5': chmod(argv[2], S_IRGRP|S_IXGRP); break;
		case '7': chmod(argv[2], S_IRGRP|S_IWGRP|S_IXGRP); break;
		case '3': chmod(argv[2], S_IWGRP|S_IXGRP); break;
		default: perror("Can't read group's rights !\n"); break;
	}
	switch(argv[1][2]) {
		case '4': chmod(argv[2], S_IROTH); break;
		case '2': chmod(argv[2], S_IWOTH); break;
		case '1': chmod(argv[2], 041); break;
		case '6': chmod(argv[2], S_IROTH|S_IWOTH); break;
		case '5': chmod(argv[2], S_IROTH|S_IXOTH); break;
		case '7': chmod(argv[2], S_IROTH|S_IWOTH|S_IXOTH); break;
		case '3': chmod(argv[2], S_IWOTH|S_IXOTH); break;
		default: perror("Can't read other's rights !\n"); break;
	}*/
	chmod(argv[2], r);
	exit(EXIT_SUCCESS);
}
