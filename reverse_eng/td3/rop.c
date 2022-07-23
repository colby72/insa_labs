#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

//la fonction vulnérable vuln
void vuln() {
	char buf[50];
	//dlsym dynamic linking
	void (*printf_addr)() = dlsym(RTLD_NEXT, "printf"); //adresse du symbole
	printf("Printf() at address : %p\n",printf_addr); //printf dans libc
	read(0, buf, 256);
}

void main() {
	seteuid(getuid());
	write(1, "On ROPe\n", 8); // 7 car. Dans la chaîne
	vuln();
}
