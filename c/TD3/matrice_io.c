#include <stdio.h>
#include <stdlib.h>
#include "matrice_io.h"
#include "alloc.h"

matrice read_matrice_4_3(FILE *p) {
  // un cas particulier pour les matrices 4x3
  if (p!=NULL) {
    int l, c;
    fscanf(p, "%d %d", &l, &c);
    matrice mat = allouer_matrice(l, c);
    mat.nb_lignes = l;
    mat.nb_colonnes = c;
    for (int i=0; i<mat.nb_lignes; i++) {
      fscanf(p, "%d %d %d", &mat.m[i][0], &mat.m[i][1], &mat.m[i][2]);
    }
    return mat;
  }
}
matrice read_matrice(FILE *p) {
  if (p!=NULL) {
    int l, c;
    fscanf(p, "%d %d", &l, &c);
    matrice mat = allouer_matrice(l, c);
    mat.nb_lignes = l;
    mat.nb_colonnes = c;
    char* s;
    for (int i=0; i<mat.nb_lignes; i++) {
      for (int j=0; j<mat.nb_colonnes; j++) {
        fscanf(p, "%d", &mat.m[i][j]);
      }
    }
    return mat;
  }
}
void write_matrice(FILE *p, matrice mat) {
  fprintf(p, "%d %d\n", mat.nb_lignes, mat.nb_colonnes);
  for (int i=0; i<mat.nb_lignes; i++) {
    for (int j=0; j<mat.nb_colonnes; j++) {
      fputc(mat.m[i][j], p);
    }
    fprintf(p, "\n");
  }
}
void display_matrice(matrice mat) {
  //printf("%d %d\n", mat.nb_lignes, mat.nb_colonnes);
  int i, j;
  for (i=0; i<mat.nb_lignes; i++) {
    for (j=0; j<mat.nb_colonnes; j++) {
      printf("%d ", mat.m[i][j]);
    }
    printf("\n");
  }
}
