#include <stdio.h>

int demander_nombre();

int main(void) {

	double valeur1 = 1;
	double valeur2 = 4.5;
	double valeur3 = 9.75;

	double* choix = NULL;

	int nombre = 0;
	nombre = demander_nombre();

	switch(nombre) {
		case 1:
			choix = &valeur1;
			break;
		case 2:
			choix = &valeur2;
			break;
		case 3:
			choix = &valeur3;
			break;
		default: break;			
	}

	printf("Vous avez choisi %.2f \n", *choix);

	return 0;
}

int demander_nombre() {
	int value = 0;

	printf("Entrez un nombre :[1-3] \n");
	scanf("%d", &value);

	return value;
}