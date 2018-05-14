#include <stdio.h>
#include <string.h>
#include "gestion.h"

/* --------------------------------------------------------------------- */
#define MAX 1025
int main(void)
{
  char s[MAX];
  int taille_lue;

  do {
    printf("Entrez une expresssion � �valuer : ");
    fgets(s, MAX, stdin);
    taille_lue = strlen(s) - 1;
    if ((taille_lue >= 0) && (s[taille_lue] == '\n'))
      s[taille_lue] = '\0';
    if (s[0] != '\0')  /* pas vide */
      printf(" -> r�sultat : %d\n", eval(s));
  } while ((taille_lue < 1) && !feof(stdin));

  return 0;
}
