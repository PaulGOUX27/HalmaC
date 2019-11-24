#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define N 12
#define couleur(param) printf("\033[%sm",param)

typedef struct{
  int plateau[N][N];
  int tour;
  int joueur;
}plateau;

typedef struct{
  int ligne;
  int colonne;
}position;

void initialiser(plateau *p);
void afficher(plateau p, position d);
int tester_victoire(plateau p);
int verifier_deplacement(plateau *p, position d, int pas);
void saisir_coord_arrive(plateau p, position *a);
void jouer(plateau *p, position position_depart,position position_arrive);
void saisir_pion_depart(plateau *p, position *d, int pas);
void affdebug(plateau p);
