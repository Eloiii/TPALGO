#include <stdio.h>
#include <stdlib.h>

#include "avl.h"

int main(int argc, char **argv) {
    Arbre_AVL_t a;

    if (argc < 2) {
        fprintf(stderr, "il manque le parametre nom de fichier\n");
        exit(-1);
    }

    a = convertToAVL(lire_arbre(argv[1]));

    afficher_arbre_avl(a, 0);
//    afficher_arbre_avl(rotation_gauche(a), 0);
//    afficher_arbre_avl(rotation_droite(a), 0);
//    afficher_arbre_avl(double_rotation_gauche(a), 0);
//    afficher_arbre_avl(double_rotation_droite(a), 0);
//    afficher_arbre_avl(reequilibrage(a), 0);
//    afficher_arbre_avl(ajoute_cle(14, a), 0);
}
