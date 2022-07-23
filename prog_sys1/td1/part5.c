#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>

int main(int argc, char* argv[]) {
	struct passwd *usr = getpwnam(argv[1]);
	printf("pw_name = %s\n"
	"pw_passwd = %s\n"
	"pw_uid = %d\n"
	"pw_gid = %d\n"
	"pw_gecos = %c\n"
	"pw_dir = %s\n"
	"pw_shell = %s\n",
	usr->pw_name, usr->pw_passwd, (int) usr->pw_uid, (int) usr->pw_gid, usr->pw_gecos, usr->pw_dir, usr->pw_shell);
	return EXIT_FAILURE;
}
