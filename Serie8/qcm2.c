#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REP 10
#define TAILLE 300

typedef struct {
	char question[TAILLE];
	char reponses[MAX_REP][TAILLE];
	unsigned int nb_rep;
	unsigned int solution;
} QCM;

typedef QCM* Examen;

void affiche(QCM*);

void affiche(QCM* qcm) {
	printf("%s \n", qcm->question);
	for(int i = 0; i < qcm->nb_rep; i++) {
		printf("%d-", i);
		printf(" %s \n", qcm->reponses[i]);
	}
}

int poser_question(QCM* qcm) {
int userAnswer = 0;
int score = 0;
		affiche(qcm);
		printf("Entrez un nombre entre 1 et %d : ", qcm->nb_rep);
		scanf("%d", &userAnswer);
		
		if(userAnswer == qcm->solution) {
			 score += 1;
		 }
		printf("\n");
	return score;
}

Examen creer_examen(void) {
	Examen exa = calloc(4, sizeof(QCM));
	Examen* retour = &exa;
	
	strcpy((*retour)[0].question,
         "Combien de dents possède un éléphant adulte");
  (*retour)[0].nb_rep = 5;
  strcpy((*retour)[0].reponses[0], "32");
  strcpy((*retour)[0].reponses[1], "de 6 à 10");
  strcpy((*retour)[0].reponses[2], "beaucoup");
  strcpy((*retour)[0].reponses[3], "24");
  strcpy((*retour)[0].reponses[4], "2");
  (*retour)[0].solution = 2;

  strcpy((*retour)[1].question,
         "Laquelle des instructions suivantes est un prototype de fonction");
  (*retour)[1].nb_rep = 4;
  strcpy((*retour)[1].reponses[0], "int f(0);");
  strcpy((*retour)[1].reponses[1], "int f(int 0);");
  strcpy((*retour)[1].reponses[2], "int f(int i);");
  strcpy((*retour)[1].reponses[3], "int f(i);");
  (*retour)[1].solution = 3;

  strcpy((*retour)[2].question,
         "Qui pose des questions stupides");
  (*retour)[2].nb_rep = 7;
  strcpy((*retour)[2].reponses[0], "le prof. de math");
  strcpy((*retour)[2].reponses[1], "mon copain/ma copine");
  strcpy((*retour)[2].reponses[2], "le prof. de physique");
  strcpy((*retour)[2].reponses[3], "moi");
  strcpy((*retour)[2].reponses[4], "le prof. d'info");
  strcpy((*retour)[2].reponses[5], "personne, il n'y a pas de question stupide");
  strcpy((*retour)[2].reponses[6], "les sondages");
  (*retour)[2].solution = 6;
  
  return exa;
}

void detruire_Examen(Examen exam) {
	if(exam != NULL) free(exam);
}
#define NB_DEMANDES 3

FILE* demander_fichier()
{
  FILE* f = NULL;
  char nom_fichier[FILENAME_MAX+1];
  size_t taille_lue = 0;
  unsigned short int nb = 0;
 
  do {
    ++nb;
 
    /* demande le nom du fichier */
    do {
      printf("Nom du fichier à lire : "); fflush(stdout);
      fgets(nom_fichier, FILENAME_MAX+1, stdin);
      taille_lue = strlen(nom_fichier);
      if ((taille_lue >= 1) && (nom_fichier[taille_lue-1] == '\n'))
        nom_fichier[--taille_lue] = '\0';
    } while ((taille_lue == 0) && !feof(stdin));
 
    if (nom_fichier[0] == '\0') {
      return NULL;
    }
 
    /* essaye d'ouvrir le fichier */
    f = fopen(nom_fichier, "r");
 
    /* est-ce que ça a marché ? */
    if (f == NULL) {
      printf("-> ERREUR, je ne peux pas lire le fichier \"%s\"\n",
             nom_fichier);
    } else {
      printf("-> OK, fichier \"%s\" ouvert pour lecture.",
             nom_fichier);
    }
  } while ((f == NULL) && (nb < NB_DEMANDES));
 
  /* la valeur de retour est le résultat du test entre (): 0 ou 1 */
  return f;
}
int main(void) {

	Examen examen = creer_examen();
	int score = 0;
	
	for(int i = 0; i < 3; i++) {
		score += poser_question(&examen[i]);
	}
	
	printf("Vous avez trouver %d bonne reponses sur 3", score);
	
	detruire_Examen(examen);
	return 0;
}
