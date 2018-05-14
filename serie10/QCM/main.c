#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "demander_nombre.h"

#define MAX_REP 10

/* Types */
typedef struct {
  char* question;
  char* reponses[MAX_REP]; /* tableau de 10 pointeurs de caractères */
  unsigned int nb_rep;
  unsigned int solution;
}  QCM;

typedef QCM* Examen;

/* Prototypes */
void affiche(QCM const * question);
unsigned int poser_question(QCM const * question);
unsigned int creer_examen(Examen*);
void detruire_examen(Examen*);

/* ====================================================================== */
int main(void)
{
  unsigned int note = 0;
  Examen exam = NULL;
  unsigned int taille_examen = creer_examen(&exam);
  unsigned int i;

  for (i = 0; i < taille_examen; ++i)
    if (poser_question(&(exam[i])) == exam[i].solution)
      ++note;

  /* petite astuce pour accorder 'bonne reponse' si 
   * l'utilisateur a plusieurs réponses correctes. 
   */
  printf("Vous avez trouvé %d bonne", note);
  if (note > 1) putchar('s');
  printf(" réponse");
  if (note > 1) putchar('s');
  printf(" sur %d.\n", taille_examen);

  detruire_examen(&exam);
  return 0;
}


/* ====================================================================== */
void affiche(QCM const * q)
{
  unsigned int i;
  printf("%s ?\n", q->question);
  for (i = 0; i < q->nb_rep; ++i) {
   /* on affiche i+1 pour éviter de commencer l'énumération des réponses avec 0 */
    printf("    %d- %s\n", i+1, q->reponses[i]);
  }
}

/* ====================================================================== */
unsigned int poser_question(QCM const * q)
{
  affiche(q);
  /* on transforme le type int retourné par demander_nombre en un unsigned int */
  return (unsigned int) demander_nombre(1, q->nb_rep);
}

/* ====================================================================== */
unsigned int creer_examen(Examen* retour)
{
  unsigned int i;

  /* Pour cet examen, on a 3 QCM, donc il faut allouer l'équivalent de
   * 3 fois la taille d'un QCM dans la mémoire.
   */
  *retour = calloc(3, sizeof(QCM));

  
  /* QUESTION 1 */
  /* On alloue une taille de 50 caractères pour la question.
   * Note: malloc(50) ou malloc(50*sizeof(char)) revient
   * au même car sizeof(char) est toujours égal à 1.
   */
  (*retour)[0].question = malloc(50);
  strcpy((*retour)[0].question,
         "Combien de dents possède un éléphant adulte");

  (*retour)[0].nb_rep = 5;
  
  for (i = 0; i < (*retour)[0].nb_rep; ++i) {
  /* On alloue 10 caractères pour chaque réponse. */
    (*retour)[0].reponses[i] = malloc(10);
  }
  strcpy((*retour)[0].reponses[0], "32");
  strcpy((*retour)[0].reponses[1], "de 6 à 10");
  strcpy((*retour)[0].reponses[2], "beaucoup");
  strcpy((*retour)[0].reponses[3], "24");
  strcpy((*retour)[0].reponses[4], "2");

  (*retour)[0].solution = 2;

  /* QUESTION 2 */
  /* On alloue 80 caractères pour la question. */
  (*retour)[1].question = malloc(80);
  strcpy((*retour)[1].question,
         "Laquelle des instructions suivantes est un prototype de fonction");

  (*retour)[1].nb_rep = 4;

  for (i = 0; i < (*retour)[1].nb_rep; ++i) {
    /* On alloue 14 caractères pour chaque réponse. */
    (*retour)[1].reponses[i] = malloc(14);
  }
  strcpy((*retour)[1].reponses[0], "int f(0);");
  strcpy((*retour)[1].reponses[1], "int f(int 0);");
  strcpy((*retour)[1].reponses[2], "int f(int i);");
  strcpy((*retour)[1].reponses[3], "int f(i);");

  (*retour)[1].solution = 3;

  /* QUESTION 2 */
  /* On alloue 40 caractères pour la question. */
  (*retour)[2].question = malloc(40);
  strcpy((*retour)[2].question,
         "Qui pose des questions stupides");

  (*retour)[2].nb_rep = 7;

  for (i = 0; i < (*retour)[2].nb_rep; ++i) {
    /* On alloue 50 caractères pour chaque réponse. */
    (*retour)[2].reponses[i] = malloc(50);
  }
  strcpy((*retour)[2].reponses[0], "le prof. de math");
  strcpy((*retour)[2].reponses[1], "mon copain/ma copine");
  strcpy((*retour)[2].reponses[2], "le prof. de physique");
  strcpy((*retour)[2].reponses[3], "moi");
  strcpy((*retour)[2].reponses[4], "le prof. d'info");
  strcpy((*retour)[2].reponses[5], "personne, il n'y a pas de question stupide");
  strcpy((*retour)[2].reponses[6], "les sondages");

  (*retour)[2].solution = 6;
         
  return (unsigned int) 3;
}

/* ====================================================================== */
void detruire_examen(Examen* retour)
{
  unsigned int i, j;

  /* Pour chaque question */
  for (i = 0; i < 3; ++i) {
  
    /* Pour chaque reponse à cette question */
    for (j = 0; j < (*retour)[i].nb_rep; ++j) 
    {   
      /* On libère la mémoire allouée pour chaque reponse */
      free((*retour)[i].reponses[j]);
    }
    /* On libère la mémoire allouée pour chaque question */
    free((*retour)[i].question);
  }
  /* On libère la mémoire allouée pour l'Examen pointé par retour */
  free(*retour);
  *retour = NULL;
}

