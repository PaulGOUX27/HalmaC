#include "fonction.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#ifndef clear_ecran
#define couleur(param) printf("\033[%sm",param)
#endif

#define clear_ecran() printf("\033[H\033[J") // issu d'internet :  http://stackoverflow.com/questions/17271576/clear-screen-in-c-and-c-on-unix-based-system

#ifndef N
#define N 12
#endif



void mettre_pion(plateau *p)// algo de remplissage des pions
{
    int i, j;
    
    for(i=1; i<=5; i++) //boucle de remplissage du coin bas droit
    {
        for(j=1; j<=i; j++)
            p->plateau[i+5][j+10-i] = 1;
    }
    
    for(i=1; i<=5; i++) //boucle de remplissage du coin haut gauche
    {
        for(j=1; j<=6-i; j++)
            p->plateau[i][j] = -1;
    }
}


void initialiser(plateau *p)//remplissage du tableau virtuel avec des 5 pour les bordures, et des 0 pour le plateau jouable.
{
    int j, i;
    
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            if(i == 0) // ne faire que un if pour les 5 <---------------
                p->plateau[i][j] = 5;
            else if(i == 11)
                p->plateau[i][j] = 5;
            else if(j == 0)
                p->plateau[i][j] = 5;
            else if(j == 11)
                p->plateau[i][j] = 5;
            else
                p->plateau[i][j] = 0;
            mettre_pion(p);
        }
    }
}


void afficher_tiret(void){
    int i=0;
    
    printf("   ");
    for(i=0; i<= 40; i++)
        printf("-");
    printf("\n");
}

void afficher_titre(plateau p){
    
    if(p.joueur == 1){ // affichage du titre
        printf("-------------- tour %d - ", p.tour);
        couleur("34");
        printf("joueur & ");
        couleur("0");
        printf("--------------\n\n");
    }
    else{
        printf("-------------- tour %d - ", p.tour);
        couleur("31");
        printf("joueur $ ");
        couleur("0");
        printf("--------------\n\n");
        
    }
    
}

void afficher_plateau(plateau p, position d){
    int i,j;
    for(i = 1; i <= 10; i++){ //on affiche le tableau sur le terminal
        printf(" %d ",i - 1); //Affichage titres lignes -1 pour aller de 0 à 9, sinon le 10 décale tous
        for(j = 1; j <= 10; j++ ){
            if(p.plateau[i][j] == -1){	//on remplace les pions -1 par un $
                printf("|");
                if(d.ligne == i && d.colonne == j)
                    couleur("1");
                couleur("31");
                printf(" $ ");
                couleur("0");
            }
            else if(p.plateau[i][j] == 1){  //on remplace les pions 1 par un &
                printf("|");
                if(d.ligne == i && d.colonne == j) //on met en gras le pion choisi
                    couleur("1");
                couleur("34");
                printf(" & ");
                couleur("0");
            }
            else if(abs(p.plateau[i][j]) == 2) //on affiche par un point les cases où peut aller le pion
                printf("| . ");
            else
                printf("|   ");
        }
        
        printf("| %d\n",i - 1);
        afficher_tiret();
    }
}

void afficher(plateau p, position d){ //fonction d'affichage sur le terminal à partir du tableau
    
    clear_ecran(); //nettoyage de l'écran <=> clear dans terminal
    
    afficher_titre(p);
    
    printf(" /   A   Z   E   R   T   Y   U   I   O   P   /\n");//affichage titer colonne
    
    afficher_tiret();
    
    afficher_plateau(p, d);
    
    printf(" /   A   Z   E   R   T   Y   U   I   O   P   /\n\n");
}


int transformer_carac_a_chiffre(char c){
    switch(tolower(c)){        //tolower pour convertir les majuscules en minuscules
        case 'a':                          // switch qui converti le caractère de la colonne en chiffre exploitable dans notre tableau de valeurs --> mettre en fonction
            return 1;
        case 'z':
            return 2;
        case 'e':
            return 3;
        case 'r':
            return 4;
        case 't':
            return 5;
        case 'y':
            return 6;
        case 'u':
            return 7;
        case 'i':
            return 8;
        case 'o':
            return 9;
        case 'p':
            return 10;
        default:
            return 11;
    }
}

position saisir_coord(){
    position p;
    char coor[2];
    scanf("%s", coor);
    
    if(coor[0] >= '0' && coor[0] <= '9'){
        p.ligne = atoi(&coor[0]) + 1;
        p.colonne = transformer_carac_a_chiffre(coor[1]);
    }
    else{
        p.ligne = atoi(&coor[1]) + 1;
        p.colonne = transformer_carac_a_chiffre(coor[0]);
    }
    return p;
}


void saisir_coord_depart(plateau p, position *d){ // fonction qui demande au joueur les coordonnées du pion qu'il veut jouer
    
    
    printf("Saisir les coordonées de départ : ");
    *d = saisir_coord();
    
    
    /*printf("Ligne du pion à bouger : ");
     scanf("%d", &d->ligne);                  //saisie ligne à bouger
     printf("Colonne du pion à bouger : ");
     scanf("%c", &colonnec);              // saisie caractère de la colonne
     colonnec=getchar();           //The C programming language - Kernighan & Ritchie
     d->colonne = transformer_carac_a_chiffre(colonnec);
     
     (d->ligne)++;*/
    
}


int verifier_deplacement(plateau *p, position d, int pas){
    int i,j, nb = 0;
    
    for(i = -1; i <= 1; i++)
        for(j = -1; j <= 1; j++)        // double boucle for pour regarder dans les 8 cases autours
            if(p->plateau[d.ligne + i][d.colonne + j] != 5){
                if(p->plateau[d.ligne + i][d.colonne + j] == 0 && pas == 1){     // si case vide, on peut marcher
                    nb++;
                    p->plateau[d.ligne + i][d.colonne + j] = 2;
                }
                else if((abs(p->plateau[d.ligne + i][d.colonne + j]) == 1) && (p->plateau[d.ligne + 2*i][d.colonne + 2*j] == 0)) {// si il y a un pion, on saute
                    nb++;
                    p->plateau[d.ligne + 2*i][d.colonne + 2*j] = -2;
                }
            }
    return nb;
}




void saisir_pion_depart(plateau *p, position *d, int pas){
    
    do{
        if(p->joueur == 1)
            do{
                saisir_coord_depart(*p, d); // fonction qui demande au joueur les coordonnées du pion qu'il veut jouer
            }while(((d->ligne < 1 || d->ligne > 10) || (d->colonne < 1 || d->colonne > 10)) || p->plateau[d->ligne][d->colonne] != 1);
        else
            do{
                saisir_coord_depart(*p, d); // fonction qui demande au joueur les coordonnées du pion qu'il veut jouer
            }while(((d->ligne < 1 || d->ligne > 10) || (d->colonne < 1 || d->colonne > 10)) || p->plateau[d->ligne][d->colonne] != -1);
    }while(verifier_deplacement(p, *d, pas) == 0); //!\ il faut regarder si le pion peut se déplacer
}

//int tester_coup(jeu p, position d, position a){
//}

void saisir_coord_arrive(plateau p, position *a){ // fonction qui demande au joueur les coordonnées du pion qu'il veut jouer
    
    
    do{
        printf("Saisir les coordonées d'arrivée : ");
        *a = saisir_coord();
        
        
        
        
        
        
        /*
         printf("Saisir la ligne d'arrivée : ");
         scanf("%d", &a->ligne);                  //saisie ligne à bouger
         printf("Saisir la colonne d'arrivée : ");
         scanf("%c", &colonnec);              // saisie caractère de la colonne
         colonnec=getchar();         //The C programming language - Kernighan & Ritchie
         a->colonne = transformer_carac_a_chiffre(colonnec);
         (a->ligne)++;
         printf("ligne : %d colonne %d", a->ligne, a->colonne);*/
    }while(abs(p.plateau[a->ligne][a->colonne]) != 2);
}


void nettoyer_2(plateau *p, position d){ // retrait des 2 et -2
    int i, j;
    
    for(i = d.ligne - 2; i <= d.ligne + 2; i++)
        for(j = d.colonne - 2; j <= d.colonne + 2; j++)
            if(abs(p->plateau[i][j]) == 2)
                p->plateau[i][j] = 0;
}


void jouer(plateau *p, position d,position a){
    
    if(p->plateau[d.ligne][d.colonne] == 1) //j1 ou 2 ?
        p->plateau[a.ligne][a.colonne] = 1;
    else
        p->plateau[a.ligne][a.colonne] = -1;
    p->plateau[d.ligne][d.colonne] = 0;
    nettoyer_2(p, d);
}


int tester_victoire(plateau p){
    int nb_pion_bien_place = 0, i ,j;
    
    if(p.joueur == 2)
        for(i = 1; i <= 5; i++) //boucle de passage du coin bas droit
            for(j = 1; j <= i; j++)// ''
                if(p.plateau[i+5][j+10-i] == -1) // es-ce un pion adverse ??
                    nb_pion_bien_place++;
    
    if(nb_pion_bien_place == 15)
        return -1;
    
    nb_pion_bien_place = 0;
    
    if(p.joueur == 1)
        for(i = 1; i <= 5; i++) //boucle de passage du coin haut gauche
            for(j = 1; j <= 6 - i; j++)
                if(p.plateau[i][j] == 1)
                    nb_pion_bien_place++;
  
    if(nb_pion_bien_place == 15)
        return 1;
    
    return 0;
}

// a supp dans version finale
void affdebug(plateau p){
    int i, j;
    
    for(i = 0; i <= 11; i++){
        for(j = 0; j <=11; j++){
            printf("%d ", p.plateau[i][j]);
        }
        printf("\n");
    }
}
