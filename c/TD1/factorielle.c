#include <stdio.h>
#include <limits.h>

int factorielle_iter(int n) {
	int i, p = 1;
	for (i=1; i<=n; i++) {
		if (INT_MAX/p<i) return -1;
		//if (p*i < p) return -1;
		p *= i;
	}
	return p;
}

int factorielle_rec(int n) {
	if (n<=0) return 1;
	else {
		if (INT_MAX/factorielle_rec(n-1)<n) return -1;
		//if (n*factorielle_rec(n-1) < factorielle_rec(n-1)) return -1;
		else return n*factorielle_rec(n-1);
	}
}

int main(void) {
	int n;
	do {
		printf("Enter an integer (0 to terminate) : ");
		scanf("%d", &n);
		printf("Factorielle_iterative(%2d)=%5d\n", n, factorielle_iter(n));
		printf("Factorielle_rec(%2d)=%5d\n", n, factorielle_rec(n));
	} while (n!=0);
	return 0;
}
