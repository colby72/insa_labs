#include <stdlib.h>
#include <stdio.h>

int fact_iter(const int n) {
	int i, p = 1;
	for(i=1; i<=n; i++) {
		p *= i;
	}
	return p;
}
int fact_rec(int n) {
	if (n<=0) return 1;
	else return n*fact_rec(n-1);
}

int main(void) {
	int n;
	do {
		printf("Enter an integer (0 to end): ");
		scanf("%d", &n);
		printf("fact_iter(%2d) = %15d\n", n, fact_iter(n));
		printf("fact_rec(%2d) = %15d\n", n, fact_rec(n));
	} while(n!=0);
	return 0;
}
