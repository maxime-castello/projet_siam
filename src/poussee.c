#include "plateau_siam.h"
#include "poussee.h"
#include "condition_victoire_partie.h"
#include "api_siam.h"
#include "plateau_modification.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int poussee_etre_valide(const plateau_siam* plateau ,int x, int y, orientation_deplacement orientation)
{
    assert(plateau_etre_integre(plateau));
    assert(coordonnees_etre_dans_plateau(x,y));
    assert(orientation_etre_integre_deplacement(orientation));
    
        if(plateau->piece[x][y].type==case_vide)
        {
           return 1;
        }
    

        /* on initialise deux compteur, un pour compter le poids des pieces: un animal dans l'orientation du déplacement ou dans l'orientation inverse du déplacement vaut 2, un rocher vaut 1. On initialise ce compteur à deux car on compte la piece poussante.
            Puis un deuxième compteur qui compte le nombre d'orientation inverse*/
        int cpt_poids_piece=2,cpt_orientation_inverse=0;
        if(piece_etre_animal(&plateau->piece[x][y]) && orientation==orientation_inverser(plateau->piece[x][y].orientation))
           {
               cpt_orientation_inverse++;
           }
        while(plateau_exister_piece(plateau, x, y) && coordonnees_etre_dans_plateau(x, y))
        {
            
                if(plateau->piece[x][y].type==rocher)
                {
                    cpt_poids_piece=cpt_poids_piece-1;
                    if ( (x==0 && orientation==gauche) || (x==4 && orientation==droite) || (y==0 && orientation==bas) || (y==4 && orientation==haut) )
                    {break;}
                    coordonnees_appliquer_deplacement(&x, &y, orientation);
                    
                    continue;
                }
                if(plateau->piece[x][y].orientation==orientation_inverser(orientation))
                {
                    cpt_poids_piece=cpt_poids_piece-2;
                }
                if(plateau->piece[x][y].orientation==orientation)
                {
                    cpt_poids_piece=cpt_poids_piece+2;
                }
            
                orientation_deplacement orientation_precedente=plateau->piece[x][y].orientation;
                // boucle pour éviter de sortir du tableau
                if ( (x==0 && orientation==gauche) || (x==4 && orientation==droite) || (y==0 && orientation==bas) || (y==4 && orientation==haut) )
                {
                    break;
                }
                coordonnees_appliquer_deplacement(&x, &y, orientation);
            
                if(piece_etre_animal(&plateau->piece[x][y]) && orientation_precedente==orientation_inverser(plateau->piece[x][y].orientation))
                {
                    cpt_orientation_inverse++;
                }
            
        }
        if(cpt_orientation_inverse==2)
        {
           return 0;
        }
        if(cpt_poids_piece>0)
        {
          return 1;
        }
                
        return 0;
            
}


void poussee_realiser(plateau_siam* plateau ,
                      int x, int y,
                      type_piece type,
                      orientation_deplacement orientation)
            
{
    assert(plateau_etre_integre(plateau));
    assert(coordonnees_etre_dans_plateau(x,y));
    assert(orientation_etre_integre_deplacement(orientation));
    int compteur_deplacement=1; // compteur de déplacement
    if(poussee_etre_valide(plateau, x, y, orientation))
    {
        
        while( coordonnees_etre_dans_plateau(x, y)==1 && piece_etre_case_vide(&plateau->piece[x][y])!=1  )
        {
            // boucle pour éviter de sortir du tableau
            if ( (x==0 && orientation==gauche) || (x==4 && orientation==droite) || (y==0 && orientation==bas) || (y==4 && orientation==haut) )
            {
                break;
            }
            coordonnees_appliquer_deplacement(&x, &y, orientation);
            compteur_deplacement++;
        }
        
        if (piece_etre_case_vide(&plateau->piece[x][y])==1)
        {
            coordonnees_appliquer_deplacement(&x, &y, orientation_inverser(orientation));
            
            compteur_deplacement--;
        }
        
        while(compteur_deplacement!=-1)
        {
            plateau_modification_deplacer_piece(plateau, x, y, orientation, plateau->piece[x][y].orientation);
            // boucle pour éviter de sortir du tableau
            if ( (x==0 && orientation==droite) || (x==4 && orientation==gauche) || (y==0 && orientation==haut) || (y==4 && orientation==bas) )
            {
                break;
            }
            coordonnees_appliquer_deplacement(&x, &y, orientation_inverser(orientation));
            compteur_deplacement--;
           
            
        }
        

        
    } assert(plateau_etre_integre(plateau));
    

}

