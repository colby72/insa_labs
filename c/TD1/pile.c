#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

pile *cree_pile() {
	pile *p = malloc(sizeof(pile));
	p->curseur = 0;
	return p;
}
void libere_pile(pile *p) {
	free(p);
}
void ajoute_pile(pile *p, int n) {
	p->tab[p->curseur] = n;
	p->curseur++;
}
int retire_pile(pile *p) {
	p->curseur--;
	return p->tab[p->curseur];
}
int sommet_pile(pile *p) {
	return p->tab[p->curseur-1];
}
int pile_vide(pile *p) {
	if (p->curseur==0) return 0;
	return 1;
}
int pile_pleine(pile *p) {
	if (p->curseur==TMAX) return 0;
	return 1;
}
void affiche_pile(pile *p) {
	printf("(");
	int n = 1;
	do {
		if (n==1) printf("%d", p->tab[p->curseur-n]);
		else printf(", %d", p->tab[p->curseur-n]);
		n--;
	} while (p->curseur-n>0);
	printf(")");
}

int main() {
	int c, n;
	pile p;
	do {
		printf("\n");
		printf("1. Empiler \n");
		printf("2. Depiler \n");
		printf("3. Sommet \n");
		printf("4. Affichage \n");
		printf("\n");
		printf("0. Quitter \n");
		printf("Votre choix : ");
		scanf("%d", &c);
		switch(c) {
			case 1:
				if (pile_pleine(&p)) {
					printf("Pile pleine. Empilement impossible\n");
					break;
				}
				printf("Empilement. Entrez le nombre a empiler : ");
				scanf("%d", &n);
				ajoute_pile(&p, n);
				break;
			case 2:
				if (pile_vide(&p)) {
					printf("Pile vide. Depilement de %d\n", retire_pile(&p));
					break;
				}
				printf("Depilement de %d\n", retire_pile(&p));
				break;
			case 3:
				if (pile_vide(&p)) {
					printf("Pile vide. Pas de sommet\n");
					break;
				}
				printf("Sommet : %d\n", sommet_pile(&p));
				break;
			case 4:
				printf("Affichage : ");
				affiche_pile(&p);
				printf("\n");
				break;
		}
	} while (c!=0);
	return 0;
}
