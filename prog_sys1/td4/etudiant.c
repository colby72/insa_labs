#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv) {
	typedef struct {
		char nom[20];
		long int note;
	} etudiant;
	etudiant *student;
	student->nom = argv[1];
	student->note = strtol(argv[2], NULL, 10);
	#define BUFF sizeof(etudiant)
	char buffer[BUFF] = student;
	FILE *dat = fopen("note.dat", "wb");
	fwrite(buffer, sizeof(etudiant), BUFF, dat);
	fclose(dat);
	return EXIT_SUCCESS;
}
