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

void test_eulerien()
{
  printf("\n=================TEST EULERIEN==================\n\n");
  pgraphe_t g;
  chemin_t c;

  lire_graphe("data/gr_eulerien", &g);
  printf("\n");
  ecrire_graphe(g);
  printf("\n");

  psommet_t s1 = chercher_sommet(g, 1);
  psommet_t s2 = chercher_sommet(g, 3);
  psommet_t s3 = chercher_sommet(g, 2);

  c.depart = s1;
  c.listArcs = malloc(sizeof(struct list));
  plistArc_t list_arc1 = c.listArcs;

  list_arc1->arcDepart = s1->liste_arcs;
  list_arc1->nextArc = malloc(sizeof(struct list));
  plistArc_t list_arc2 = list_arc1->nextArc;

  list_arc2->arcDepart = s2->liste_arcs;
  list_arc2->nextArc = malloc(sizeof(struct list));
  plistArc_t list_arc3 = list_arc2->nextArc;

  list_arc3->arcDepart = s3->liste_arcs;
  list_arc3->nextArc = NULL;

  printf("Le chemin 1->3->2->1 est-il eulerien ? %s \n", trad(eulerien(g, c)));
  printf("Le graphe est Eulérien ? %s \n", trad(graphe_eulerien(g)));
}

void test_hamiltonien()
{
  printf("\n=================TEST HAMILTONIEN==================\n\n");

  pgraphe_t g;
  chemin_t c;

  lire_graphe("data/gr_hamiltonien", &g);
  printf("\n");
  ecrire_graphe(g);

  psommet_t s1 = chercher_sommet(g, 1);
  psommet_t s2 = chercher_sommet(g, 2);
  psommet_t s3 = chercher_sommet(g, 3);
  psommet_t s4 = chercher_sommet(g, 4);

  c.depart = s1;
  c.listArcs = malloc(sizeof(struct list));
  plistArc_t list_arc1 = c.listArcs;

  list_arc1->arcDepart = s1->liste_arcs;
  list_arc1->nextArc = malloc(sizeof(struct list));
  plistArc_t list_arc2 = list_arc1->nextArc;

  list_arc2->arcDepart = s2->liste_arcs;
  list_arc2->nextArc = malloc(sizeof(struct list));
  plistArc_t list_arc3 = list_arc2->nextArc;

  list_arc3->arcDepart = s3->liste_arcs;
  list_arc3->nextArc = malloc(sizeof(struct list));
  plistArc_t list_arc4 = list_arc3->nextArc;

  list_arc4->arcDepart = s4->liste_arcs;
  list_arc4->nextArc = NULL;

  printf("Le chemin 1->2->3->4 est-il Hamiltonien ? %s \n", trad(hamiltonien(g, c)));
  printf("Le graphe est Hamiltonien ? %s \n", trad(graphe_hamiltonien(g)));
}

void test_principal(pgraphe_t g)
{
  int nc;
  printf("\n");
  ecrire_graphe(g);
  printf("\n");

  nc = colorier_graphe(g);

  printf("Nombre chromatique graphe = %d\n", nc);

  ecrire_graphe_colorie(g);
  printf("\n");

  afficher_graphe_profondeur(g, g->label);
  printf("\n");

  afficher_graphe_largeur(g, g->label);
  printf("\n");

  // afficherDijkstra(g, 1); PROBLEME DIJKSTRA
  printf("Degre maximal du graphe: %d\n", degre_maximal_graphe(g));
  printf("Degre minimal du graphe: %d\n", degre_minimal_graphe(g));
  printf("\n");

  printf("Le graphe est Connexe ? %s\n", trad(graphe_connexe(g)));
  printf("Le graphe est Eulérien ? %s \n", trad(graphe_eulerien(g)));
  printf("Le graphe est Hamiltonien ? %s \n", trad(graphe_hamiltonien(g)));

  printf("\n");
}

int main(int argc, char **argv)
{
  pgraphe_t g;

  if (argc != 2)
  {
    fprintf(stderr, "erreur parametre \n");
    exit(-1);
  }

  /*
    la fonction lire_graphe alloue le graphe (matrice,...)
    et lit les donnees du fichier passe en parametre
  */
  printf("\n");
  lire_graphe(argv[1], &g);
  printf("\n");

  /*
    la fonction ecrire_graphe affiche le graphe a l'ecran
  */

  printf("nombre de sommets du graphe %d nombre arcs %d \n", nombre_sommets(g), nombre_arcs(g));
  fflush(stdout);

  test_principal(g);
  test_eulerien();
  test_hamiltonien();
}
