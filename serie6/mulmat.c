//Created by Valentin Garnier - PROGOS Course - EPFL

/* C89 */
#include <stdio.h>
#include <stdlib.h>
 
#define N 10
 
typedef struct {
   double m[N][N];
   size_t lignes;
   size_t colonnes;
} Matrice;
 
Matrice* lire_matrice(void);
void affiche_matrice(const Matrice);
Matrice* multiplication(Matrice const* a, Matrice const* b);
 
/* ---------------------------------------------------------------------- */
int main(void)
{
  Matrice* m1Pointeur = NULL;
  Matrice* m2Pointeur = NULL;
  Matrice* mPointeur = NULL;

  m1Pointeur = malloc(sizeof(Matrice));
  m2Pointeur = malloc(sizeof(Matrice));
  mPointeur = malloc(sizeof(Matrice));

  m1Pointeur = lire_matrice();
  m2Pointeur = lire_matrice();
 
  if ((*m1Pointeur).colonnes != (*m2Pointeur).lignes) 
    printf("Multiplication de matrices impossible !\n");
  else {
    printf("Résultat :\n");
    mPointeur = multiplication(m1Pointeur, m2Pointeur);
    affiche_matrice(*mPointeur);
  }
  free(m1Pointeur);
  free(m2Pointeur);
  free(mPointeur);
  return 0;
}
 
/* ---------------------------------------------------------------------- */
Matrice* lire_matrice(void)
{
  Matrice* resultat = NULL;
  resultat = malloc(sizeof(Matrice));
  
  size_t lignes = 2;
  size_t colonnes = 2;
 
  printf("Saisie d'une matrice :\n");
 
  do {
    printf("  Nombre de lignes (< %d) : ", N+1);
    scanf("%lu", &lignes); /* "%zu" en C99 ; c'est mieux. */
  } while ((lignes < 1) || (lignes > N));
 
  do {
    printf("  Nombre de colonnes (< %d) : ", N+1);
    scanf("%lu", &colonnes);
  } while ((colonnes < 1)  || (colonnes > N));
 
 resultat->lignes = lignes;
 resultat->colonnes = colonnes;
 { size_t i, j;
  for (i = 0; i < lignes; ++i) 
    for (j = 0; j < colonnes; ++j) {
      printf("  M[%lu, %lu]=", i+1, j+1);
      scanf("%lf", &resultat->m[i][j]);
    }
  }
  
  return resultat;
}
 
/* ---------------------------------------------------------------------- */
Matrice* multiplication(Matrice const* a, Matrice const* b)
{
  Matrice* resultat = NULL;
  resultat = malloc(sizeof(Matrice));

  *resultat = *a; /* Disons que par convention on retourne a si la
                         * multiplication ne peut pas se faire.
                         */
  size_t i, j, k; /* variables de boucle */
 
  if (a->colonnes == b->lignes) {
    resultat->lignes = a->lignes;
    resultat->colonnes = b->colonnes;
 
    for (i = 0; i < a->lignes; ++i) 
      for (j = 0; j < b->colonnes; ++j) {
        resultat->m[i][j] = 0.0;
        for (k = 0; k < b->lignes; ++k) 
	  resultat->m[i][j] += a->m[i][k] * b->m[k][j];
      }
  }
 
  return resultat;
}
 
/* ---------------------------------------------------------------------- */
void affiche_matrice(const Matrice matrice)
{
  size_t i, j;
  for (i = 0; i < matrice.lignes; ++i) {
    for (j = 0; j < matrice.colonnes; ++j) 
      printf("%g ", matrice.m[i][j]);
    putchar('\n');
  }
}