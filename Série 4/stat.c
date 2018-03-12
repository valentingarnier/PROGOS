#include <stdio.h>
#include <string.h>

#define SIZE_STAT 222
typedef unsigned long int Statistique[SIZE_STAT];

FILE* demander_fichier();
void initialise_statistique(Statistique, int);
unsigned long int collecte_statistique(Statistique, FILE*);
void affiche(Statistique, unsigned long int);

int main(void) {
    Statistique s;
    
    FILE* file = demander_fichier();
    if(file != NULL) {
    initialise_statistique(s, SIZE_STAT);
    unsigned long int nbElem = collecte_statistique(s, file);
    affiche(s, nbElem);
    }
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
        int len = strlen(nom_fichier) - 1;
        if(len >= 0 && (nom_fichier[len] == '\n')) nom_fichier[len] = '\0';
        compteur++;
        entree = fopen(nom_fichier, "r");
        if(entree == NULL) {
            printf("ERREUR, je ne peux pas lire le fichier %s\n", nom_fichier);
        }
    } while(!feof(stdin) && !ferror(stdin) && entree == NULL);
    
    return entree;
    
}

void initialise_statistique(Statistique s, int size) {
    for (int i = 0; i < size; i++) {
        s[i] = 0;
    }
}

unsigned long int collecte_statistique(Statistique s, FILE* f) {
    unsigned long int result = 0;
    
    while(!feof(f) && !ferror(f)) {
        int j = getc(f);
        if(j >= 32 && j <= 253) {
            s[j - 32] += 1;
        }
    }
    for(int i = 0; i < SIZE_STAT; i++) {
        result += s[i];
    }
    return result;
}

void affiche(Statistique stat, unsigned long int nbElem) {
    printf("STATISTIQUES : \n");
    for (int i = 0; i < SIZE_STAT; i++) {
        if(stat[i] == 0) continue;
        printf("%c : %11ld - %5f%%\n", i + 32, stat[i], 1.0*stat[i]/nbElem);
    }
}
