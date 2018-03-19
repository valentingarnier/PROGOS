#include <stdio.h>

typedef unsigned char Octet;

void afficher_binaire(Octet);

int main(void) {

afficher_binaire(00111);

	return 0;
}

void afficher_binaire(Octet o) {
	
	printf("%d\n", o);
}