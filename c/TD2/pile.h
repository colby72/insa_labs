#ifndef __PILE_H__
#define __PILE_H__
#include "vehicule.h"

typedef struct PileVehicule {
	int nbVehicule;
	vehicule **tpv;
} PileVehicule;

PileVehicule* init_pilevehicule();
void empile_vehicule(PileVehicule *pv, vehicule *v);
void affiche_pilevehicule(PileVehicule *pv);
vehicule* depile_vehicule(PileVehicule *pv);
void supprime_pilevehicule(PileVehicule *pv);
#endif
