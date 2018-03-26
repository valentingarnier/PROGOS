//Created by Valentin Garnier - PROGOS Course - EPFL

#include <stdio.h>
#include <stdlib.h>

#define SIZE_ADDR 4

typedef struct NoeudT {
	unsigned char addr[SIZE_ADDR];
	struct NoeudT** voisins;
	size_t sizeNeighbor;
} Noeud;

Noeud* creation(unsigned char, unsigned char, unsigned char, unsigned char);
void sont_voisins(Noeud*, Noeud*);
int voisins_communs(Noeud*, Noeud*);
void affiche(Noeud*);
int equals_ip(Noeud*, Noeud*);

int main(void) {
	printf("test");
	return 0;
}

Noeud* creation(unsigned char first, unsigned char second,
				unsigned char third, unsigned char fourth) {

	Noeud* resultat = malloc(sizeof(Noeud));

	resultat->addr[0] = first;
	resultat->addr[1] = second;
	resultat->addr[2] = third;
	resultat->addr[3] = fourth;

	return resultat;
}

void sont_voisins(Noeud* a, Noeud* b) {
	++(a->sizeNeighbor);
	a->voisins = realloc(a->voisins, a->sizeNeighbor * sizeof(Noeud));
	++(b->sizeNeighbor);
	b->voisins = realloc(b->voisins, b->sizeNeighbor * sizeof(Noeud));

	a->voisins[a->sizeNeighbor] = b;
	b->voisins[b->sizeNeighbor]= a;

	free(a);
	free(b);
}

int voisins_communs(Noeud* a, Noeud* b) {
	int compteur = 0;

	for (int i = 0; i < a->sizeNeighbor; ++i) {
		for (int j = 0; j < b->sizeNeighbor; ++i) {
			if(equals_ip(a->voisins[i], b->voisins[j])) {
				++compteur;
			}
		}
	}
return compteur;
}

int equals_ip(Noeud* a, Noeud* b) {
	int result = 0;
	for(int i = 0; i < SIZE_ADDR; i++) {
		if(a->addr[i] != b->addr[i]) {
			result = 1;
		}
	}

	return result;
}