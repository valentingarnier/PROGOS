#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void genereLettre();

int main(void) {
	genereLettre();

	return 0;
}

void genereLettre() {
	printf("Bonjour chère Mireille,\n");
	fflush(stdout);
	printf("Je vous écris à propos de votre cours.\n");
	fflush(stdout);
	printf("Il faudrait que nous nous voyons le 18/12 pour en discuter.\n");
	fflush(stdout);
	printf("Donnez-moi vite de vos nouvelles !\n");
	fflush(stdout);
	printf("Amicalement, John.\n");
	fflush(stdout);
}