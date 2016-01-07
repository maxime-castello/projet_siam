#include <stdio.h>
#include<stdlib.h>
#include "piece_siam.h"
#include "plateau_siam.h"
#include "jeu_siam.h"
#include "api_siam.h"
#include "mode_interactif.h"
#include "type_piece.h"
#include "plateau_modification.h"


void test_type_etre_animal()
{
    puts("Test type_etre_animal");

    if(type_etre_animal(elephant)!=1)
        puts("elephant KO");

    if(type_etre_animal(rhinoceros)!=1)
        puts("rhinoceros KO");

    if(type_etre_animal(rocher)!=0)
        puts("rocher KO");
    if(type_etre_animal(case_vide)!=0)
        puts("case vide KO");

    int k=0;
    for(k=4;k<20;++k)
        if(type_etre_animal(k)!=0)
            printf("valeur %d KO\n",k);

}
/*void test_piece_etre_animal()
{
    puts("test piece etre animal");
    piece_siam* piece=NULL;//malloc(sizeof(piece_siam));
    piece->type=elephant;//test n°1
    //piece->type=rocher;//test n°2
    if(piece_etre_animal(piece)==1) puts("la pièce est un animal");
    else puts("ce n'est pas un animal");
}
void test_piece_etre_rocher()
{
    puts("test piece etre rocher");
    piece_siam* piece=NULL;//malloc(sizeof(piece_siam));
    piece->type=elephant;//test n°1
    //piece->type=rocher;//test n°2
    if(piece_etre_animal(piece)==1) puts("la pièce est un rocher");
    else puts("ce n'est pas un rocher");
}

void test_piece_definir()
{
    puts("test piece definir");
    piece_siam* piece=NULL;//malloc(sizeof(piece_siam));
    type_piece type=elephant;
    orientation_deplacement orientation=haut;
    piece_definir(piece,type,orientation);
    printf("%s %s\n",type_nommer(piece->type),orientation_nommer(piece->orientation));
}

void test_piece_etre_integre()
{
    puts("test piece etre integre");
    
    piece_siam* piece=malloc(sizeof(piece_siam));
    
    piece->type=elephant;
    piece->orientation=droite;
    
    if(piece_etre_integre(piece)==1)
        puts("piece integre");
    else
        puts("piece non-integre");
    
    free(piece);

}*/

void test_coordonnees_etre_bordure_plateau()
{
    puts("test_coordonnees_etre_bordure_plateau");
    int x=0,y=0;
    for (y=0;y<NBR_CASES;y++)
        
    {
        if (coordonnees_etre_bordure_plateau(0,y)!=1)
            puts(" 1ere colonne bordure KO");
        
        else if (coordonnees_etre_bordure_plateau(NBR_CASES-1, y)!=1)
            puts("derniere colone bordure KO");
    }
    
    for(x=0; x<NBR_CASES;x++)
    {
        
        if (coordonnees_etre_bordure_plateau(x, 0)!=1)
            puts(" 1ere ligne bordure KO");
        else if (coordonnees_etre_bordure_plateau(x, NBR_CASES-1)!=1)
            puts("derniere ligne bordure KO");
    }
    
}
void test_jeu_verifier_type_piece_a_modifier()
{
    puts("test_jeu_verifier_type_piece_a_modifier");
    jeu_siam* jeu=malloc(sizeof(jeu_siam));
    jeu_initialiser(jeu);
    jeu_siam* jeu2=malloc(sizeof(jeu_siam));
    jeu_initialiser(jeu2);
    jeu2->joueur=1;
    plateau_siam plateau;
    plateau_initialiser(&plateau);
    jeu->plateau=plateau;
    jeu2->plateau=plateau;
    
    piece_siam* p1 = plateau_obtenir_piece(&jeu->plateau,2,3);
    piece_siam* p2 = plateau_obtenir_piece(&jeu2->plateau,2,4);
    p1->type=elephant;
    p1->orientation=haut;
    p2->type=rhinoceros;
    p2->orientation=haut;
    
    if (jeu_verifier_type_piece_a_modifier(jeu, 2, 3)!=1)
        puts("joueur 0 elephant KO");
    if (jeu_verifier_type_piece_a_modifier(jeu2, 2, 4)!=1)
        puts("joueur 1 rhino KO");
   
    free(jeu);
    free(jeu2);
}

void test_jeu_obtenir_type_animal_courant()
{
    puts("test_jeu_obtenir_type_animal_courant");
    jeu_siam jeu;
    jeu_initialiser(&jeu);
    jeu_siam jeu2;
    jeu_initialiser(&jeu2);
    jeu2.joueur=1;
    
    if(jeu_obtenir_type_animal_courant(&jeu)!=elephant)
        puts("joueur 0 elephant KO");
    if(jeu_obtenir_type_animal_courant(&jeu2)!=rhinoceros)
        puts("joueur 1 rhino KO");
}

void test_plateau_modification_changer_orientation_piece_etre_possible()
{
    puts("test_plateau_modification_changer_orientation_piece_etre_possible");
    plateau_siam plateau;
    plateau_initialiser(&plateau);
    piece_siam* p1 = plateau_obtenir_piece(&plateau,2,3);
    p1->type=elephant;
    p1->orientation=haut;
    
    if(plateau_modification_changer_orientation_piece_etre_possible(&plateau, 2, 3, droite)!=1)
        puts(" changement orientation KO");
    if(plateau_modification_changer_orientation_piece_etre_possible(&plateau, 2, 3, haut)!=0)
        puts(" meme orientation KO");
    
}

void test_plateau_modification_changer_orientation_piece()
{
    puts("test_plateau_modification_changer_orientation_piece");
    plateau_siam plateau;
    plateau_initialiser(&plateau);
    piece_siam* p1 = plateau_obtenir_piece(&plateau,2,3);
    p1->type=elephant;
    p1->orientation=haut;
    
    plateau_modification_changer_orientation_piece(&plateau, 2, 3, gauche);
    if (p1->orientation!=gauche)
        puts("chgt orientation KO");

    plateau_modification_changer_orientation_piece(&plateau, 2, 3, droite);
    if (p1->orientation!=droite)
        puts("chgt orientation KO");
    
    plateau_modification_changer_orientation_piece(&plateau, 2, 3, bas);
    if (p1->orientation!=bas)
        puts("chgt orientation KO");
    
}

void test_lancer()
{
    test_type_etre_animal();
    test_coordonnees_etre_bordure_plateau();
    test_jeu_verifier_type_piece_a_modifier();
    test_jeu_obtenir_type_animal_courant();
    test_plateau_modification_changer_orientation_piece_etre_possible();
    test_plateau_modification_changer_orientation_piece();

}


int main()
{
    mode_interactif_lancer();
    //test_lancer();
    return 0;
}
