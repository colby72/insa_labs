#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
	if (argc==1) {
		perror("Achtung ! No command was specified !\n");
		exit(EXIT_FAILURE);
	}
	for (int i=1; i<argc; i++) {
		printf("----- Help for %s -----\n", argv[i]);
		if ((strcmp(argv[i],"env"))==0) {
			printf("Affiche les valeur des variables d'environnement données en paramètres\n");
			printf("Affiche toutes les variables d'environnement si aucun paramètre n'est donné\n");
		}
		else {
			printf("Entchuldigung ! I got no idea what to say !!!\n");
		}
	}
	exit(EXIT_SUCCESS);
}
