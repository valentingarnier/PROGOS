#include <stdio.h>

int main(void) {
	char const nom_fichier[] = "data.dat";
	FILE* entree = NULL;
	
	entree = fopen(nom_fichier, "r");
	if(entree == NULL) {
		fprintf(stderr, "Impossible de lire le fichier");
	}
	else {
		
		#define MAX_NAME 50
		#define MAX_AGE 3
		
		char nameRead[MAX_NAME] = "";
		int ageRead = 0;
		int nbPersonne = 0;
		int maxAge = 0;
		int minAge = 0;
		int sommeAge = 0;
		
	printf("+-----------------+-----+ \n");
		while(fscanf(entree, "%[^\t]\t%d\n", nameRead, &ageRead) == 2) {
			minAge = ageRead;
			nbPersonne ++;
			if(ageRead > maxAge) maxAge = ageRead;
			if(ageRead < minAge) minAge = ageRead;
			sommeAge += ageRead;
			printf("| %-15s | %3d |\n", nameRead, ageRead);
		}
		printf("+-----------------+-----+ \n");
		double moyenne = sommeAge / nbPersonne;
		printf("\nAge maximum: %d \n", maxAge);
		printf("Age minimum: %d \n", minAge);
		printf("%d personnes, moyenne des age: %3f\n", nbPersonne, moyenne);
		
		fclose(entree);
	}
	return 0;
}
