#include "piece_siam.h"
#include"type_piece.h"
#include "orientation_deplacement.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int piece_etre_integre(const piece_siam* piece)
{
    assert(piece!=NULL);
    
    type_piece type=piece->type;
    orientation_deplacement orientation=piece->orientation;

    if ( (type_etre_animal(type)==1 && orientation_etre_integre_deplacement(orientation)==1)
        || ((type_etre_animal(type))==0 && orientation==aucune_orientation) )
    {
        return 1;
    }
    else
        return 0;
}

void piece_initialiser(piece_siam* piece)
{
    assert(piece!=NULL);

    piece_definir(piece,case_vide,aucune_orientation);

    assert(piece_etre_integre(piece));
}


int piece_etre_animal(const piece_siam* piece)
{
    
    assert(piece_etre_integre(piece));
    
    return type_etre_animal(piece->type);
    
    
}

int piece_etre_rocher(const piece_siam* piece)
{
    assert(piece!=NULL);
    assert(piece_etre_integre(piece)==1);
   
    if(piece->type==rocher)
        return 1;
    
    else
        
        return 0;
    
}


int piece_etre_case_vide(const piece_siam* piece)
{
    assert(piece!=NULL);
    assert(piece_etre_integre(piece)==1);

    if(piece->type==case_vide)
        return 1;
    
    else
        return 0;
}






void piece_definir(piece_siam* piece,type_piece type,orientation_deplacement orientation)
{
    assert(piece!=NULL);
    assert(piece_etre_integre(piece));
    assert(type_etre_integre(type));
    assert(orientation_etre_integre(orientation));  

    /*if(type_etre_animal(type)==1 && orientation_etre_integre_deplacement(orientation)==1)
    {
        piece->type=type;
        piece->orientation=orientation;
    }
    if(type_etre_animal(type)==0 && orientation==aucune_orientation)
    {
        piece->type=type;
        piece->orientation=orientation;
    }*/
    
     piece->type=type;
     piece->orientation=orientation;
     assert(piece_etre_integre(piece));
}


void piece_definir_rocher(piece_siam* piece)
{
    assert(piece!=NULL);
    
    piece->type=rocher;
    piece->orientation=aucune_orientation;

}

void piece_definir_case_vide(piece_siam* piece)
{
    assert(piece!=NULL);
    
    piece->type=case_vide;
    piece->orientation=aucune_orientation;
   
}





orientation_deplacement piece_recuperer_orientation_animal(const piece_siam* piece)
{
    assert(piece!=NULL);
    assert(piece_etre_integre(piece));
    assert(piece_etre_animal(piece));

    return piece->orientation;
}


void piece_afficher(const piece_siam* piece)
{
    assert(piece!=NULL);

    printf("%s,%s\n",type_nommer(piece->type),orientation_nommer(piece->orientation));
}

void piece_afficher_nom_cours(const piece_siam* piece)
{
    assert(piece!=NULL);

    printf("%s",type_nommer_nom_cours(piece->type));
    if(piece_etre_animal(piece))
        printf("-%s\n",orientation_nommer_nom_cours(piece->orientation));
}


piece_siam piece_correspondre_nom_cours(const char* nom_cours)
{
    assert(nom_cours!=NULL);
    assert(strlen(nom_cours)==3);

    //Possibilites:
    //
    // - nom vaut "***" -> case vide
    // - nom vaut "RRR" -> rocher
    // - nom commence par "e-" ou "r-"
    //     Alors il s'agit d'un animal.
    //     -> Recuperer le 3eme caractere
    //     -> Le convertir dans l'orientation de l'animal.
    //  - Si aucun des cas precedent, alors affiche erreur.

    piece_siam piece;
    piece_initialiser(&piece);


    if(strncmp(nom_cours,"***",3)==0)
    {
        piece_definir_case_vide(&piece);
    }
    else if(strncmp(nom_cours,"RRR",3)==0)
    {
        piece_definir_rocher(&piece);
    }
    else if((nom_cours[0]=='e' || nom_cours[0]=='r') && nom_cours[1]=='-')
    {
        const type_piece type=type_correspondre_caractere_animal(nom_cours[0]);
        const orientation_deplacement orientation=orientation_correspondre_caractere(nom_cours[2]);

        piece_definir(&piece,type,orientation);
    }
    else
    {
        printf("Erreur fonction %s\n",__FUNCTION__);
        abort();
    }

    return piece;

}
