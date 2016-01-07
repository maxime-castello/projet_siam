/**
 * **************************************************
 * **************************************************
 *   _____ _____  ______   _
 *  / ____|  __ \|  ____| | |
 * | |    | |__) | |__    | |    _   _  ___  _ __
 * | |    |  ___/|  __|   | |   | | | |/ _ \| '_ \
 * | |____| |    | |____  | |___| |_| | (_) | | | |
 *  \_____|_|    |______| |______\__, |\___/|_| |_|
 *                                __/ |
 *                               |___/
 * **************************************************
 * **************************************************
 *
 *
 * Role general de ce fichier
 * --------------------------------------------------------------
 * Le mode interactif permet d'interfacer le jeu de siam avec
 *  la commande d'utilisateur en ligne de commande.
 *
 * Role des fonctions et note d'implementation
 * --------------------------------------------------------------
 * Les fonctions proposee dans le mode interactifs permettent de
 *  demarer le controle du jeu en ligne de commande.
 * Les fonctions du mode interactif ont pour but de dialoguer avec
 *  un utilisateur (potentiellement non programmeur). Elles
 *  affichent donc les messages de dialogue avec l'utilisateur.
 * Le mode interactif vient egalement realiser la synchronisation
 *  des fonctions de gestion du jeu (demande d'action, realisation
 *  d'actions, affichage informatif, enregistrement et lecture
 *  a partir de fichiers et affichage du vainqueur).
 * Comme les fonctions traitent de demandent utilisateurs elles
 *  ne peuvent pas presuposer de contraintes de type "assertions"
 *  sur les variables completees interactivement.
 *
 *
 * Notion d'abstraction
 * --------------------------------------------------------------
 * Ce niveau d'abstraction a pour role de realiser l'interface entre
 *  une entree sous forme de demande utilisateur vers l'API du programme.
 * Le mode interactif ne vient utiliser que des fonctions de hauts
 *  niveaux du jeu qu'il utilise comme une librairie externe.
 */





#ifndef MODE_INTERACTIF_H
#define MODE_INTERACTIF_H

#include "jeu_siam.h"
/**
 * Fonction mode_interactif_lancer:
 * *************************
 *    Permet de lancer une partie de Siam ou le joueur peut intéragir.
 *	  Cette fonction va utiliser les fonction jeu initialiser et action initialiser.
 *    Elle permet aussi aux joueur de choisir une action chaqu'un leur tour
 *    et ne s'arrête que lorsque un joueur gagne.
 *    Necessite:
 *      Elle ne nécessite rien car elle initialise le jeu.
 *    Garantie:
 *      Une partie entre deux joueurs jusqu'à ce qu'un joueur gagne.
 */
void mode_interactif_lancer();
/**
 * Fonction mode_interactif_parametres_etre_valides:
 * *************************
 *    Vérifie que les coordonnées données et l'orientation sont des paramètres valides.
 *    Dans le cas ou l'introduction de la piece est possible, le jeu est
 *    Necessite:
 *      - Un pointeur non NULL vers un jeu integre modifiable.
 *      - Deux coordonnees entieres (x,y).
 *      - Une orientation.
 *    Garantie:
 *      - Si l'orientation est invalide la fonction retourne "Orientation invalide".
 *      - Si les coordonnees sont fausses la fonction retourne "Coordonnees invalides".
 *		- retourne 1 si les paramètres sont valide et 0 dans le cas contraire
 */
int mode_interactif_parametres_etre_valides(const jeu_siam* jeu,int x,int y,orientation_deplacement orientation);
/**
 * Fonction mode_interactif_introduire_nouvelle_piece:
 * *************************
 *    Tente d'introduire une nouvelle piece du jeu sur le plateau.
 *    L'introduction est possible si:
 *     - les coordonnees designent une piece modifiable par le joueur courant.
 *     - l'introduction de la piece designee dans la direction donnee est
 *        permise par les regles du jeu (poussee comprise).
 *
 *    Dans le cas ou l'introduction de la piece est possible, le jeu est
 *    mis a jour, en utilisant la fonction
 *    api_siam_tenter_introduire_nouvelle_piece_si_possible.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers un jeu integre modifiable.
 *      - Deux coordonnees entieres (x,y).
 *      - Une orientation que doit prendre la piece introduite.
 *    Garantie:
 *      - Si l'introduction est possible suivant les regle du jeu, alors
 *         le jeu est mise a jour.
 *      - Si le coup n'est pas possible, la fonction renvoie "Echec introduction piece impossible".
 *		  ou si les coordonnées sont mauvaise : "Introduction piece impossible aux coordonnees x y".
 *
 */
void mode_interactif_introduire_nouvelle_piece(jeu_siam* jeu,int x,int y,orientation_deplacement orientation,int* victoire);
/**
 * Fonction mode_interactif_deplacer_piece:
 * *************************
 *    Tente de deplacement une nouvelle piece du jeu sur le plateau avec un
 *     changement d'orientation possible.
 *
 *    Le deplacement est possible si:
 *     - les coordonnees designent une piece modifiable par le joueur courant.
 *     - le deplacement dans la direction indiquee est possible (poussee
 *       comprise)
 *     - la piece peut prendre l'orientation finale designee.
 *
 *    Dans le cas ou le deplacement de la piece est possible, le jeu est
 *     mis a jour et la structure via api_siam_tenter_deplacer_piece_si_possible.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers un jeu integre modifiable.
 *      - Deux coordonnees entieres (x,y).
 *      - Une direction de deplacement.
 *      - Une orientation de piece apres deplacement.
 *    Garantie:
 *      - Si le deplacement est possible suivant les regle du jeu, alors
 *         le jeu est mise a jour.
 *      - Si le coup n'est pas possible, la fonction renvoie "Echec deplacement piece impossible".
 *		  ou si les coordonnées sont mauvaise : "Deplacement piece (x,y) impossible".
 */
void mode_interactif_deplacer_piece(jeu_siam* jeu,int x,int y,orientation_deplacement deplacement,orientation_deplacement orientation,int* victoire);
/**
 * Fonction mode_interactif_changer_orientation:
 * *************************
 *    Tente de changer l'orientation d'une piece du jeu.
 *
 *    Le changement d'orientation est possible si:
 *     - les coordonnees designent une piece modifiable par le joueur courant.
 *     - la piece peut prendre l'orientation finale designee.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers un jeu integre modifiable.
 *      - Deux coordonnees entieres (x,y).
 *      - Une orientation de piece apres changement.
 *    Garantie:
 *      - Si il est possible de deplacer la piece designee par le
 *        joueur courant dans la direction indiquee et ayant l'orientation
 *        souhaitee apres deplacement, alors le jeu est modifie en deplacant
 *        cette piece.
 *        Le jeu passe le tour au joueur suivant.
 *      - Si le deplacement de la piece n'est pas possible dans les
 *        conditions indiquees, alors le jeu n'est pas modifie et la fonction retourne
 *		  "Echec changement orientation piece impossible" ou
 *		  "Changement orientation piece (x,y) impossible ".
 */
void mode_interactif_changer_orientation(jeu_siam* jeu,int x,int y,orientation_deplacement orientation);
/**
 * Fonction mode_interactif_sauvegarder_jeu_fichier:
 * *************************
 *    Sauvegarde la partie sur le fichier "etat_courant.txt"
 *
 *    Necessite:
 *      - Un pointeur non NULL vers un jeu integre modifiable.
 *    Garantie:
 *      - Une sauvegarde dans etat_courant.txt.
 */
void mode_interactif_sauvegarder_jeu_fichier(const jeu_siam* jeu);
/**
 * Fonction mode_interactif_lire_fichier:
 * *************************
 *    Lit un fichier donné en paramètre puis sauvegarde le jeu dedans.
 *
 *    Necessite:
 *      - Un pointeur non NULL vers un jeu integre modifiable.
 *      - Un fichier qui existe et qui est accesible.
 *    Garantie:
 *      - Si le fichier et le pointeur sont valide il suavegarde le jeu sur le fichier.
 *      - Si le fichier n'est pas valide indique "Fichier %s non accessible en lecture".
 */
void mode_interactif_lire_fichier(jeu_siam* jeu,const char* filename);

#endif

