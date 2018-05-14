#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion.h"

/* -------------------------------------------------------------------- */
int empile (Pile* p, type_el e)
{
  ++(p->tete);
  if (p->tete >= STACK_OVERFLOW) {
    p->tete = STACK_OVERFLOW;
    return 0; }
  else {
    p->tab[p->tete] = e;
  }
  return 1;
}

/* ---------------------------------------------------------------------- */
void depile (Pile* p)
{
  if (!est_vide(p)) --(p->tete);
}

/* ---------------------------------------------------------------------- */
type_el top (Pile* p)
{
  if (!est_vide(p))
    return p->tab[p->tete];

  else /* que faire ??  -> totalement arbitraire... */
    return 0;
}

/* ---------------------------------------------------------------------- */
int est_vide(Pile* p)
{
  return ((p->tete < 0) || (p->tete >= STACK_OVERFLOW));
}

/* ---------------------------------------------------------------------- */
void init_Pile(Pile* p)
{
  p->tete = -1; /* convention => pile vide */
}

/* --------------------------------------------------------------------- */
int eval(char* s) 
{
  Pile p;
  unsigned int i;
  
  init_Pile(&p);

  /* recopie dans la pile */
    for (i = 0; i < strlen(s); ++i)
    if ((s[i] >= '0') && (s[i] <= '9')) {
      /* On a lu un chiffre */
      empile(&p, (int) (s[i] - '0'));
    } else if ((s[i] == '+') || (s[i] == '-') || 
         (s[i] == '*') || (s[i] == '/')) {

      int x, y; /* arguments */

      /* recupere le second argument */
      y = top(&p);
      depile(&p);

      /* recupere le premier argument */
      x = top(&p);
      depile(&p);

      /* calcule et empile le resultat */
      switch(s[i]) {
      case '+': empile(&p, x + y); break;
      case '-': empile(&p, x - y); break;
      case '*': empile(&p, x * y); break;
      case '/': empile(&p, x / y); break;
      }
    }

  return top(&p);
}