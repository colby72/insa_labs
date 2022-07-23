#include <stdio.h>
#include <unistd.h>

int main() {
	char * param[] = {"/bin/sh", NULL};
	execve("/bin/sh", param, NULL);
	return 0;
}
