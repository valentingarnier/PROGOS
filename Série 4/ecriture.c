#include <stdio.h>
#include <string.h>

int main(void) {
#define FILEMAX 50

	char nom_fichier[FILEMAX] = "data.dat";
	
	FILE* sortie = NULL;
	sortie = fopen(nom_fichier, "w");
	
	if(sortie == NULL) {
		fprintf(stderr, "Impossible d'ecrire dans le fichier \n");
	}
	else {	
		#define MAXNAME 50
		#define AGEMAX 2
		char nom[MAXNAME] = "";
		int age = 0;
			do {
			printf("Entrez un nom (CTRL-D pour terminer) : \n");	
			fgets(nom, MAXNAME, stdin);
			int len = strlen(nom) - 1;
			
			if ((len >= 0) && (nom[len] == '\n')) {
				nom[len] ='\0';
			}	
			printf("age :\n");
			int i = scanf("%d", &age);
			if(i < 1) { printf("age invalide, on annule \n"); }
			 else { fprintf(sortie, "%s\t%d\n", nom, age); }
			
			while(!feof(stdin) && !ferror(stdin) && getc(stdin) != '\n');
			
		} while (!feof(stdin) && !ferror(stdin));
		fclose(sortie);
	}
	
	return 0;
}
