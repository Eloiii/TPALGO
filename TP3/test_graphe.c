#include <stdio.h>
#include <stdlib.h>

#include "graphe.h"

char *trad(int bool)
{
  char *rep;
  if (bool == 1)
  {
    rep = "oui";
  }
  else
  {
    rep = "non";
  }
  return rep;
}

int main(int argc, char **argv)
{
  pgraphe_t g;
  int nc;

  if (argc != 2)
  {
    fprintf(stderr, "erreur parametre \n");
    exit(-1);
  }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...)
    et lit les donnees du fichier passe en parametre
  */

  lire_graphe(argv[1], &g);

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */

  printf("nombre de sommets du graphe %d nombre arcs %d \n", nombre_sommets(g), nombre_arcs(g));
  fflush(stdout);

  ecrire_graphe(g);

  nc = colorier_graphe(g);

  printf("nombre chromatique graphe = %d\n", nc);

  ecrire_graphe_colorie(g);
  afficher_graphe_profondeur(g, 1);
  printf("Parcours en largeur :\n");
  afficher_graphe_largeur(g, 1);
  printf("bonjout");
  afficherDijkstra(g, 1); //PROBLEME DIJKSTRA
  printf("fini");
  printf("Degre maximal du graphe: %d\n", degre_maximal_graphe(g));
  printf("Degre minimal du graphe: %d\n", degre_minimal_graphe(g));

  printf("Le graphe est Connexe ? %s\n", trad(graphe_connexe(g)));

  printf("Le graphe est Eulérien ? %s\n", trad(graphe_eulerien(g)));

  printf("Le graphe est Hamiltonien ? %s\n", trad(graphe_hamiltonien(g)));
 
  printf("Distance entre label 1 et 2 ? %d\n", distance(g, 1, 2));

  printf("Excentricité du label 1 ? %d\n", excentricite(g, 1));
}
