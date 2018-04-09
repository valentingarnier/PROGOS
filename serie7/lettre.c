#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum Genre Genre;
enum Genre { M, F };

void genereLettre();

int main(void) {
	char genre[] = "chère";
	char destinataire[] = "Mireille";
	char sujet[] = "votre cours";
	char politesse[] = "Amicalement";
	char auteur[] = "John";
	int jour = 18;
	int mois = 12;

	genereLettre(genre, destinataire, sujet, jour, mois, politesse, auteur);

	/*genre[] = "cher";
	destinataire[] = "John";
	sujet[] = "votre demande de rendez-vous.";
	jour[] = 16;
	politesse[] = "Sincèrement";
	auteur[] = "Mireille"; */

	printf("\n");
	printf("\n");
	fflush(stdout);
	genereLettre(genre, destinataire, sujet, jour, mois, politesse, auteur);

	printf("\n");
	fflush(stdout);

	return 0;
}

void genereLettre(char genre[], char destinataire[], char sujet[], int jour, int mois, char politesse[], char auteur[]) {
	printf("Bonjour %s %s,\n", genre, destinataire);
	fflush(stdout);
	printf("Je vous écris à propos de %s.\n", sujet);
	fflush(stdout);
	printf("Il faudrait que nous nous voyons le %d/%d pour en discuter.\n", jour, mois);
	fflush(stdout);
	printf("Donnez-moi vite de vos nouvelles !\n");
	fflush(stdout);
	printf("%s, %s.\n", politesse, auteur);
	fflush(stdout);
}