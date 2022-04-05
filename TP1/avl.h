#ifndef __AVL__H__
#define __AVL__H__

#include "abr.h"

/* structure noeud presentee en cours */

typedef struct n_AVL {
    int cle;
    int bal;
    struct n_AVL *fgauche, *fdroite;
} noeud_AVL_t, *pnoeud_AVL_t;

typedef pnoeud_AVL_t Arbre_AVL_t;

Arbre_AVL_t convertToAVL(Arbre_t a);

void afficher_arbre_avl(Arbre_AVL_t a, int niveau);

int hauteur_arbre_r_avl(Arbre_AVL_t a);

void set_balance(Arbre_AVL_t a);

Arbre_AVL_t reequilibrage(Arbre_AVL_t A);

Arbre_AVL_t rotation_gauche(Arbre_AVL_t A);

Arbre_AVL_t rotation_droite(Arbre_AVL_t A);

Arbre_AVL_t double_rotation_gauche(Arbre_AVL_t A);

Arbre_AVL_t double_rotation_droite(Arbre_AVL_t A);

Arbre_AVL_t ajoute_cle(int x, Arbre_AVL_t A);

Arbre_AVL_t ajouter_noeud_AVL(Arbre_AVL_t a, Arbre_AVL_t n);


#endif