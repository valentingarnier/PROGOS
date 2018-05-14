// C99
#include <stdio.h>

typedef unsigned char octet;

// ======================================================================
// version 1

static inline void affiche_bit(const octet c,
                               const octet position_pattern)
{
  putchar(c & position_pattern ? '1' : '0');
}

void affiche_binaire(const octet c) {
  for(octet mask = 0x80; mask; mask >>= 1)
    affiche_bit(c, mask);
}

/* version 2 : moins bonne que ci-dessus :
 * affiche les bits � � l'envers � et n'affiche
 * pas les 0 de poids fort.
 */
void affiche_binaire_2(octet c) {
  do {
    if (c & 1) putchar('1');
    else       putchar('0');
    c >>= 1; // ou c /= 2;
  } while (c);
}

// ======================================================================
void affiche(size_t i, octet c) {
  printf("%02zu : ", i);
  affiche_binaire(c);
  printf(" %3u ", (unsigned int) c);
  if ((c >= 32) && (c <= 126)) {
    printf("'%c'", c);
  }
  putchar('\n');
}

// ======================================================================
void dump_mem(const octet* ptr, size_t length)
{
  /* Avec l'arithmetique des pointeurs
   */
  octet* ptr_end = ptr + length;
  printf("A partir de %p :\n", ptr);
  for(octet* index = ptr; index != ptr_end; index++) {
    affiche(index - ptr, *index);
  }
} 

// ======================================================================
int main(void)
{
  int a = 64 + 16;
  int b = -a;
  double x = 0.5;
  double y = 0.1;

  dump_mem( (octet*) &a, sizeof(a) );
  dump_mem( (octet*) &b, sizeof(b) );
  dump_mem( (octet*) &x, sizeof(x) );
  dump_mem( (octet*) &y, sizeof(y) );

  return 0;
}