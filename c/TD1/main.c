#include <stdlib.h>
#include <stdio.h>
#include "produit.h"

int main(void) {
	int a, b, c;
	float d;
	scanf("%d", &a);
	scanf("%d", &b);
	c = produit(a, b);
	d = moy_geo(a, b);
	printf("Le produit vaut %d\n", c);
	printf("La moyenne géométrique vaut %f\n", d);
	return EXIT_SUCCESS;
}
