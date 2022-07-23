#include <stdio.h>
#include <string.h>

int chaine_longueur_rec(char *s) {
	int l=0;
	while (s[l]!='\0') l++;
	return l;
}
int chaine_debute_par (char *s1, char *s2) {
	int i;
	for (i=0; i<strlen(s2); i++) {
		if (s1[i]!=s2[i]) return 0;
	}
	return 1;
}

int main(void) {
	char ch1[] = "Salut", ch2[] = "Sal";
	printf("Longueur : %d\n", chaine_longueur_rec(ch1));
	printf("%s dans %s : %d\n", ch2, ch1, chaine_debute_par(ch1, ch2));
	return 0;
}
