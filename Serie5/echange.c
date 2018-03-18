#include <stdio.h>

void echange(int*, int*);

int main(void) {

int i = 10;
    int j = 55;

    printf("Avant : i=%d et j=%d\n", i, j);
    echange(&i, &j);
    printf("Après : i=%d et j=%d\n", i, j);
    return 0;
}

void echange(int* pointeur1, int* pointeur2) {
	int const tmp = *pointeur1;
	*pointeur1 = *pointeur2;
	*pointeur2 = tmp; 
}