#include <stdio.h>
#include <stdlib.h>
#include "matrice_calcul.h"
#include "matrice.h"
#include "alloc.h"

matrice add_matrice(matrice m1, matrice m2) {
  int i, j;
  if (m1.nb_lignes==m2.nb_lignes && m1.nb_colonnes==m2.nb_colonnes) {
    matrice mat = allouer_matrice(m1.nb_lignes, m1.nb_colonnes);
    for (i=0; i<mat.nb_lignes; i++) {
      for (j=0; j<mat.nb_colonnes; j++) {
        //printf("%d\n", mat.m[i][j]);
        mat.m[i][j] = m1.m[i][j] + m2.m[i][j];
      }
    }
    return mat;
  }
  else{
    printf("\nAddition impossible car matrices incompatibles.\n");
    return m1;
  }
}
matrice multiply_matrice(matrice m1, matrice m2) {
  if (m1.nb_colonnes==m2.nb_lignes) {
    matrice mat = allouer_matrice(m2.nb_lignes, m1.nb_colonnes);
    int s = 0;
    for (int i=0; i<mat.nb_lignes; i++) {
      for (int j=0; j<mat.nb_colonnes; j++) {
        s = 0;
        for (int k=0; k<m1.nb_colonnes; k++) {
          s += m1.m[i][k] * m2.m[k][j];
        }
      }
    }
  }
  else{
    printf("\nMultiplication impossible car matrices incompatibles.\n");
    return m1;
  }
}
