
#ifndef GRAPH
#define GRAPH

typedef struct a *parc_t;

/*
  definition des types sommet et pointeur de sommet
  un graphe est constitué d'une liste de sommets
*/

typedef struct s
{
  int label;                // label du sommet
  parc_t liste_arcs;        // arcs sortants du sommet
  struct s *sommet_suivant; // sommet suivant dans le graphe
  int couleur;              // couleur du sommet
  int explore;              // s'il a déjà été exploré auparavant
  int longueur;
  struct s *parent;
} sommet_t, *psommet_t;

/*
  definition des types arc et pointeur d'arc
  Les arcs sortants d'un sommet sont chainés
  Pour chaque arc, il y a un poids qui peut par exemple correspondre a une distance
*/

typedef struct a
{
  int poids;             // poids de l arc
  psommet_t dest;        // pointeur sommet destinataire
  struct a *arc_suivant; // arc suivant
} arc_t, *parc_t;

/*
  pgraphe_t: pointeur vers le premier sommet d'un graphe
*/

typedef psommet_t pgraphe_t;

typedef struct list *plistArc_t;

typedef struct list
{
  parc_t arcDepart;   // arc de départ
  plistArc_t nextArc; // liste d'arcs
} * plistArc_t;

typedef struct chemin
{
  psommet_t depart;
  plistArc_t listArcs;
} chemin_t, *pchemin_t;

psommet_t chercher_sommet(pgraphe_t g, int label);

void ajouter_arc(psommet_t o, psommet_t d, int distance);

int nombre_arcs(pgraphe_t g);

int nombre_sommets(pgraphe_t g);

void lire_graphe(char *file_name, pgraphe_t *g);

void ecrire_graphe(psommet_t p);

void ecrire_graphe_colorie(psommet_t p);

int colorier_graphe(pgraphe_t g);

void afficher_graphe_profondeur(pgraphe_t g, int r);

void afficher_graphe_largeur(pgraphe_t g, int r);

void relachement(psommet_t sommet, parc_t arc);

void algo_dijkstra(pgraphe_t g, int sommet_depart);

void afficherDijkstra(pgraphe_t g, int sommet_depart);

int degre_sortant_sommet(pgraphe_t g, psommet_t s);

int degre_entrant_sommet(pgraphe_t g, psommet_t s);

void ecrire_deg_sortant(psommet_t g);

void ecrire_deg_entrant(psommet_t g);

int degre_maximal_graphe(pgraphe_t g);

int degre_minimal_graphe(pgraphe_t g);

int independant(pgraphe_t g);

int connecter(psommet_t s1, psommet_t s2);

int complet(pgraphe_t g);

int regulier(pgraphe_t g);

int elementaire(pgraphe_t g, chemin_t c);

int simple(pgraphe_t g, chemin_t c);

int correct(chemin_t c);

int nbr_arc_chemin(chemin_t c);

int eulerien(pgraphe_t g, chemin_t c);

int pas_visiter(psommet_t *sommet_visiter, psommet_t sommetCourant, int nbSommet);

int hamiltonien(pgraphe_t g, chemin_t c);

int graphe_connexe(pgraphe_t g);

int graphe_eulerien(pgraphe_t g);

int graphe_hamiltonien(pgraphe_t g);

int distance(pgraphe_t, int x, int y);

int excentricite(pgraphe_t g, int n);

int diametre(pgraphe_t g);
#endif
