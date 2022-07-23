#include <stdlib.h>
#include <stdio.h>
#include "matrice.h"
#include "alloc.h"
#include "matrice_io.h"
#include "matrice_calcul.h"

int main() {
	FILE *p1 = fopen("matrice.txt", "r");
	FILE *p2 = fopen("matrice2.txt", "r");
  matrice mat1 = read_matrice(p1);
  matrice mat2 = read_matrice(p2);
	fclose(p1);
	fclose(p2);
	printf("Affichage mat1\n\n");
	display_matrice(mat1);
	printf("\nAffichage mat2\n\n");
	display_matrice(mat2);
	matrice mat3 = add_matrice(mat1, mat2);
	printf("\nAffichage addition\n\n");
	display_matrice(mat3);
	matrice mat4 = multiply_matrice(mat1, mat2);
	printf("\nAffichage multiplication\n\n");
	display_matrice(mat4);
	detruire_matrice(&mat1);
	printf("\nfree1\n");
	detruire_matrice(&mat2);
	printf("free2\n");
	detruire_matrice(&mat3);
	printf("free3\n");
	detruire_matrice(&mat4);
	printf("free4\n");
	return 0;
}
