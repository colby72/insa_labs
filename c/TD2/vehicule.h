#ifndef __VEHICULE_H__
#define __VEHICULE_H__

typedef struct vehicule {
	char nom_modele[20];
	int puissance;
	float vitesse_max;
} vehicule;

vehicule * init_vehicule();
void affiche_vehicule(vehicule *v);
void supprime_vehicule(vehicule *v);
void saisie_vehicule(vehicule *v);
#endif
