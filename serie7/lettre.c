#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void genereLettre(char, char [], char [], int, int, char [], char[]);

int main(void) {
	char genre = 'F';
	char destinataire[] = "Mireille      ";
	char sujet[] = "votre cours                ";
	char politesse[] = "Amicalement            ";
	char auteur[] = "John                ";
	int jour = 18;
	int mois = 12;

	genereLettre(genre, destinataire, sujet, jour, mois, politesse, auteur);
	

	genre = 'M';
	strcpy(destinataire, "John");

	strcpy(sujet, "votre demande de rendez-vous.");
	jour = 16;
	strcpy(politesse, "Sincèrement");
	
		
	printf("%s", destinataire);
	strcpy(auteur, "Mireille"); 


	printf("\n");
	printf("\n");
	fflush(stdout);
	genereLettre(genre, destinataire, sujet, jour, mois, politesse, auteur);

	printf("\n");
	fflush(stdout);

	return 0;
}

void genereLettre(char genre, char destinataire[], char sujet[], int jour, int mois, char politesse[], char auteur[]) {

	
	char salut[] = "aaaaaa";	
	(genre == 'M') ? strcpy(salut, "cher"), salut[5] = '\0' : strcpy(salut, "chère"), salut[6] = '\0';

	
	printf("Bonjour %s %s,\n", salut, destinataire);
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
