#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "api_siam.h"
#include "plateau_modification.h"

coup_jeu api_siam_tenter_introduire_nouvelle_piece_si_possible(jeu_siam* jeu,
                                                               int x,int y,
                                                               orientation_deplacement orientation)
{
    assert(jeu!=NULL);
    assert(jeu_etre_integre(jeu));
    assert(coordonnees_etre_dans_plateau(x, y));
    assert(orientation_etre_integre_deplacement(orientation));
    coup_jeu coup;
    coup_jeu_initialiser(&coup);
    
    if(plateau_modification_introduire_piece_etre_possible(&jeu->plateau, x, y, jeu_obtenir_type_animal_courant(jeu), orientation)==1 )
    {
        
        
            coup.valide=1;
            puts("coup valide\n");
            plateau_modification_introduire_piece(&jeu->plateau, x, y, jeu_obtenir_type_animal_courant(jeu), orientation);
            jeu_changer_joueur(jeu);
    }
    
    else
    {

            coup.valide=0;
            puts("coup invalide\n");
    }
    

    /*if(coup.valide==1)
    {
        jeu_changer_joueur(jeu);
    }*/
    
    return coup;
}



coup_jeu api_siam_tenter_deplacer_piece_si_possible(jeu_siam* jeu,
                                                    int x,int y,
                                                    orientation_deplacement deplacement,
                                                    orientation_deplacement orientation)
{
    assert(jeu_etre_integre(jeu));
    assert(coordonnees_etre_dans_plateau(x, y));
    assert(orientation_etre_integre_deplacement(deplacement));
    assert(orientation_etre_integre_deplacement(orientation));
    coup_jeu coup;
    coup_jeu_initialiser(&coup);
    
    if ( (plateau_modification_deplacer_piece_etre_possible(&jeu->plateau,x,y,deplacement,orientation)==1)
          && (jeu_verifier_type_piece_a_modifier(jeu, x, y)==1) )
    {
      coup.valide=1;
      puts("coup valide\n");
      plateau_modification_deplacer_piece(&jeu->plateau,x,y,deplacement,orientation);

    }
    else
    {
        coup.valide=0;
        puts("coup invalide\n");
    }
    if(coup.valide==1)
        jeu_changer_joueur(jeu);
    return coup;
    
}



coup_jeu api_siam_tenter_changer_orientation_piece_si_possible(jeu_siam* jeu,int x,int y,orientation_deplacement orientation)
{
    assert(jeu!=NULL);
    assert(coordonnees_etre_dans_plateau(x, y));
    assert(orientation_etre_integre_deplacement(orientation));

    coup_jeu coup;
    coup_jeu_initialiser(&coup);

    if (plateau_modification_changer_orientation_piece_etre_possible(&jeu->plateau,x,y,orientation)==1 && jeu_verifier_type_piece_a_modifier(jeu, x, y)==1)
    {
      coup.valide=1;
      puts("coup valide\n");
      plateau_modification_changer_orientation_piece(&jeu->plateau,x,y,orientation);
    }
    else
    {
        coup.valide=0;
        puts("coup invalide\n");
    }
    if(coup.valide==1)
        jeu_changer_joueur(jeu);
    return coup;
}
