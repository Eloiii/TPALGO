#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"

#define max(a,b) ((a)>(b)?(a):(b))


Arbre234 get_fils(Arbre234 a, int fils) {
    switch (a->t) {
        case 4:
            return a->fils[fils];
        case 3:
            return fils >= 3 ? NULL : a->fils[fils];
        case 2:
            return fils >= 2 ? NULL : a->fils[fils + 1];
        default:
            return NULL;
    }
}


int get_cle(Arbre234 a, int cle) {
    //pas besoin de break car on a les returns.
    switch (a->t) {
        case 4:
            return a->cles[cle];
        case 3:
            return cle >= 2 ? -1 : a->cles[cle];
        case 2:
            return a->cles[1];
        default:
            return -1;
    }
}


int hauteur (Arbre234 a)
{
  int h0, h1, h2, h3 ;
  
  if (a == NULL)
    return 0 ;

  if (a->t == 0)
    return 0 ;

  h0 = hauteur (a->fils [0]) ;
  h1 = hauteur (a->fils [1]) ;
  h2 = hauteur (a->fils [2]) ;
  h3 = hauteur (a->fils [3]) ;

  return 1 + max (max (h0,h1),max (h2,h3)) ;
} 

int NombreCles (Arbre234 a)
{
  if (a!= NULL && a->t !=0){
    int res=a->t - 1;
    if (a->t==2){
      return NombreCles(a->fils[1])+NombreCles(a->fils[2])+res;
    }
    else if (a->t==3){
      return NombreCles(a->fils[1])+NombreCles(a->fils[2])+NombreCles(a->fils[3])+res;
    }
    else if (a->t==4){
      return NombreCles(a->fils[1])+NombreCles(a->fils[2])+NombreCles(a->fils[3])+NombreCles(a->fils[4])+res;
    }
  }
  return 0 ;
}

int CleMax(Arbre234 a) {
    Arbre234 temp = a;
    int cleMax;

    while (temp->fils[1]->t != 0) {
        temp = get_fils(temp, temp->t - 1);
    }

    return get_cle(temp, temp->t - 2);
}

int CleMin(Arbre234 a) {
    Arbre234 temp = a;
    int cleMax;

    while (temp->fils[1]->t != 0) {
        temp = get_fils(temp, 0);
    }
    return get_cle(temp, 0);
}

Arbre234 RechercherCle (Arbre234 a, int cle)
{
  /*
     rechercher si la cle a est presente dans
     l'arbre a. Si oui, retourne le noeud ou se trouve la cle.
  */

  return NULL ;
}

int feuille(Arbre234 a){
  return a->t == 0;
}

void AnalyseStructureArbre (Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
  if (a != NULL && a->t !=0) {

        if (a->t == 2) {
            (*noeud2)++;
            if (!feuille(a->fils[1])) {
                AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
            } else {
                (*feuilles)++;
            }
        } else if (a->t == 3) {
            (*noeud3)++;
            if (!feuille(a->fils[1])) {
                AnalyseStructureArbre(a->fils[0], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
            } else {
                (*feuilles)++;
            }
        } else if (a->t == 4) {
            (*noeud4)++;
            if (!feuille(a->fils[1])) {
                AnalyseStructureArbre(a->fils[0], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[3], feuilles, noeud2, noeud3, noeud4);
            } else {
                (*feuilles)++;
            }
        }
        
    } else {
        (*feuilles)++;
    }
}

Arbre234 noeud_max (Arbre234 a)
{
  /*
    Retourne le noeud avec la somme maximale des cles internes
  */
  
  return NULL ;
}


void Afficher_Cles_Largeur (Arbre234 a)
{
  /*
    Afficher le cles de l'arbre a avec
    un parcours en largeur
  */

  return ;
}

void Affichage_Cles_Triees_Recursive (Arbre234 a)
{
  /* 
     Afficher les cles en ordre croissant
     Cette fonction sera recursive
  */
     
}

void Affichage_Cles_Triees_NonRecursive (Arbre234 a)
{
    /* 
     Afficher les cles en ordre croissant
     Cette fonction ne sera pas recursive
     Utiliser une pile
  */

}


void Detruire_Cle (Arbre234 *a, int cle)
{
  /*
    retirer la cle de l'arbre a
  */

  return ;
}



void voir(Arbre234 a,int b){
  printf ("==== Afficher arbre ====\n") ;
  afficher_arbre (a, 0) ;
}

void nrbcle(Arbre234 a){
  printf ("==== Le nombre de cles dans l'arbre ====\n") ;
  int nbrCles=NombreCles(a);
  printf("%d cles dans l'arbre\n",nbrCles);
}

void analys(Arbre234 a){
  printf ("==== Voici l'analyse complète de l'arbre ====\n") ;
  int *feuilles=0;
  int *noeud2=0;
  int *noeud3=0;
  int *noeud4=0;
  AnalyseStructureArbre(a,feuilles,noeud2,noeud3,noeud4);
  printf("L'arbre possède %d feuilles, %d noeud2, %d noeud3, %d noeud4\n",feuilles,noeud2,noeud3,noeud4);
}

int main (int argc, char **argv)
{
  Arbre234 a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre (argv [1]) ;
  voir(a,0);
  nrbcle(a);
  analys(a);


    printf("%d\n", CleMax(a));

}
