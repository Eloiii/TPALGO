/*
  Structures de type graphe
  Structures de donnees de type liste
  (Pas de contrainte sur le nombre de noeuds des  graphes)
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "file.h"
#include "graphe.h"

psommet_t chercher_sommet(pgraphe_t g, int label)
{
  psommet_t s;

  s = g;

  while ((s != NULL) && (s->label != label))
  {
    s = s->sommet_suivant;
  }
  return s;
}

parc_t existence_arc(parc_t l, psommet_t s)
{
  parc_t p = l;

  while (p != NULL)
  {
    if (p->dest == s)
      return p;
    p = p->arc_suivant;
  }
  return p;
}

void ajouter_arc(psommet_t o, psommet_t d, int distance)
{
  parc_t parc;

  parc = (parc_t)malloc(sizeof(arc_t));

  if (existence_arc(o->liste_arcs, d) != NULL)
  {
    fprintf(stderr, "ajout d'un arc deja existant\n");
    exit(-1);
  }

  parc->poids = distance;
  parc->dest = d;
  parc->arc_suivant = o->liste_arcs;
  o->liste_arcs = parc;
  return;
}

// ===================================================================

int nombre_sommets(pgraphe_t g)
{
  psommet_t p = g;
  int nb = 0;

  while (p != NULL)
  {
    nb = nb + 1;
    p = p->sommet_suivant;
  }

  return nb;
}

int nombre_arcs(pgraphe_t g)
{

  psommet_t p = g;
  int nb_arcs = 0;

  while (p != NULL)
  {
    parc_t l = p->liste_arcs;

    while (l != NULL)
    {
      nb_arcs = nb_arcs + 1;
      l = l->arc_suivant;
    }

    p = p->sommet_suivant;
  }
  return nb_arcs;
}

void init_couleur_sommet(pgraphe_t g)
{
  psommet_t p = g;

  while (p != NULL)
  {
    p->couleur = 0;        // couleur indefinie
    p = p->sommet_suivant; // passer au sommet suivant dans le graphe
  }

  return;
}

int colorier_graphe(pgraphe_t g)
{
  /*
    coloriage du graphe g

    datasets
    graphe data/gr_planning
    graphe data/gr_sched1
    graphe data/gr_sched2
  */

  psommet_t p = g;
  parc_t a;
  int couleur;
  int max_couleur = INT_MIN; // -INFINI

  int change;

  init_couleur_sommet(g);

  while (p != NULL)
  {
    couleur = 1; // 1 est la premiere couleur

    // Pour chaque sommet, on essaie de lui affecter la plus petite couleur

    // Choix de la couleur pour le sommet p

    do
    {
      a = p->liste_arcs;
      change = 0;

      while (a != NULL)
      {
        if (a->dest->couleur == couleur)
        {
          couleur = couleur + 1;
          change = 1;
        }
        a = a->arc_suivant;
      }

    } while (change == 1);

    // couleur du sommet est differente des couleurs de tous les voisins

    p->couleur = couleur;
    if (couleur > max_couleur)
      max_couleur = couleur;

    p = p->sommet_suivant;
  }

  return max_couleur;
}

void afficher_graphe_largeur(pgraphe_t g, int r)
{
  psommet_t debut = chercher_sommet(g, r);
  debut->explore = 1;

  pfile_t f_sommets = creer_file();
  enfiler(f_sommets, debut);
  while (!file_vide(f_sommets))
  {
    psommet_t current = defiler(f_sommets);
    printf("%d | ", current->label);

    parc_t current_arc = current->liste_arcs;
    while (current_arc != NULL)
    {
      if (!current_arc->dest->explore)
      {
        enfiler(f_sommets, current_arc->dest);
        current_arc->dest->explore = 1;
      }
      current_arc = current_arc->arc_suivant;
    }
  }
  printf("\n");
  return;
}

void parcours_profondeur_rec(pgraphe_t g, int r)
{
  psommet_t s = chercher_sommet(g, r);
  if (s != NULL && s->couleur != 1)
  {
    printf("%d | ", r);
    s->couleur = 1;
    parc_t arcs = s->liste_arcs;
    while (arcs != NULL && arcs->dest != NULL)
    {
      parcours_profondeur_rec(g, arcs->dest->label);
      arcs = arcs->arc_suivant;
    }
  }
}

void afficher_graphe_profondeur(pgraphe_t g, int r)
{
  init_couleur_sommet(g);
  printf("Voici le parcours en profondeur du graphe: ");
  parcours_profondeur_rec(g, r);
  printf("\n");
}

/**
 * Algorithme de Dijkstra : trouve les plus courts chemins
 * Pour cela, il faut d'abord initialiser le graphe
 */

void enfileSommet(pgraphe_t g, pfile_t fap)
{
  psommet_t sommet = g;
  if (sommet != NULL && sommet->couleur != 1)
  {
    sommet->couleur = 1;
    enfiler(fap, g);
    g->longueur = INT_MAX;
    g->parent = NULL;
    parc_t arcs = sommet->liste_arcs;
    while (arcs != NULL && arcs->dest != NULL)
    {
      enfileSommet(arcs->dest, fap);
      arcs = arcs->arc_suivant;
    }
  }
}

void initialisation(pgraphe_t g, pfile_t fap)
{
  init_couleur_sommet(g);
  enfileSommet(g, fap);

  g->longueur = 0;
  g->parent = NULL;
  g = g->sommet_suivant;

  while (g != NULL)
  {
    g->longueur = INT_MAX;
    g->parent = NULL;
    g = g->sommet_suivant;
  }
}

/*
 Permet de relacher un arc si un parcours plus court est trouvé
 */
void relachement(psommet_t sommet, parc_t arc)
{
  psommet_t dest = arc->dest;
  if (dest->longueur > sommet->longueur + arc->poids)
  {
    dest->longueur = sommet->longueur + arc->poids;
    dest->parent = sommet;
  }
}

void algo_dijkstra(pgraphe_t g, int sommet_depart)
{
  pfile_t fap = creer_file();
  psommet_t sommetPlusPetit;
  initialisation(g, fap);
  while (!file_vide(fap))
  {
    sommetPlusPetit = extraire(fap);
    parc_t arcsSortants = sommetPlusPetit->liste_arcs;
    while (arcsSortants != NULL)
    {
      relachement(sommetPlusPetit, arcsSortants);
      arcsSortants = arcsSortants->arc_suivant;
    }
  }
}

/**
 Affiche les plus courts chemin de l'algo de Dijkstra
 */
void afficherDijkstra(pgraphe_t g, int sommet_depart)
{
	printf("BONJOUR");
  printf("Voici Diskstra ");
  init_couleur_sommet(g);
  algo_dijkstra(g, sommet_depart);
  psommet_t sommet = g;
  psommet_t parent = g;
  while (sommet != NULL)
  {
    parent = sommet;

    while (parent != NULL)
    {
      if (parent != g)
      {
        printf("%i <- ", parent->label);
        if (sommet->longueur == INT_MAX) 
        {
          printf("inaccessible");
        }
      }
      else
      {
        printf("%i ", parent->label);
      }
      parent = parent->parent;
    }

    printf("\n");
    sommet = sommet->sommet_suivant;
  }
}

// ======================================================================
/*
    Cette fonction retourne le nombre d'arcs sortants
    du sommet n dans le graphe g
  */
int degre_sortant_sommet(pgraphe_t g, psommet_t s)
{
  int cmpt = 0;
  if (s == NULL)
  {
    return 0;
  }
  else
  {
    parc_t arc = s->liste_arcs;
    while (arc)
    {
      arc = arc->arc_suivant;
      cmpt++;
    }
  }
  return cmpt;
}
/*
  Cette fonction retourne le nombre d'arcs entrants
  dans le noeud n dans le graphe g
*/
int degre_entrant_sommet(pgraphe_t g, psommet_t s)
{
  int cmpt = 0;
  if (s == NULL)
  {
    return cmpt;
  }
  else
  {
    pgraphe_t noeudCourant = g;
    while (noeudCourant)
    {
      parc_t listArcs = noeudCourant->liste_arcs;
      while (listArcs) // on parcourt les noeuds
      {
        if (listArcs->dest == s)
        {
          cmpt++;
        }
        listArcs = listArcs->arc_suivant;
      }
      noeudCourant = noeudCourant->sommet_suivant;
    }
  }
  return cmpt;
}

/*
   Max des degres des sommets du graphe g
 */
int degre_maximal_graphe(pgraphe_t g)
{
  if (g == NULL)
  {
    return 0;
  }
  else
  {
    pgraphe_t noeudCourant = g;
    int degresMax = degre_entrant_sommet(g, g) + degre_sortant_sommet(g, g);

    while (noeudCourant)
    {
      int deg = degre_entrant_sommet(g, noeudCourant) + degre_sortant_sommet(g, noeudCourant);
      if (deg > degresMax)
      {
        degresMax = deg;
      }
      noeudCourant = noeudCourant->sommet_suivant;
    }
    return degresMax;
  }
}

/*
   Min des degres des sommets du graphe g
 */
int degre_minimal_graphe(pgraphe_t g)
{
  if (g == NULL)
  {
    return 0;
  }
  else
  {
    pgraphe_t noeudCourant = g;
    int degresMin = degre_entrant_sommet(g, g) + degre_sortant_sommet(g, g);

    while (noeudCourant)
    {
      int deg = degre_entrant_sommet(g, noeudCourant) + degre_sortant_sommet(g, noeudCourant);
      if (deg < degresMin)
      {
        degresMin = deg;
      }
      noeudCourant = noeudCourant->sommet_suivant;
    }
    return degresMin;
  }
}

/* Les aretes du graphe n'ont pas de sommet en commun */

int independant(pgraphe_t g)
{
  psommet_t sommetCourant;
  sommetCourant = g;
  while (sommetCourant && (degre_entrant_sommet(g, sommetCourant) + degre_sortant_sommet(g, sommetCourant) < 2))
  {
    // on a un sommet en commun si il y a plus que 2 arcs
    sommetCourant = sommetCourant->sommet_suivant;
  }
  if (sommetCourant == NULL)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

/*
 Fonction qui indique si les deux sommets passés en paramètre sont connectés dans les deux sens
*/

int connecter(psommet_t s1, psommet_t s2)
{
  parc_t listArc = s1->liste_arcs;
  while (listArc != NULL && listArc->dest != s2)
  {
    listArc = listArc->arc_suivant;
  }
  if (listArc != NULL && listArc->dest == s2)
  {
    listArc = s2->liste_arcs;
    while (listArc != NULL && listArc->dest != s1)
    {
      listArc = listArc->arc_suivant;
    }
    if (listArc == NULL || listArc->dest != s1)
    {
      return 0;
    }
  }
  else
  {
    return 0;
  }
  return 1;
}

/* Toutes les paires de sommet du graphe sont jointes par un arc */

int complet(pgraphe_t g)
{
  int complet = 1;
  psommet_t sommetCourant = g;
  while (sommetCourant && complet)
  {
    complet = connecter(sommetCourant, sommetCourant->sommet_suivant);
    sommetCourant = sommetCourant->sommet_suivant;
  }
  return complet;
}

/*
     graphe regulier: tous les sommets ont le meme degre
     g est le ponteur vers le premier sommet du graphe
     renvoie 1 si le graphe est régulier, 0 sinon
*/

int regulier(pgraphe_t g)
{
  psommet_t base = g;
  int degresBase = degre_sortant_sommet(g, base) + degre_entrant_sommet(g, base);
  while (base)
  {
    if (degre_sortant_sommet(g, base) + degre_entrant_sommet(g, base) != degresBase)
    {
      return 0;
    }
    base = base->sommet_suivant;
  }
  return 1;
}

/*
====================================================================================================================
=============================================FONCTIONS EXAM 2017====================================================
====================================================================================================================


  Fonction qui vérifie que le chemin est élémentaire cad verifie que le chemin ne passe pas deux fois par le même sommet
*/

int elementaire(pgraphe_t g, chemin_t c)
{
  int nbSommet = nombre_sommets(g);
  int visite[nbSommet];            // liste qui contiendra les sommets visités
  plistArc_t courant = c.listArcs; // on récupère le premier element de la liste d'arc representant le chemin
  int cmpt = 0;                    // pour se déplacer dans le tableau d'arcs déjà vus
  while (courant != NULL)          // tant qu'on a un arc dans le chemin
  {
    for (int i = 0; i < cmpt; i++)
    {
      if (visite[i] == courant->arcDepart->dest->label)
      {
        // Le chemin n'est pas élémentaire
        return 0;
      }
    }
    visite[cmpt] = courant->arcDepart->dest->label;
    courant = courant->nextArc; // on passe à l'arc suivant
    cmpt++;
  }
  return 1; // Le chemin est élémentaire
}
/*
====================================================================================================================
=============================================FONCTION SIMPLE========================================================
====================================================================================================================


  Fonction qui vérifie que le chemin est simple cad vérifie que le chemin ne passe pas deux fois par le même arc
*/
int simple(pgraphe_t g, chemin_t c)
{
  int nbArc = nombre_arcs(g);
  parc_t visite[nbArc];            // liste qui contiendra les arcs déjà visités
  plistArc_t courant = c.listArcs; // on récupère le premier element de la liste d'arc representant le chemin
  int cmpt = 0;
  while (courant != NULL)
  {
    for (int i = 0; i < cmpt; i++)
    {
      if (visite[i] == courant->arcDepart)
      {
        return 0; // Le chemin n'est pas simple
      }
    }
    visite[cmpt] = courant->arcDepart;
    courant = courant->nextArc;
    cmpt++;
  }
  return 1; // Le chemin est simple
}
/*
====================================================================================================================
=============================================FONCTION CHEMIN EULERIEN===============================================
====================================================================================================================

  Fonction eulérien qui vérifie qu'un chemin possède tous les arcs du graphe.
  Pour cette fonction, on a besoin de vérifier que le chemin est simple mais aussi correct
  Il faut aussi que le nombre d'arcs du chemin = nombre d'arcs du graphe
  On va alors implementer 2 fonctions auxiliaires:
    correct() qui vérifie que le chemin est correct
    nbr_arc_chemin() qui calcule le nombre d'arc dans le chemin
*/

int correct(chemin_t c)
{
  plistArc_t courantArc = c.listArcs;
  parc_t courant = NULL;
  int nbr = 0;
  while (courantArc)
  {
    courant = courantArc->arcDepart->dest->liste_arcs;
    if (courantArc->nextArc != NULL)
    {
      while (courant != NULL && courant != courantArc->nextArc->arcDepart)
      {
        courant = courant->arc_suivant;
      }
      if (courant == NULL)
      {
        return 0;
      }
    }
    courantArc = courantArc->nextArc;
    nbr++;
  }
  return 1;
}

int nbr_arc_chemin(chemin_t c)
{
  plistArc_t courant = c.listArcs;
  int nbr = 0;
  if (courant == NULL)
  {
    return nbr;
  }
  nbr++;
  while (courant->nextArc)
  {
    courant = courant->nextArc;
    nbr++;
  }
  return nbr;
}

int eulerien(pgraphe_t g, chemin_t c)
{
  int nb = nbr_arc_chemin(c);
  if ((nb != nombre_arcs(g)) || !correct(c) || !simple(g, c))
  {
    return 0;
  }
  return 1;
}
/*
====================================================================================================================
=========================================FONCTION CHEMIN HAMILTONIEN================================================
====================================================================================================================

Fonction Hamiltonien qui vérifie qu'un chemin possède tous les sommets du graphe.
Pour cette fonction, on a besoin de vérifier que le chemin est non simple et élémentaire
Il faut aussi que le nombre de sommets du chemin = nombre de sommets du graphe
On va implementer une fonction auxiliaire qui va vérifier que le sommet sur lequel on passe ne fait pas déjà
parti des sommets visités.
*/

int pas_visiter(psommet_t *sommet_visiter, psommet_t sommetCourant, int nbSommet)
{
  for (int i = 0; i < nbSommet; i++)
  {
    if (sommetCourant == sommet_visiter[i])
    {
      return 0;
    }
  }
  return 1;
}

int hamiltonien(pgraphe_t g, chemin_t c)
{
  psommet_t Courant = g;
  int nbr_sommet = nombre_sommets(g);
  psommet_t sommet_visiter[nbr_sommet]; // tableau qui contiendra les sommets visités
  int index = 0;
  Courant = c.depart;
  sommet_visiter[index] = Courant;
  index++;
  plistArc_t arcCourant = c.listArcs;
  while (arcCourant != NULL)
  {
    sommet_visiter[index] = arcCourant->arcDepart->dest;
    index++;
    arcCourant = arcCourant->nextArc;
  }
  Courant = g;
  while (Courant != NULL)
  {
    if (pas_visiter(sommet_visiter, Courant, nbr_sommet))
    {
      return 0;
    }
    Courant = Courant->sommet_suivant;
  }
  return 1;
}
/*
====================================================================================================================
=============================================FONCTIONS GRAPHE EULERIEN==============================================
====================================================================================================================

  Fonction graphe_eulerien qui vériein qu'il existe au moins un chemin qui soit Eulérien
  Cette fonction implique de savoir si le graphe est connexe ou non
  Un graphe orienté connexe est une graphe dans le lequel tout les sommets
  sont accessible depuis tout les autres sommets.
  Il suffira alors de vérifier que le graphe connexe possède uniquement des sommets pairs
  (propriété des graphes connexes)
 */
int graphe_connexe(pgraphe_t g)
{
  int nbSommet = 0;
  psommet_t sommetCourant = g;
  while (sommetCourant != NULL)
  {
    nbSommet++;
    sommetCourant = sommetCourant->sommet_suivant;
  }

  pfile_t fap = creer_file();
  int nbr_elem_file = 0;
  sommetCourant = g;
  while (sommetCourant != NULL)
  {
    init_couleur_sommet(g);
    enfileSommet(g, fap);
    nbr_elem_file++;
    if (nbr_elem_file != nbSommet)
    {
      return 0;
    }
    sommetCourant = sommetCourant->sommet_suivant;
    detruire_file(fap);
    fap = creer_file();
  }
  return 1;
}

int graphe_eulerien(pgraphe_t g)
{
  psommet_t sommetCourant = g;
  if (!graphe_connexe(g))
  {
    return 0;
  }
  int estEulerien = 1;
  sommetCourant = g;
  while (sommetCourant != NULL && estEulerien)
  {
    int degree = degre_entrant_sommet(g, sommetCourant) + degre_sortant_sommet(g, sommetCourant);
    if (degree % 2 != 0)
    {
      estEulerien = 0;
    }
    sommetCourant = sommetCourant->sommet_suivant;
  }
  return estEulerien;
}

int dejaVisite(psommet_t s, int sommetsVisites[], int nbVisites) {
	for(int i = 0; i < nbVisites; i++) {
		if(s->label == sommetsVisites[i])
			return 1;
	}
	return 0;
}

int cheminPlusLong(psommet_t s, int nbVisites, int sommetsVisites[]) {
	if(dejaVisite(s, sommetsVisites, nbVisites) || !s)
		return nbVisites;
	sommetsVisites[nbVisites++] = s->label;
	int visitesCurr = 0;
	parc_t curr = s->liste_arcs;
	while(curr) {
		visitesCurr = cheminPlusLong(curr->dest, nbVisites, sommetsVisites);
		if(visitesCurr > nbVisites)
			nbVisites = visitesCurr;
		curr = curr->arc_suivant;
	}
	return nbVisites;
}

int graphe_hamiltonien(pgraphe_t g) {
	init_couleur_sommet(g);
	psommet_t curr = g;
	int nbSommet = nombre_sommets(g);
	int sommetsVisites[nbSommet];
	while(curr){
		if(nbSommet == cheminPlusLong(curr, 0, sommetsVisites))
			return 1;
		curr = curr->sommet_suivant;
	}
	return 0;
}

int distance(pgraphe_t g, int x, int y) {
	algo_dijkstra(g, x);
	psommet_t Y = chercher_sommet(g, y);
	return Y->longueur != INT_MAX ? Y->longueur : -1;
}

int excentricite(pgraphe_t g, int n) {
	psommet_t N = chercher_sommet(g, n);
	int excentricite = 0;
	algo_dijkstra(g, n);
	while(N) {
		if(N->longueur > excentricite)
			excentricite = N->longueur;
		N = N->sommet_suivant;
	}
	return excentricite != INT_MAX ? excentricite : -1;
}

int diametre(pgraphe_t g) {
	psommet_t sommet = g;
	int excMax = 0;
	int excentriciteCurr = 0;
	while(sommet) {
		excentriciteCurr = excentricite(g, sommet->label);
		if(excentriciteCurr > excMax || excentriciteCurr == -1)
			excMax = excentriciteCurr;
		sommet = sommet->sommet_suivant;
	}
	return excMax;
}
