#ifndef __ALLOC_H__
#define __ALLOC_H__
#include "matrice.h"

matrice allouer_matrice(int nb_lignes, int nb_colonnes);
void detruire_matrice(matrice *mat);

#endif
