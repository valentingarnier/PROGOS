typedef int type_el;

/* version simpliste avec tableau de taille fixe.
   Une version plus r�aliste utiliserait des tableaux dynamique.
*/

#define STACK_OVERFLOW 256
#define VIDE -1
typedef struct {
  type_el tab[STACK_OVERFLOW];
  int tete;
} Pile;