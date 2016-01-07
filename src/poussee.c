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
    
    
        int cpt=2,cpt2=0;
        if(piece_etre_animal(&plateau->piece[x][y]) && orientation==orientation_inverser(plateau->piece[x][y].orientation))
           {
               cpt2++;
           }
        while(plateau->piece[x][y].type!=case_vide && coordonnees_etre_dans_plateau(x, y))
        {
            
                if(plateau->piece[x][y].type==rocher)
                {
                    cpt=cpt-1;
                    coordonnees_appliquer_deplacement(&x, &y, orientation);
                    continue;
                }
                if(plateau->piece[x][y].orientation==orientation_inverser(orientation))
                {
                    cpt=cpt-2;
                }
                if(plateau->piece[x][y].orientation==orientation)
                {
                    cpt=cpt+2;
                }
            
                orientation_deplacement orientation_precedente=plateau->piece[x][y].orientation;
                coordonnees_appliquer_deplacement(&x, &y, orientation);
                if (coordonnees_etre_dans_plateau(x, y)==0) continue;
                if(piece_etre_animal(&plateau->piece[x][y]) && orientation_precedente==orientation_inverser(plateau->piece[x][y].orientation))
                {
                    cpt2++;
                }
            
        }
        if(cpt2==2) return 0;
        if(cpt>0)
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
    int compteur=0; // compteur de déplacement
    if(poussee_etre_valide(plateau, x, y, orientation))
    {
        
        while( coordonnees_etre_dans_plateau(x, y)==1 && piece_etre_case_vide(&plateau->piece[x][y])!=1  )
        {
            coordonnees_appliquer_deplacement(&x, &y, orientation);
            compteur++;
            
        }
        coordonnees_appliquer_deplacement(&x, &y, orientation_inverser(orientation));
        compteur--;
        
        while(compteur!=-2)
        {
            if (coordonnees_etre_dans_plateau(x, y)==0) break;
            else
            {plateau_modification_deplacer_piece(plateau, x, y, orientation, plateau->piece[x][y].orientation);
            
            coordonnees_appliquer_deplacement(&x, &y, orientation_inverser(orientation));
                compteur--;
            }
           
            
        }
        

        
    }
    

}

