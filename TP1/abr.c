#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "abr.h"
#include "pile.h"
#include "file.h"


#define max(a, b) ((a)>(b)?(a):(b))


int feuille(Arbre_t a) {
    if (a == NULL)
        return 0;
    else {
        if ((a->fgauche == NULL) && (a->fdroite == NULL))
            return 1;
        else
            return 0;
    }
}

Arbre_t ajouter_noeud(Arbre_t a, Arbre_t n) {
    /* ajouter le noeud n dans l'arbre a */

    if (a == NULL)
        return n;
    else if (n->cle < a->cle)
        a->fgauche = ajouter_noeud(a->fgauche, n);
    else
        a->fdroite = ajouter_noeud(a->fdroite, n);
    return a;

}

Arbre_t rechercher_cle_arbre(Arbre_t a, int valeur) {
    if (a == NULL)
        return NULL;
    else {
        if (a->cle == valeur)
            return a;
        else {
            if (a->cle < valeur)
                return rechercher_cle_arbre(a->fdroite, valeur);
            else
                return rechercher_cle_arbre(a->fgauche, valeur);
        }
    }
}

Arbre_t ajouter_cle(Arbre_t a, int cle) {
    Arbre_t n;
    Arbre_t ptrouve;

    /*
       ajout de la clé. Creation du noeud n qu'on insere
      dans l'arbre a
    */

    ptrouve = rechercher_cle_arbre(a, cle);

    if (ptrouve == NULL) {
        n = (Arbre_t) malloc(sizeof(noeud_t));
        n->cle = cle;
        n->fgauche = NULL;
        n->fdroite = NULL;

        a = ajouter_noeud(a, n);
        return a;
    } else
        return a;
}


Arbre_t lire_arbre(char *nom_fichier) {
    FILE *f;
    int cle;
    Arbre_t a = NULL;

    f = fopen(nom_fichier, "r");

    while (fscanf(f, "%d", &cle) != EOF) {
        a = ajouter_cle(a, cle);
    }

    fclose(f);

    return a;
}

void afficher_arbre(Arbre_t a, int niveau) {
    /*
      affichage de l'arbre a
      on l'affiche en le penchant sur sa gauche
      la partie droite (haute) se retrouve en l'air
    */

    int i;

    if (a != NULL) {
        afficher_arbre(a->fdroite, niveau + 1);
        for (i = 0; i < niveau; i++)
            printf("\t");
        printf(" %d (%d)\n\n", a->cle, niveau);
        afficher_arbre(a->fgauche, niveau + 1);
    }
    return;
}


int hauteur_arbre_r(Arbre_t a) {
    if (a == NULL) {
        return -1;
    } else
        return 1 + max(hauteur_arbre_r(a->fgauche), hauteur_arbre_r(a->fdroite));
}

int hauteur_arbre_nr(Arbre_t a) {
    pfile_t file = creer_file();
    pfile_t temp = creer_file();
    enfiler(file, a);
    int niveau = -1;
    while (!file_vide(file)) {
        int count = 0;
        while (!file_vide(file)) {
            Arbre_t fd, fg;
            Arbre_t noeud = defiler(file);
            fg = noeud->fgauche;
            fd = noeud->fdroite;
            if (fg != NULL)
                enfiler(temp, fg);
            if (fd != NULL)
                enfiler(temp, fd);
            count++;
        }
        while (!file_vide(temp))
            enfiler(file, defiler(temp));
        niveau++;
    }
    return niveau;
}

void parcourir_arbre_largeur(Arbre_t a) {

    pfile_t f = creer_file();
    pnoeud_t sommet = a;
    if (a != NULL) enfiler(f, sommet);
    while (file_vide(f) != 1) {
        pnoeud_t temp = defiler(f);
        printf("%i\n", temp->cle);
        if (temp->fgauche != NULL) {
            enfiler(f, temp->fgauche);
        }
        if (temp->fdroite != NULL) {
            enfiler(f, temp->fdroite);
        }
    }
    return;
}


void afficher_nombre_noeuds_par_niveau(Arbre_t a) {
    pfile_t f = creer_file();
    pfile_t temp = creer_file();
    enfiler(f, a);
    int niveau = 0;
    while (!file_vide(f)) {
        int compteur = 0;
        while (!file_vide(f)) {
            Arbre_t fd, fg;
            Arbre_t noeud = defiler(f);
            fg = noeud->fgauche;
            fd = noeud->fdroite;
            if (fg != NULL) enfiler(temp, fg);
            if (fd != NULL) enfiler(temp, fd);
            compteur++;
        }
        while (!file_vide(temp)) enfiler(f, defiler(temp));
        printf("Niveau %i : %i noeuds\n", niveau, compteur);
        niveau++;
    }
    return;
}


int nombre_cles_arbre_r(Arbre_t a) {
    if (a == NULL) {
        return 0;
    } else
        return 1 + nombre_cles_arbre_r(a->fgauche) + nombre_cles_arbre_r(a->fdroite);
}

int nombre_cles_arbre_nr(Arbre_t a) {
    int nb_cle = 0;
    if (a != NULL) {
        pnoeud_t noeud;
        pfile_t file = creer_file();
        enfiler(file, a);
        while (!file_vide(file)) {
            noeud = defiler(file);
            nb_cle++;
            if (noeud->fgauche) {
                enfiler(file, noeud->fgauche);
            }
            if (noeud->fdroite)
                enfiler(file, noeud->fdroite);
        }
    }
    return nb_cle;
}

Arbre_t trouver_cle_min(Arbre_t a) {
    if (a == NULL) {
        return NULL;
    } else if (a->fgauche == NULL) {
        return a;
    } else
        return trouver_cle_min(a->fgauche);
}


void imprimer_liste_cle_triee_r(Arbre_t a) {
    if (a != NULL) {
        imprimer_liste_cle_triee_r(a->fgauche);
        printf("%d\n", a->cle);
        imprimer_liste_cle_triee_r(a->fdroite);
    }
}

void get_liste_cle_triee(Arbre_t a, int *tab, int *index) {
    if (a != NULL) {
        get_liste_cle_triee(a->fgauche, tab, index);
        tab[*index] = a->cle;
        (*index)++;
        get_liste_cle_triee(a->fdroite, tab, index);
    }
}

void imprimer_liste_cle_triee_nr(Arbre_t a) {
    ppile_t pile = creer_pile();
    Arbre_t curr = a;
    while (curr != NULL || !pile_vide(pile)) {
        while (curr != NULL) {
            empiler(pile, curr);
            curr = curr->fgauche;
        }
        curr = depiler(pile);
        printf("%d\n", curr->cle);
        curr = curr->fdroite;
    }
}


int arbre_plein(Arbre_t a) {
    int hauteur = hauteur_arbre_r(a);
    int noeuds = nombre_cles_arbre_r(a);
    if (noeuds == pow(2, hauteur - 1) - 1)
        return 1;
    return 0;
}

int arbre_parfait(Arbre_t a) {
    int hauteur = hauteur_arbre_r(a);
    int noeuds = nombre_cles_arbre_r(a);
    if (hauteur == floor(log2(noeuds)))
        return 1;
    return 0;
}


Arbre_t rechercher_cle_sup_arbre(Arbre_t a, int valeur) {
    if (a->cle < valeur) {
        if (a->fdroite == NULL)
            return a;
        return rechercher_cle_sup_arbre(a->fdroite, valeur);
    } else {
        if (a->fgauche == NULL)
            return a;
        Arbre_t sup = rechercher_cle_sup_arbre(a->fgauche, valeur);
        if (sup->cle == valeur)
            return a;
        if ((sup->cle - valeur) < (a->cle - valeur))
            return sup;
        return a;
    }
}

Arbre_t rechercher_cle_inf_arbre(Arbre_t a, int valeur) {
    if (a->cle < valeur) {
        if (a->fdroite == NULL)
            return a;
        Arbre_t inf = rechercher_cle_inf_arbre(a->fdroite, valeur);
        if (inf->cle == valeur)
            return a;
        if (inf->cle - valeur < 0)
            return inf;
        if (a->cle - valeur < 0)
            return a;
        if ((inf->cle - valeur) > (a->cle - valeur)) {
            return inf;
        }
        return a;

    } else {
        if (a->fgauche == NULL)
            return a;
        return rechercher_cle_inf_arbre(a->fgauche, valeur);
    }
}


Arbre_t detruire_cle_arbre(Arbre_t a, int cle) {
    if (a == NULL)
        return a;

    if (cle < a->cle)
        a->fgauche = detruire_cle_arbre(a->fgauche, cle);
    else if (cle > a->cle)
        a->fdroite = detruire_cle_arbre(a->fdroite, cle);
    else {
        if (a->fgauche == NULL) {
            Arbre_t temp = a->fdroite;
            free(a);
            return temp;
        } else if (a->fdroite == NULL) {
            Arbre_t temp = a->fgauche;
            free(a);
            return temp;
        }

        Arbre_t temp = trouver_cle_min(a->fdroite);

        a->cle = temp->cle;

        a->fdroite = detruire_cle_arbre(a->fdroite, temp->cle);

    }
    return a;

}


Arbre_t intersection_deux_arbres(Arbre_t a1, Arbre_t a2) {
    Arbre_t res = NULL;
    int nbCle1 = nombre_cles_arbre_r(a1);
    int nbCle2 = nombre_cles_arbre_r(a2);

    int tab1[nbCle1];
    int tab2[nbCle2];

    int *index = malloc(sizeof(int));
    *index = 0;
    get_liste_cle_triee(a1, tab1, index);
    *index = 0;
    get_liste_cle_triee(a2, tab2, index);

    for (int i = 0; i < nbCle1; ++i) {
        for (int j = 0; j < nbCle2; ++j) {
            if (tab1[i] == tab2[j])
                res = ajouter_cle(res, tab1[i]);

        }
    }
    return res;

}

Arbre_t union_deux_arbres(Arbre_t a1, Arbre_t a2) {
    Arbre_t res = NULL;
    int nbCle1 = nombre_cles_arbre_r(a1);
    int nbCle2 = nombre_cles_arbre_r(a2);

    int tab1[nbCle1];
    int tab2[nbCle2];

    int *index = malloc(sizeof(int));
    *index = 0;
    get_liste_cle_triee(a1, tab1, index);
    *index = 0;
    get_liste_cle_triee(a2, tab2, index);

    for (int i = 0; i < nbCle1; ++i)
        res = ajouter_cle(res, tab1[i]);
    for (int i = 0; i < nbCle2; ++i)
        res = ajouter_cle(res, tab2[i]);
    return res;
}