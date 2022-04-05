#include <stdio.h>
#include <stdlib.h>

#include "abr.h"

int main(int argc, char **argv) {
//    Arbre_t a, b;
    Arbre_t a;
    if (argc < 2) {
        fprintf(stderr, "il manque le parametre nom de fichier\n");
        exit(-1);
    }

    a = lire_arbre(argv[1]);
//    b = lire_arbre(argv[2]);

   afficher_arbre(a, 0);

//    printf("%d\n",hauteur_arbre_r(a)); 

//    printf("%d\n",hauteur_arbre_nr(a)); 
//    parcourir_arbre_largeur(a); 
//    afficher_nombre_noeuds_par_niveau(a); 
//
//    printf("%d\n",nombre_cles_arbre_r(a)); 
//
//    printf("%d\n",nombre_cles_arbre_nr(a)); 
//
//    printf("%d\n",trouver_cle_min(a)); 
//
//    imprimer_liste_cle_triee_r(a); 
//
//    imprimer_liste_cle_triee_nr(a); 
//
//    printf("%d\n",arbre_plein(a)); 
//
//    printf("%d\n", arbre_parfait(a));
//
//    printf("%d\n",rechercher_cle_sup_arbre(a, 15)->cle); 
//    printf("%d\n",rechercher_cle_inf_arbre(a, 7)->cle); 
//
//    afficher_arbre(detruire_cle_arbre(a, 4), 0); 

//    afficher_arbre(intersection_deux_arbres(a, b), 0);
//
//    afficher_arbre(union_deux_arbres(a, b), 0);

}
