#include <stdio.h>

/* ====================================================================== */
int demander_nombre(int a, int b)
{
   int res;

   if (a > b) { res=b; b=a; a=res; }

   do {
       printf("Entrez un nombre entier compris entre %d et %d : ",
              a, b);
       scanf("%d", &res);
    } while ((res < a) || (res > b));
    return res;
}