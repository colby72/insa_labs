#include <stdio.h>

void secret() {
	printf("Bravo !\n");
	printf("Vous connaissez maintenant le secret !\n");
}

void echo() {
	char buff[20];
	printf("Saisir votre texte : \n");
	scanf("%s", buff);
	printf("Vous avez saisi : %s\n", buff);
}

int main() {
	echo();
	return 0;
}
