#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

int list(char* fname) {
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
	struct passwd *pw = getpwuid(fil.st_uid);
	struct group *group = getgrgid(fil.st_gid);
	switch (fil.st_mode & S_IFMT) {
		case S_IFBLK: printf("b"); break;
		case S_IFCHR: printf("c"); break;
		case S_IFDIR: printf("d"); break;
		case S_IFIFO: printf("f"); break;
		case S_IFLNK: printf("l"); break;
		case S_IFREG: printf("-"); break;
		case S_IFSOCK: printf("s"); break;
		default: printf("?"); break;
	}
	printf("%c%c%c%c%c%c%c%c%c ",
	fil.st_mode&S_IRUSR?'r':'-',
	fil.st_mode&S_IWUSR?'w':'-',
	fil.st_mode&S_IXUSR?'x':'-',
	fil.st_mode&S_IRGRP?'r':'-',
	fil.st_mode&S_IWGRP?'w':'-',
	fil.st_mode&S_IXGRP?'x':'-',
	fil.st_mode&S_IROTH?'r':'-',
	fil.st_mode&S_IWOTH?'w':'-',
	fil.st_mode&S_IXOTH?'x':'-');
	printf("%d ", (int) fil.st_nlink);
	printf("%s %s ", pw->pw_name, group->gr_name);
	printf("%li ", fil.st_size);
	char time[20] = "";
	strftime(time, 20, "%b %d %H:%M", localtime(&(fil.st_mtime)));
	printf("%s ", time);
	printf("%s\n", fname);
}
int main(int argc, char* argv[]) {
	if (argc==1) {
		DIR *dir = opendir(".");
		struct dirent *f;
		while (f=readdir(dir)) list(f->d_name);
	}
	if (argc>1) {
		int i;
		for (i=1; i<argc; i++) list(argv[i]);
	}
	exit(EXIT_SUCCESS);
}
