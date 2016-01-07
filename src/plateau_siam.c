#include "plateau_siam.h"
#include "entree_sortie.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



void plateau_initialiser(plateau_siam* plateau)
{
    // Initialise l'ensemble des cases du plateau a piece_vide
    // sauf les 3 cases du milieu avec un rocher (1,2), (2,2) et (3,2)
    //
    // L'etat de l'echiquier initial est le suivant:
    //
    // [4] *** | *** | *** | *** | *** |
    // [3] *** | *** | *** | *** | *** |
    // [2] *** | RRR | RRR | RRR | *** |
    // [1] *** | *** | *** | *** | *** |
    // [0] *** | *** | *** | *** | *** |
    //     [0]   [1]   [2]   [3]   [4]
    //



    int kx=0;
    for(kx=0 ; kx<NBR_CASES ; ++kx)
    {
        int ky=0;
        for(ky=0 ; ky<NBR_CASES ; ++ky)
        {

            piece_siam* piece=plateau_obtenir_piece(plateau,kx,ky);

            assert(piece!=NULL);

            if(ky==2 && (kx>=1 && kx<=3) )
                piece_definir_rocher(piece);
            else
                piece_definir_case_vide(piece);
        }
    }

    assert(plateau_etre_integre(plateau));
}

int plateau_etre_integre(const plateau_siam* plateau)
{
    int kx=0;
    assert(plateau!=NULL);
    for(kx=0;kx<NBR_CASES;kx++)
    {
        int ky=0;
        for(ky=0;ky<NBR_CASES;ky++)
        {
            if(piece_etre_integre(&(plateau->piece[kx][ky]))==0) return 0;
        }
    }
    int nb_rocher=plateau_denombrer_type(plateau,rocher);
    int nb_rhino=plateau_denombrer_type(plateau,rhinoceros);
    int nb_elephant=plateau_denombrer_type(plateau,elephant);
    if(nb_rhino>=0 && nb_elephant>=0 && nb_rocher>=0 && nb_rhino<6 && nb_elephant<6 && nb_rocher<=3)
        return 1;
    else
        return 0;
}


piece_siam* plateau_obtenir_piece(plateau_siam* plateau,int x,int y)
{
    assert(plateau!=NULL);
    assert(coordonnees_etre_dans_plateau(x,y));
    return &(plateau->piece[x][y]);
}

const piece_siam* plateau_obtenir_piece_info(const plateau_siam* plateau,int x,int y)
{
    assert(plateau!=NULL);
    assert(coordonnees_etre_dans_plateau(x,y));
    return &(plateau->piece[x][y]);
}



int plateau_denombrer_type(const plateau_siam* plateau,type_piece type)
{
    assert(plateau!=NULL);
    // Algorithme:
    //
    // Initialiser compteur <- 0
    // Pour toutes les cases du tableau
    //
    //Si case courante est du type souhaite
    //
    //Incremente compteur
    // Renvoie compteur
    int compteur=0;
    int kx=0;
    for(kx=0 ; kx<NBR_CASES ; ++kx)
    {
    int ky = 0;
    for(ky=0 ; ky<NBR_CASES ; ++ky)
    {
    const piece_siam* piece=
    plateau_obtenir_piece_info(plateau,kx,ky);
    assert(piece!=NULL);
    if(piece->type == type)
    compteur++;
    }
    }
    return compteur;
}
int plateau_exister_piece(const plateau_siam* plateau,int x,int y)
{
    assert(plateau_etre_integre(plateau)==1);
    assert(plateau!=NULL);
    assert(coordonnees_etre_dans_plateau(x,y));
    
    const piece_siam* piece=plateau_obtenir_piece_info(plateau,x,y);
    assert(piece!=NULL);
    if(piece->type == case_vide)
        return 0;
    else
        return 1;
}

void plateau_afficher(const plateau_siam* plateau)
{
    assert(plateau!=NULL);

    //utilisation d'une fonction generique d'affichage
    // le parametre stdout permet d'indiquer que l'affichage
    // est realise sur la ligne de commande par defaut.
    entree_sortie_ecrire_plateau_pointeur_fichier(stdout,plateau);

}
