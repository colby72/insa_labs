#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

int type(char* fname) {
	struct stat fil;
	if (lstat(fname, &fil)<0) {
		perror("Das funktioniert nicht ! ");
		printf("%s : ", fname);
		switch (errno) {
			case EACCES: printf("EACCES\n"); break;
			case EBADF: printf("EBADF\n"); break;
			case EFAULT: printf("EFAULT\n"); break;
			case ELOOP: printf("ELOOP\n"); break;
			case ENAMETOOLONG: printf("ENAMETOOLONG\n"); break;
			case ENOENT: printf("ENOENT\n"); break;
			case ENOMEM: printf("ENOMEM\n"); break;
			case ENOTDIR: printf("ENOTDIR\n"); break;
			case EOVERFLOW: printf("EOVERFLOW\n"); break;
			case EINVAL: printf("EINVAL\n"); break;
			default: printf("error unknown\n"); break;
		}
		exit(errno);
	}
	switch (fil.st_mode & S_IFMT) {
		case S_IFBLK: printf("%s : SPECIAL BLOCK\n", fname); break;
		case S_IFCHR: printf("%s : SPECIAL CHARACTER\n", fname); break;
		case S_IFDIR: printf("%s : DIRECTORY\n", fname); break;
		case S_IFIFO: printf("%s : FIFO\n", fname); break;
		case S_IFLNK: printf("%s : LINK\n", fname); break;
		case S_IFREG: printf("%s : REGULAR FILE\n", fname); break;
		case S_IFSOCK: printf("%s : SOCKET\n", fname); break;
		default: printf("%s : UNKNOWN FILE TYPE\n", fname); break;
	}
	return EXIT_SUCCESS;
}

int main(int argc, char** argv) {
	/*if (argc==1) {
		printf("No files passed in argument !!\n");
		return EXIT_FAILURE;
	}*/
	if (argc==1) {
		DIR *dir = opendir(".");
		struct dirent *f;
		while(f=readdir(dir)) type(f->d_name);
	}
	if (argc>1) {
		int i;
		for (i=1; i<argc; i++) type(argv[i]);
	}
	return EXIT_SUCCESS;
}
