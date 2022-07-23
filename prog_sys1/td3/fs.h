#define TMAX 100

typedef struct inode {
	int type; //type de fichier: 0=rep 1=fichier
	int taille; //taille en octets
	int nb_liens;
	int * num_blocs; //table des numéros de blocs
} inode;

int bitmap_inode[10];
int bitmap_blocs[10];
char blocs[10][TMAX];
inode table[10];
