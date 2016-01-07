#include "jeu_siam.h"
#include "joueur.h"

#include "entree_sortie.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int jeu_etre_integre(const jeu_siam* jeu)
{
    assert(jeu!=NULL);

    //verification du joueur integre
    const int joueur=jeu->joueur;
    if(joueur_etre_integre(joueur)==0)
        return 0;

    //verification du plateau integre
    const plateau_siam* plateau=&jeu->plateau;
    if(plateau_etre_integre(plateau)==0)
        return 0;

    return 1;
}


void jeu_initialiser(jeu_siam* jeu)
{
    
    plateau_initialiser(&jeu->plateau);
    assert(jeu!=NULL);
    /*jeu->plateau.piece[3][3].type=elephant;
    jeu->plateau.piece[3][3].orientation=gauche;
    jeu->plateau.piece[0][3].type=elephant;
    jeu->plateau.piece[0][3].orientation=droite;
    jeu->plateau.piece[1][3].type=elephant;
    jeu->plateau.piece[1][3].orientation=bas;
    jeu->plateau.piece[2][3].type=rhinoceros;
    jeu->plateau.piece[2][3].orientation=droite;*/

    jeu->joueur=0;
}





void jeu_changer_joueur(jeu_siam* jeu)
{
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu));

    joueur_changer(&jeu->joueur);

    assert(jeu_etre_integre(jeu));

}


int jeu_verifier_type_piece_a_modifier(const jeu_siam* jeu,int x,int y)
{
    assert(jeu_etre_integre(jeu));
    assert(coordonnees_etre_dans_plateau(x,y));
    const piece_siam* piece=plateau_obtenir_piece_info(&jeu->plateau,x,y);
    assert(piece!=NULL);
    
    int num_joueur=jeu->joueur;
    type_piece type=piece->type;
    
    if (type_etre_animal(type)==0)
        return 0;
    
    if(joueur_etre_type_animal(num_joueur,type)==1)
        return 1 ;
    
    return 0;

}



void jeu_afficher(const jeu_siam* jeu)
{
    assert(jeu!=NULL);

    //utilisation d'une fonction generique avec affichage sur
    //  la ligne de commande.
    entree_sortie_ecrire_jeu_pointeur_fichier(stdout,jeu);
}



type_piece jeu_obtenir_type_animal_courant(const jeu_siam* jeu)
{
    assert(jeu_etre_integre(jeu));
    return joueur_obtenir_animal(jeu->joueur);
}

