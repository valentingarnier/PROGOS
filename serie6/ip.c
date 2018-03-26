//Created by Valentin Garnier - PROGOS Course - EPFL

#include <stdio.h>
#include <stdlib.h>

#define SIZE_ADDR 4
#define FIRST_SIZE 0
typedef struct {
	unsigned char addr[SIZE_ADDR];
	struct Noeud* voisins[FIRST_SIZE];
	size_t sizeNeighbor;
} Noeud;

Noeud* creation(unsigned char, unsigned char, unsigned char, unsigned char);
void sont_voisins(Noeud*, Noeud*);
int voisins_communs(Noeud*, Noeud*);
void affiche(Noeud*);

int main(void) {
	printf("test");
	return 0;
}

Noeud* creation(unsigned char first, unsigned char second, unsigned char third, unsigned char fourth) {
	Noeud* resultat = malloc(sizeof(Noeud));

	resultat->addr[0] = first;
	resultat->addr[1] = second;
	resultat->addr[2] = third;
	resultat->addr[3] = fourth;

	return resultat;
}

void sont_voisins(Noeud* a, Noeud* b) {
	++(a->sizeNeighbor);
	++(b->sizeNeighbor);

	*(a->voisins)[a->sizeNeighbor] = b;
	*(b->voisins)[a->sizeNeighbor] = a;
}

int voisins_communs(Noeud* a, Noeud* b) {
	int compteur = 0;

	for (int i = 0; i < a->sizeNeighbor; ++i) {
		for (int j = 0; j < b->sizeNeighbor; ++i) {
			if(*(a->voisins)[i] == *(b->voisins)[j]) {
				++compteur;
			}
		}
	}
return compteur;
}

/*PROBLEMES : LA TAILLE DU TABLEAU, LACCESS AU POINTEUR DE POINTEUR GENRE, Incrementer la taille du tableau dynamiquement pas bonne




