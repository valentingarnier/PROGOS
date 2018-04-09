#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int nextToken(char const *, int*, int*);
#define TAILLE_MAX 1000

int nextToken(char const * str, int* from, int* len) { //pointeur sur un objet constant
	int result = 0;
	for (int i = *from; i <= strlen(str); i++) {
		if(str[i] == '\0') return result;
		else {
			if (str[i] == ' ') {
				*len = i - *from;
				 *from = i + 1;
				 return 1;
			 }
			 printf("%c", str[i]);
		}	
	}

	return result;
}

int main(void) {
	
	char ligne[TAILLE_MAX];
	int index = 0;
	int length = 0;
	
	printf("Entrez une chaine : ");
	fgets(ligne, TAILLE_MAX, stdin);
	fflush(stdout);
	
	ligne[strlen(ligne) - 1] = '\0';
	
	printf("Les mots de '%s' sont : \n", ligne);
	printf("'");
	nextToken(ligne, &index, &length);
	printf("'\n");
	printf("'");
	nextToken(ligne, &index, &length);
	printf("'\n");
	printf("'");
	nextToken(ligne, &index, &length);
	printf("'\n");
	
	
	return 0;
}
