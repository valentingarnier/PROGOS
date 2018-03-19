#include <stdio.h>

typedef unsigned char Octet;

void afficher_binaire(Octet);
void affiche(size_t, Octet);
void dump_mem(Octet*, size_t);

int main(void) {
char* a = "80";
int lol = 80;
int lolinverse = -80;
double little = 0.5;

dump_mem((Octet*)a, 3);

	return 0;
}

#define SIZE_TAB 8

void afficher_binaire(Octet o) {
	int list[SIZE_TAB] = {0, 0, 0, 0, 0, 0, 0, 0};
	int index = 0;
	
	do {
		int r = o%2;
		list[index] = r;
		o = (o - r)/2;
		index++;
	} while(o != 0);
	
	for(int j = SIZE_TAB-1; j >= 0; j--) {
		printf("%d", list[j]);
	}
}

void affiche(size_t size, Octet o) {

		printf("%02zu : ", size);
		afficher_binaire(o);
		printf(" %d : ", o);
		
		if(o > 32 && o <= 126) {
			printf("%c \n", o);
		} else {
		printf("'' \n");

		}
}

void dump_mem(Octet* pointeur, size_t n) {
	printf("A partie de %p : \n", &pointeur);
	
	for(size_t i = 0; i < n; i++) {
		affiche(i, pointeur[i]);
	}
}
