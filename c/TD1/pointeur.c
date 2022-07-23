#include <stdio.h>

int elever_au_cube(int* p) {
	int n = *p;
	//printf("ici %d\n", n);
	*p = n*n*n;
	//printf("la %d\n", n);
	return n;
}

int main(void) {
	int n = 5;
	printf("%d et %d\n", n, &n);
	elever_au_cube(&n);
	printf("%d et %d\n", n, &n);
	return 0;
}

/*
Résultat affiché
5 et 1782263996
125 et 1782263996
*/
