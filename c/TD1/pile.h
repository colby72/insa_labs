#define TMAX 10
typedef struct pile {
	int tab[TMAX];
	int curseur;
} pile;

pile *cree_pile();
int retire_pile(pile *p);
void ajoute_pile(pile *p, int n);
void libere_pile(pile *p);
int sommet_pile(pile *p);
void affiche_pile(pile *p);
int pile_vide(pile *p);
int pile_pleine(pile *p);
