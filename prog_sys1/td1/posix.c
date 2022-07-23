#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
	#ifdef _POSIX_SOURCE
	printf("_POSIX_SOURCE=%d\n", _POSIX_SOURCE);
	#endif
	#ifdef _SVID_SOURCE
	printf("_SVID_SOURCE=%d\n", _SVID_SOURCE);
	#endif
	#ifdef _GNU_SOURCE
	printf("_GNU_SOURCE=%d\n", _GNU_SOURCE);
	#endif
	#ifdef _ISOC99_SOURCE
	printf("_ISOC99_SOURCE=%d\n", _ISOC99_SOURCE);
	#endif
	#ifdef _POSIX_C_SOURCE
	printf("_POSIX_C_SOURCE=%d\n", _POSIX_C_SOURCE);
	#endif
	#ifdef _XOPEN_SOURCE
	prinf("_XOPEN_SOURCE=%d\n", _XOPEN_SOURCE);
	#endif
	#ifdef _XOPEN_SOURCE_EXTENDED
	printf("_OPEN_SOURCE_EXTENDED=%d\n", _XOPEN_SOURCE_EXTENDED);
	#endif
	#ifdef _BSD_SOURCE
	printf("_BSD_SOURCE=%d\n", _BSD_SOURCE);
	#endif
	#ifdef __STRICT_ANSI__
	printf("__STRICT_ANSI__=%d\n", __STRICT_ANSI__);
	#endif
	#ifdef _LARGEFILE64_SOURCE
	printf("_LARGEFILE64_SOURCE=%d\n", _LARGEFILE64_SOURCE);
	#endif
	if (_POSIX_C_SOURCE==2008) printf("Code de 2008 inclu !\n");
	else printf("Code par défaut\n");
	if (_POSIX_C_SOURCE==200112) printf("Code de 2008 inclu par ub #if!\n");
	int j;
	j = sysconf(_SC_VERSION);
	printf("_SC_VERSION=%i\n", j);
	return EXIT_SUCCESS;
}
