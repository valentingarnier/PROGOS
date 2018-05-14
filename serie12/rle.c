#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* compresse(char const* data, char flag);
char* decompresse(char const* rledata, char flag);
#define TAILLE_MAX 1024

char buffer[TAILLE_MAX] = { '\0' };

int main(void ) {
	char* const data = "#aaaaa";
	printf("\n\n %s \n\n", compresse(data, '#'));
	return 0;
}

char* compresse(char const* data, char flag) {
	char* result = NULL;
	int length = strlen(data);
	if (length < 3) return result;
	else {
		result = calloc(1000, sizeof(char));
		int count = 0;

		char concat[3]; 

		while (count != length) {
			if (data[count] == flag) {
				concat[0] = '\0';
				concat[1] = flag;
				concat[2] = (char)0;
				strcat(result, concat); //Ca ne concat pas !!!

				printf(" fuck : %s", result);
			}
			else if(data[count] == data[count + 1]) {
				int numberOfRep = 0;
				
				while (data[count] == data[count + 1]) {
					numberOfRep++;
					count++;
				}
				concat[0] = data[count];
				concat[1] = flag;
				concat[2] = (char)numberOfRep;
				
				strcat(result, concat);
			}
			else {
				concat[0] = data[count];
				concat[1] = flag;
				concat[2] = (char)1;
			}
			
			count ++;
		}
		return result;
	}
}