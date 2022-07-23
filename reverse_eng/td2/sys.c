#include <unistd.h>

void main() {
	execve("/bin/sh", 0, 0);
}
