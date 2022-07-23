#include <stdio.h>
#include <string.h>

int conforme(char *s1, char *s2, int p) {
	int i = 0;
	for (i=0; i<strlen(s2); i++) if (s1[p+i]!=s2[i]) return 0;
	return 1;
}
int chaine_indice(char *s1, char *s2) {
	int i = 0;
	for (i=0; i<strlen(s1); i++) {
		if (s1[i]==s2[0]) {
			if (conforme(s1, s2, i)) return i;
		}
	}
	return -1;
}
int main(void) {
	char ch1[] = "jemappelleramy", ch2[] = "eller";
	printf("%s dans %s : %d\n", ch2, ch1, chaine_indice(ch1, ch2));
	return 0;
}

/*
Résultat affiché:
eller dans jemappelleramy : 6
*/
