#include <stdio.h>
#include <stdlib.h>
#include "alloc.h"
#include "matrice.h"

matrice allouer_matrice(int nb_lignes, int nb_colonnes) {
    //matrice* mat = (matrice *)malloc(sizeof(matrice));
    matrice mat;
    mat.nb_lignes = nb_lignes;
    mat.nb_colonnes = nb_colonnes;
    mat.m = malloc(nb_lignes*sizeof(int*));
    int i = 0;
    for (i=0; i<nb_lignes; i++) {
      mat.m[i] = malloc(nb_colonnes * sizeof(int));
    }
    return mat;
}
void detruire_matrice(matrice *mat) {
    int i = 0;
    for (i=0; i<mat->nb_lignes; i++) {
      free(mat->m[i]);
    }
    free(mat->m);
}
