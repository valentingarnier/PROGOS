#include <stdio.h>
#include <stdlib.h>

int nextToken(char const * str, int* from, int* len);
#define TAILLE_MAX 1024


int nextToken(char const* str, int* from, int* len) {
	int result = 0;
	for (int i = *from; i < strlen(str); ++i) {
		if(str[i] == '\0') return result;
		else {

		}
	}

	return result;
}

int main(void) {

	char sentence[TAILLE_MAX];
	int index = 0;
	int len = 0;

	printf("Entrez la phrase : ");
	fflush(stdout);
	fgets(sentence, TAILLE_MAX, stdin);
	sentence[strlen(sentence) - 1] = '\0';

	nextToken(sentence, &index, &len);

	printf("%s\n", sentence);
	return 0;
}