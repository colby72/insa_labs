/* file name  : liste.c
 * authors    : Simon MORIN / JF Lalande
 * created    : dim 08 jan 2006 16:36:13 CET
 * copyright  : ENSIB
 *
 * modifications:
 * - Le premier �l�ment est d�sormais un �l�ment "de gestion". Il ne contient
 *   pas de vehicule. Lorsque la liste est vide, le premier element contient:
 *   l->v = NULL;
 *   l->next = NULL;
 * - Par consequent, le "vrai" premier element est juste apres.
 * - Quelques fonctions ont ete renommees.
 *
 */
#include <stdlib.h>
#include <string.h>
#include "liste.h"

// Initialise une liste vide
liste_vehicule * init_liste() {
	liste_vehicule *temp = (liste_vehicule *) malloc(sizeof(liste_vehicule));
	temp->v = NULL;
	temp->next = NULL;
  temp->size = 0;
	return temp;
}

// Ajoute un vehicule en queue
void add_vehicule(vehicule *v,liste_vehicule * l) {
  // On augmente la taille
  l->size++;
  // Puis on ajoute
	if (l->next != NULL) add_vehicule(v,l->next);
	else {
		l->next = (liste_vehicule *) malloc(sizeof(liste_vehicule));
		l->next->v = v;
		l->next->next = NULL;
	}
}

// Ajoute un vehicule en tete
void add_vehicule_head(vehicule *v, liste_vehicule *l) {
  liste_vehicule *nouv = (liste_vehicule *) malloc(sizeof(liste_vehicule));
  nouv->v = v;
  nouv->next = l->next;
  l->next = nouv;
  l->size++;
}

// Enleve le premier vehicule et le retourne
vehicule * remove_first_vehicule(liste_vehicule * l) {
	vehicule *v;
  v = l->next->v;
	l->next = l->next->next;
  l->size--;
	return v;
}

// Retourne la tete de la liste
vehicule * get_first_vehicule(liste_vehicule * l) {
  if (l->next != NULL) return l->next->v;
  else return NULL;
}

// Retourne le dernier element de la liste
vehicule *get_last_vehicule(liste_vehicule * l) {
  if (l->next != NULL) return get_last_vehicule(l->next);
  else return l->v;
}

// Detruit la liste des vehicules et les vehicules
void destroy_list_and_vehicules(liste_vehicule * l) {
	if(l->next != NULL) destroy_list_and_vehicules(l->next);
	if(l->v != NULL) destroy_vehicule(l->v);
  else l->size = 0;
	free(l);
}

// Taille de la liste
int size(liste_vehicule * l) {
  return l->size;
}

// Cherche une vehicule par son nom
vehicule* cherche_vehicule(char nom[20], liste_vehicule* L) {
	if (strcmp(get_first_vehicule(L)->nom_modele,nom)==0) return get_first_vehicule(L);
	else return cherche_vehicule(nom, L->next);
}

// Enlever une vehicule par son nom
vehicule* enlever_vehicule(char nom[20], liste_vehicule* l) {
	l->size--;
	printf("\n%s\n", (l->v)->nom_modele);
	if (strcmp(get_first_vehicule(l)->nom_modele, nom) == 0) {
		vehicule* ret = cherche_vehicule(nom, l);
		liste_vehicule* temp = l->next;
		l->next = NULL;
		l = temp;
		return ret;
	}
	else return enlever_vehicule(nom, l->next);
}

// Renverser une liste
liste_vehicule* renverser_liste(liste_vehicule* l) {
	liste_vehicule* new = init_liste();
	while (l->next != NULL) {
		add_vehicule_head(get_first_vehicule(l), new);
		l->next = (l->next)->next;
	}
	destroy_list_and_vehicules(l);
	return new;
}

// Teste l'existence d'un vehicule dans la liste
int exist_in(char nom[20], liste_vehicule* l) {
	while (l->next != NULL) {
		if (strcmp((l->v)->nom_modele,nom)==0) return 0;
	}
	return 1;
}

// Union de deux listes
liste_vehicule* union_liste(liste_vehicule *l1, liste_vehicule *l2, int doublon) {
	liste_vehicule* new = init_liste();
	int i=0;
	while (l1->next != NULL) {
		printf("%d\n", i);
		l1->next = (l1->next)->next;
		add_vehicule(get_last_vehicule(l1), new);
		i++;
	}
	if (doublon==0) {
		while (l2->next != NULL) {
			//printf("%d\n", i);
			l2->next = (l2->next)->next;
			add_vehicule(get_last_vehicule(l2), new);
			i++;
		}
	}
	else {
		while (l2->next != NULL) {
			printf("%d\n", i);
			if (exist_in((l2->v)->nom_modele, new)==0) l2->next = (l2->next)->next;
			else {
				add_vehicule(get_last_vehicule(l2), new);
				l2->next = (l2->next)->next;
			}
			i++;
		}
	}
	return new;
}
