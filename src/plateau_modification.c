#include "plateau_modification.h"
#include "coordonnees_plateau.h"

#include "poussee.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



int plateau_modification_introduire_piece_etre_possible(const plateau_siam* plateau,
                                                        int x,int y,
                                                        type_piece type,
                                                        orientation_deplacement orientation)
{
    assert(plateau_etre_integre(plateau));
    
    assert(type_etre_animal(type));
    assert(orientation_etre_integre_deplacement(orientation));
    
    if( (coordonnees_etre_bordure_plateau(x, y)==1) && poussee_etre_valide(plateau, x, y, orientation) && plateau_denombrer_type(plateau, type)<5 ) 
    {
        
        return 1;
    }
    else
    {
        
        return 0;
    }

}


void plateau_modification_introduire_piece(plateau_siam* plateau,
                                           int x,int y,
                                           type_piece type,
                                           orientation_deplacement orientation)
{
    assert(plateau_etre_integre(plateau));
    assert(coordonnees_etre_bordure_plateau(x, y));
    assert(type_etre_animal(type));
    assert(orientation_etre_integre_deplacement(orientation));
    
    if ((plateau_modification_introduire_piece_etre_possible(plateau, x, y, type, orientation)==1))
        {
            if (piece_etre_case_vide(&plateau->piece[x][y])==1)
            {
                piece_siam* piece=&plateau->piece[x][y];
                piece_definir(piece,type,orientation);
            }
            else
            {
                poussee_realiser(plateau, x, y, type, orientation);
                piece_definir(&plateau->piece[x][y],type,orientation);
            }
        }
    
}


int plateau_modification_changer_orientation_piece_etre_possible(const plateau_siam* plateau,int x0,int y0,orientation_deplacement orientation)
{
    
    assert(plateau_etre_integre(plateau));
    assert(coordonnees_etre_dans_plateau(x0, y0));
    assert(orientation_etre_integre_deplacement(orientation));
    
    const piece_siam* piece=plateau_obtenir_piece_info(plateau, x0, y0);
    
    assert(piece_etre_integre(piece));
    

    if(piece_etre_animal(piece)==1 && piece->orientation!=orientation)
        return 1;
    if (piece_etre_animal(piece)==1 && piece->orientation==orientation)
        return 0;
    return 0;
    
}



void plateau_modification_changer_orientation_piece(plateau_siam* plateau,int x0,int y0,orientation_deplacement orientation)
{
    assert(plateau_etre_integre(plateau));
    assert(plateau_modification_changer_orientation_piece_etre_possible(plateau, x0, y0, orientation)==1);
    
    piece_siam* piece=plateau_obtenir_piece(plateau, x0, y0);
    piece->orientation=orientation;
    
    
}


int plateau_modification_deplacer_piece_etre_possible(const plateau_siam* plateau,
                                                      int x0,int y0,
                                                      orientation_deplacement direction_deplacement,
                                                      orientation_deplacement orientation)
{
    assert(plateau_etre_integre(plateau));
    
    assert(coordonnees_etre_dans_plateau(x0, y0));
    assert(orientation_etre_integre_deplacement(direction_deplacement));
    assert(orientation_etre_integre(orientation));
    
    
    if(type_etre_animal(plateau->piece[x0][y0].type))
    {
            orientation_deplacement orientation_piece_qui_pousse=plateau->piece[x0][y0].orientation;
            if ( (x0==0 && direction_deplacement==gauche) || (x0==4 && direction_deplacement==droite) || (y0==0 &&          	    direction_deplacement==bas) || (y0==4 && direction_deplacement==haut) )
    {
        return 1;
    }
            coordonnees_appliquer_deplacement(&x0,&y0,direction_deplacement);
        
            if( coordonnees_etre_dans_plateau(x0, y0)==0 || poussee_etre_valide(plateau, x0, y0, direction_deplacement )   )
            {
                if ( piece_etre_case_vide(&plateau->piece[x0][y0])==0 && orientation!=direction_deplacement )
                {
                    puts("orientation finale non valide");
                    return 0;
                    
                }
                if(piece_etre_case_vide(&plateau->piece[x0][y0])==0 && orientation_piece_qui_pousse!=direction_deplacement )
                {
                    puts("orientation de la piece qui pousse differente de la direction de deplacement");
                    return 0;
                }
                return 1;
            }
    }
    if (poussee_etre_valide(plateau, x0, y0, direction_deplacement)) return 1;
    return 0;
}


void plateau_modification_deplacer_piece(plateau_siam* plateau,
                                         int x0,int y0,
                                         orientation_deplacement direction_deplacement,
                                         orientation_deplacement orientation_final)
{
    assert(plateau_etre_integre(plateau));
    assert(coordonnees_etre_dans_plateau(x0, y0));
    assert(orientation_etre_integre_deplacement(direction_deplacement));
    assert(orientation_etre_integre(orientation_final));
    
    if ( (x0==0 && direction_deplacement==gauche) || (x0==4 && direction_deplacement==droite) || (y0==0 && direction_deplacement==bas) || (y0==4 && direction_deplacement==haut) )
    {
        piece_definir_case_vide(&plateau->piece[x0][y0]);
        plateau->piece[x0][y0].orientation=aucune_orientation;
    }
    
    if(coordonnees_etre_dans_plateau(x0, y0))
    {
        piece_siam* piece=plateau_obtenir_piece(plateau,x0,y0);
        type_piece type=piece->type;
        if(plateau_modification_deplacer_piece_etre_possible(plateau,x0,y0,direction_deplacement,orientation_final))
            {
                int x=x0;
                int y=y0;
                
                coordonnees_appliquer_deplacement(&x0,&y0,direction_deplacement);
                if (coordonnees_etre_dans_plateau(x0, y0)==0)
                {
                    coordonnees_appliquer_deplacement(&x0,&y0,orientation_inverser(direction_deplacement));

                }
                else if (piece_etre_case_vide(&plateau->piece[x0][y0]))
                {
                    piece_definir(&plateau->piece[x0][y0],type,orientation_final);
                }
                else
                {
                    
                    poussee_realiser(plateau, x0, y0, plateau->piece[x0][y0].type, direction_deplacement);
                }
                
                piece_definir_case_vide(&plateau->piece[x][y]);
            }
    }
   
}


