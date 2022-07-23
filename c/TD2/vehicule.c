#include <stdlib.h>
#include <stdio.h>
#include "vehicule.h"

vehicule* init_vehicule() {
	vehicule* v = (vehicule *)malloc(sizeof(vehicule));
	v->vitesse_max = rand()/rand();
	return v;
}
void saisie_vehicule(vehicule *v) {
	printf("Entrez nom de modele : ");
	scanf("%s", v->nom_modele);
}
void affiche_vehicule(vehicule *v) {
	printf("Vehicule : %s\nPuissance : %d\nVitesse max : %f\n", v->nom_modele, v->puissance, v->vitesse_max);
}
void supprime_vehicule(vehicule *v) {
	free(v);
}

/*------ Pour éviter un conflit avec l'autre main dans pile.c lors de l'édition de lien -------
int main() {
	vehicule *v;
	v = init_vehicule();
	saisie_vehicule(v);
	affiche_vehicule(v);
	supprime_vehicule(v);
	return 0;
}
*/
