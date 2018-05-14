#include <stdio.h>
#include <stdlib.h>

int demander_nombre();

int main(void) {
	int a = demander_nombre();
	int b = demander_nombre();

	printf("Calcul du pgcd de %d et %d \n", a, b);

	int x = a;
	int y = b;
	int u = 0;
	int v = 1;

	int q = x / y;

	int prev_u = 1;
	int prev_v = 0;

	while(y != 0) {
		int r = x % y; 
		int newY = 0;
		int newX = 0;

		newX = y;
		newY = r;
		int new_u = prev_u - u*q;
		int new_v = prev_v - v*q;

		prev_v = v;
		prev_u = u;

		u = new_u;
		v = new_v;
		x = newX;
		y = newY;

		printf("%d   %d   %d   %d\n", x, y, u, v);
	}

	printf("PGCD(%d, %d) = %d\n", a, b, x);

	return 0;
}

int demander_nombre() {
	int x = 0;
	printf("Entrez un nombre : ");
	scanf("%d", &x);

	return x;
}