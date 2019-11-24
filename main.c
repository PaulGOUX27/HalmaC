#include "fonction.h"

int main(void)
{
    position position_depart, position_arrive;
    plateau jeu;
    
    int pas;
    char rejouer;
    //int ligneD, colonneD, ligneA, colonneA; // A Supp
    //int tour;
    int compteur = 0;
    //int joueur;
    //int plateau[N][N];
    
    initialiser(&jeu);
    
    do{
        position_depart.ligne = -1;
        position_depart.colonne = -1;
        pas = 1;
        compteur++;
        jeu.tour = (compteur + 1) / 2;
        jeu.joueur = (compteur - 1)  % 2 + 1;
        
        afficher(jeu, position_depart);
        
        saisir_pion_depart(&jeu, &position_depart, pas); //PK JE REGARDE LE PAS ??
        
        afficher(jeu, position_depart);
        
        saisir_coord_arrive(jeu, &position_arrive);
        jouer(&jeu, position_depart, position_arrive);
        
        //afficher(jeu, position_depart);
        
        if(abs(position_depart.ligne - position_arrive.ligne) == 2 || abs(position_depart.colonne - position_arrive.colonne) == 2){
            pas = 0;
            do{
                do{
                    afficher(jeu, position_arrive);
                    
                    printf("voulez vous rejouer ? (O/N)");
                    scanf("%c", &rejouer);
                    rejouer = getchar();
                    
                }while(tolower(rejouer) != 'o' && tolower(rejouer) != 'n');
                if(tolower(rejouer) == 'o'){
                    
                    position_depart.ligne = position_arrive.ligne;
                    position_depart.colonne = position_arrive.colonne;
                    
                    verifier_deplacement(&jeu, position_depart, pas);
                    
                    afficher(jeu, position_depart);
                    
                    saisir_coord_arrive(jeu, &position_arrive);
                    jouer(&jeu, position_depart, position_arrive);
                    
                    //afficher(jeu, position_depart);
                }
                
            }while(tolower(rejouer) != 'n');//j'arrete de faire des sauts
        }
        
    }while(tester_victoire(jeu) == 0);
    
    afficher(jeu, position_depart);
    
    if(tester_victoire(jeu) == -1){
        couleur("31");
        printf("Le vainqueur est le joueur $ !");
        couleur("0");
    }
    else{
        couleur("34");
        printf("Le vainqueur est le joueur & !");
        couleur("0");
    }
}
