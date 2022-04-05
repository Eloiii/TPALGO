#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

Arbre_AVL_t ajoute_noeud(Arbre_AVL_t pAvl, Arbre_AVL_t pAvl1);

Arbre_AVL_t convertToAVL(Arbre_t a) {
    if (a) {
        Arbre_AVL_t res = (Arbre_AVL_t) malloc(sizeof(noeud_AVL_t));
        res->cle = a->cle;
        res->bal = hauteur_arbre_r(a->fdroite) - hauteur_arbre_r(a->fgauche);

        res->fgauche = convertToAVL(a->fgauche);
        res->fdroite = convertToAVL(a->fdroite);

        return res;
    }
    return NULL;
}

void afficher_arbre_avl(Arbre_AVL_t a, int niveau) {
    int i;

    if (a != NULL) {
        afficher_arbre_avl(a->fdroite, niveau + 1);

        for (i = 0; i < niveau; i++)
            printf("\t");
        printf(" %d (%d)\n\n", a->cle, a->bal);

        afficher_arbre_avl(a->fgauche, niveau + 1);
    }
}


int hauteur_arbre_r_avl(Arbre_AVL_t a) {
    if (a == NULL)
        return -1;
    else
        return 1 + MAX(hauteur_arbre_r_avl(a->fgauche), hauteur_arbre_r_avl(a->fdroite));
}

void set_balance(Arbre_AVL_t a) {
    if (a != NULL) {
        a->bal = hauteur_arbre_r_avl(a->fgauche) - hauteur_arbre_r_avl(a->fdroite);
    }
}


Arbre_AVL_t rotation_gauche(Arbre_AVL_t a) {
    if (a) {
        Arbre_AVL_t a1 = a->fdroite;
        Arbre_AVL_t a2 = a1->fgauche;
        a1->fgauche = a;
        a->fdroite = a2;

        set_balance(a);
        set_balance(a1);

        return a1;
    }
    return NULL;

}


Arbre_AVL_t rotation_droite(Arbre_AVL_t A) {
    if (A) {
        Arbre_AVL_t A1 = A->fgauche;
        Arbre_AVL_t A2 = A1->fdroite;
        A1->fdroite = A;
        A->fgauche = A2;

        set_balance(A);
        set_balance(A1);

        return A1;
    }
    return NULL;
}

Arbre_AVL_t double_rotation_gauche(Arbre_AVL_t a) {
    if (a) {
        Arbre_AVL_t a1 = a;
        Arbre_AVL_t a2 = a1->fdroite;
        a1->fdroite = rotation_droite(a2);
        a1 = rotation_gauche(a1);
        set_balance(a1);
        return a1;
    }
    return NULL;
}

Arbre_AVL_t double_rotation_droite(Arbre_AVL_t a) {
    if (a) {
        Arbre_AVL_t a1 = a;
        Arbre_AVL_t a2 = a1->fgauche;
        a1->fgauche = rotation_gauche(a2);
        a1 = rotation_droite(a1);
        set_balance(a1);
        return a1;
    }
    return NULL;
}

Arbre_AVL_t reequilibrage(Arbre_AVL_t a) {
    if (a->bal == 2) {
        if (a->fdroite->bal >= 0)
            return rotation_gauche(a);
        else {
            a->fdroite = rotation_droite(a->fdroite);
            return rotation_gauche(a);
        }

    } else if (a->bal == -2) {
        if (a->fgauche->bal <= 0)
            return rotation_droite(a);
        else {
            a->fgauche = rotation_gauche(a->fgauche);
            return rotation_droite(a);
        }

    } else
        return a;
}

Arbre_AVL_t ajoute_cle(int x, Arbre_AVL_t a) {
    Arbre_AVL_t n = (Arbre_AVL_t) malloc(sizeof(noeud_AVL_t));
    n->cle = x;
    n->fdroite = NULL;
    n->fgauche = NULL;
    n->bal = 0;
    a = ajouter_noeud_AVL(a, n);
    set_balance(a);
    if (a->bal == 2 || a->bal == -2) {
        a = reequilibrage(a);
    }
    return a;
}

Arbre_AVL_t ajouter_noeud_AVL(Arbre_AVL_t a, Arbre_AVL_t n) {
    if (a == NULL)
        return n;
    else if (n->cle < a->cle)
        a->fgauche = ajouter_noeud_AVL(a->fgauche, n);
    else
        a->fdroite = ajouter_noeud_AVL(a->fdroite, n);
    return a;
}

