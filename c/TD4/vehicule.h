/* file name  : vehicule 
 * authors    : Simon MORIN / JF Lalande
 * created    : dim 08 jan 2006 16:39:20 CET
 *
 * modifications:
 *
 */
#ifndef __VEHICULE_H__
#define __VEHICULE_H__

#include <stdio.h>
#include <stdlib.h>

// Structure d'un vehicule
typedef struct {
	char nom_modele[20];
	int puissance;
	float vitesse_max;
} vehicule;

// Affichage d'un vehicule
void printVehicule(vehicule *v);

// Creation d'un vehicule
vehicule *newVehicule(char *m,int p,float v);

// Destruction d'un vehicule
void destroy_vehicule(vehicule *v);

#endif
