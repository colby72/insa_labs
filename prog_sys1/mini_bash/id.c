#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>

int main(int argc, char* argv[]) {
	int uid = getuid();
	int gid = getgid();
	struct passwd *pw = getpwuid(uid);
	struct group *group = getgrgid(gid);
	printf("uid=%d(%s) gid=%d(%s)\n", uid, pw->pw_name, gid, group->gr_name);
	exit(EXIT_SUCCESS);
}
