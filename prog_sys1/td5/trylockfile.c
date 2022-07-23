#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int lock_reg(int fd, int lockCmd, int lockType, off_t regRffset, int regWhence, off_t regLen) {
	struct flock lock;
	lock.l_type = lockType;
	lock.l_start = regRffset;
	lock.l_whence = regWhence;
	lock.l_len = regLen;
	return fcntl(fd, lockCmd, &lock);
}

#define read_lock(fd, offset, whence, len) lock_reg(fd, F_SETLK, F_RDLCK, offset, whence, len)
#define readw_lock(fd, offset, whence, len) lock_reg(fd, F_SETLKW, F_RDLCK, offset, whence, len)
#define write_lock(fd, offset, whence, len) lock_reg(fd, F_SETLK, F_WRLCK, offset, whence, len)
#define writew_lock(fd, offset, whence, len) lock_reg(fd, F_SETLKW, F_WRLCK, offset, whence, len)
#define un_lock(fd, offset, whence, len) lock_reg(fd, F_SETLK, F_UNLCK, offset, whence, len)

int main(int argc, char* argv[]) {
	return EXIT_SUCCESS;
}
