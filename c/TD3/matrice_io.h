#ifndef __MATRICE_IO_H__
#define __MATRICE_IO_H__
#include "matrice.h"

matrice read_matrice(FILE *p);
matrice read_matrice_4_3(FILE *p);
void write_matrice(FILE *p, matrice m);
void display_matrice(matrice mat);

#endif
