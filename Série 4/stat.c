#include <stdio.h>


FILE* demander_fichier();
type

int main(void) {
    demander_fichier();
    
return 0;
}

FILE* demander_fichier() {
    int compteur = 0;
    FILE* entree = NULL;
    do {
        if (compteur == 3) {
            printf("J'abandonne ! \n");
            break;
        }
#define MAXVAL 100
        char nom_fichier[MAXVAL] = "";
        printf("Nom du fichier a lire: ");
        fflush(stdout);
        fgets(nom_fichier, MAXVAL, stdin);
        compteur++;
        entree = fopen(nom_fichier, "r");
        if(entree == NULL) {
            printf("ERREUR, je ne peux pas lire le fichier %s", nom_fichier);
        }
    } while(!feof(stdin) && !ferror(stdin));
    
    return entree;
    
}
