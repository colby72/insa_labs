#include <stdlib.h>
#include <stdio.h>
#include "vehicule.h"
#include "pile.h"

PileVehicule* init_pilevehicule() {
	PileVehicule* pv = (PileVehicule *)malloc(sizeof(PileVehicule));
	pv->nbVehicule = 0;
	pv->tpv = (vehicule**)malloc(15*sizeof(vehicule*));
	return pv;
}
void empile_vehicule(PileVehicule *pv, vehicule *v) {
	(pv->nbVehicule)++;
	pv->tpv[pv->nbVehicule] = v;
}
void affiche_pilevehicule(PileVehicule *pv) {
	printf("Nombre de véhicules : %d\n", pv->nbVehicule);
	int i = 0;
	for (i=0; i < pv->nbVehicule; i++) {
		printf("%s\n", pv->tpv[pv->nbVehicule]);
	}
}
vehicule* depile_vehicule(PileVehicule *pv) {
	pv->nbVehicule--;
	return pv->tpv[pv->nbVehicule];
}
void supprime_pilevehicule(PileVehicule *pv) {
	free(pv);
}

int main() {
	vehicule *v1, *v2, *v3;
	PileVehicule *pv;
	v1 = init_vehicule();
	v2 = init_vehicule();
	saisie_vehicule(v1);
	saisie_vehicule(v2);
	printf("\nCréation de la pile");
	pv = init_pilevehicule();
	empile_vehicule(pv, v1);
	empile_vehicule(pv, v2);
	printf("\n\nAffichage de la pile\n");
	affiche_pilevehicule(pv);
	printf("\n\nSuppression d'un element de la pile\n\n");
	v3 = depile_vehicule(pv);
	affiche_vehicule(v2);
	printf("\n\nPile après supression\n\n");
	affiche_pilevehicule(pv);
	supprime_pilevehicule(pv);
	affiche_pilevehicule(pv);
	return 0;
}
