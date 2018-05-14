#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* deux definition utiles */
#define LISTE_VIDE (NULL)
#define est_vide(L) ((L) == LISTE_VIDE)

/* deux definitions pour changer facilement de type */
#define type_el char
#define affiche_el(T) printf("%c", T)

/* la structure de liste chainee */
typedef struct Element_ Element;
typedef Element* ListeChainee;
struct Element_ {
    type_el valeur;
    ListeChainee suite;
};

/* les "méthodes" */
void insere_entete(ListeChainee* liste, type_el une_valeur);
void insere_apres(Element* existant, type_el a_inserer);
void supprime_tete(ListeChainee* liste);
void supprime_suivant(Element* e);
size_t taille(ListeChainee liste);
void affiche_liste(ListeChainee liste);

/* ====================================================================== */
void insere_entete(ListeChainee* liste, type_el une_valeur)
{
  const ListeChainee tmp = *liste;

  *liste = malloc(sizeof(Element));
  if (*liste != NULL) {
    (*liste)->valeur = une_valeur; 
    (*liste)->suite = tmp;
  } else {
    /* si on n'a pas pu faire d'allocation, au moins on restitue
       l'origine.
       Mieux : il faudrait l'indiquer par une valeur de retour */
    *liste = tmp;
  }
}

/* ====================================================================== */
void insere_apres(Element* existant, type_el a_inserer)
{
  Element* e;
  e = malloc(sizeof(Element));
  if (e != NULL) {
    e->valeur = a_inserer;
    e->suite = existant->suite;
    existant->suite = e;
  }
}

/* ====================================================================== */
void supprime_tete(ListeChainee* liste)
{
  if (!est_vide(*liste)) {
    ListeChainee nouvelle = (*liste)->suite;
    free(*liste);
    *liste = nouvelle;
  }
}

/* ====================================================================== */
void supprime_suivant(Element* e)
{
  /* supprime le premier élément de la liste "suite" */
  supprime_tete(&(e->suite)); 
}

/* ====================================================================== */
size_t taille(ListeChainee liste)
{
  size_t t = 0;
  while (!est_vide(liste)) { 
    ++t; 
    liste = liste->suite; 
  }
  return t;
}

/* ====================================================================== */
void affiche_liste(ListeChainee liste)
{
    ListeChainee i;
    putchar('(');
    for (i = liste; !est_vide(i); i = i->suite) {
      affiche_el(i->valeur);
      if (!est_vide(i->suite)) printf(", ");
	}
    putchar(')');
}

/* ====================================================================== */
#define TAILLE_MAX 1024
int main(void) {

  ListeChainee maliste = LISTE_VIDE;
  char entree[TAILLE_MAX + 1]; // pour le caractere vide

  printf("Entrez une expression parenthésée : ");
  fflush(stdout);
  fgets(entree, TAILLE_MAX, stdin);

  int i = 0;
  while (i < strlen(entree) - 1) {
    if (entree[i] == '(' || entree[i] == '[') {
      insere_entete(&maliste, entree[i]);

    }
    else if(entree[i] == ']' || entree[i] == ')') {
      if(est_vide(maliste)) { 
        return -1;
      }
      else {
        char entete = maliste->valeur;
        if((entete == '(' && entree[i] == ')') || (entete == '[' && entree[i] == ']')) {
          supprime_tete(&maliste);
        }
        else return -1;
      }
    }
    i++;
  }

  if(est_vide(maliste))  printf("OK\n");
  else printf("Elle n'est pas parenthesee\n");
  fflush(stdout);

  return 0;
}
