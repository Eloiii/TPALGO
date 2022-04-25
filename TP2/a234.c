#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a234.h"
#include "file.h"
#include "pile.h"

#define max(a, b) ((a) > (b) ? (a) : (b))

Arbre234 get_fils(Arbre234 a, int fils)
{
    switch (a->t)
    {
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

int get_cle(Arbre234 a, int cle)
{
    switch (a->t)
    {
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

int hauteur(Arbre234 a)
{
    int h0, h1, h2, h3;

    if (a == NULL)
        return 0;

    if (a->t == 0)
        return 0;

    h0 = hauteur(a->fils[0]);
    h1 = hauteur(a->fils[1]);
    h2 = hauteur(a->fils[2]);
    h3 = hauteur(a->fils[3]);

    return 1 + max(max(h0, h1), max(h2, h3));
}

int NombreCles(Arbre234 a)
{
    if (a != NULL && a->t != 0)
    {
        int res = a->t - 1;
        if (a->t == 2)
        {
            return res + NombreCles(a->fils[0]) + NombreCles(a->fils[1]);
        }
        else if (a->t == 3)
        {
            return res + NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]);
        }
        else if (a->t == 4)
        {
            return res + NombreCles(a->fils[0]) + NombreCles(a->fils[1]) + NombreCles(a->fils[2]) +
                   NombreCles(a->fils[3]);
        }
    }
    return 0;
}

int CleMax(Arbre234 a)
{
    Arbre234 temp = a;

    while (temp->fils[1]->t != 0)
    {
        temp = get_fils(temp, temp->t - 1);
    }

    return get_cle(temp, temp->t - 2);
}

int CleMin(Arbre234 a)
{
    Arbre234 temp = a;

    while (temp->fils[1]->t != 0)
    {
        temp = get_fils(temp, 0);
    }
    return get_cle(temp, 0);
}

int position(int x, Arbre234 A)
{
    int pos, trouve = 0;
    for (pos = 0; pos < A->t && !trouve; pos++)
    {
        trouve = (x <= A->cles[pos]);
    }
    return pos - 1;
}

Arbre234 RechercherCle(Arbre234 a, int cle)
{
    int pos;
    if (a == NULL)
        return 0;
    else
    {
        pos = position(cle, a);
        if (cle == get_cle(a, pos))
            return a;
        else
        {
            if (get_cle(a, pos) > cle && a->t == 2)
                return RechercherCle(get_fils(a, pos - 1), cle);
            return RechercherCle(get_fils(a, pos), cle);
        }
    }
}

int feuille(Arbre234 a)
{
    return a->t == 0;
}

void AnalyseStructureArbre(Arbre234 a, int *feuilles, int *noeud2, int *noeud3, int *noeud4)
{
    if (a != NULL)
    {

        if (a->t == 2)
        {
            (*noeud2)++;
            if (!feuille(a->fils[1]))
            {
                AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
            }
            else
            {
                (*feuilles) = *feuilles + 2;
            }
        }
        else if (a->t == 3)
        {
            (*noeud3)++;
            if (!feuille(a->fils[1]))
            {
                AnalyseStructureArbre(a->fils[0], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
            }
            else
            {
                (*feuilles) = *feuilles + 3;
            }
        }
        else if (a->t == 4)
        {
            (*noeud4)++;
            if (!feuille(a->fils[1]))
            {
                AnalyseStructureArbre(a->fils[0], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[1], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[2], feuilles, noeud2, noeud3, noeud4);
                AnalyseStructureArbre(a->fils[3], feuilles, noeud2, noeud3, noeud4);
            }
            else
            {
                (*feuilles) = *feuilles + 4;
            }
        }
    }
    else
    {
        (*feuilles)++;
    }
}

Arbre234 max_deux_noeuds(Arbre234 a, Arbre234 b)
{
    int noeudA = 0;
    int noeudB = 0;

    for (int i = 0; i < a->t - 1; i++)
    {
        noeudA += get_cle(a, i);
    }

    for (int j = 0; j < b->t - 1; j++)
    {
        noeudB += get_cle(b, j);
    }
    if (noeudA > noeudB)
    {
        return a;
    }
    else
    {
        return b;
    }
}

Arbre234 noeud_max_rec(Arbre234 a, Arbre234 max_noeud)
{
    max_noeud = max_deux_noeuds(max_noeud, a);
    if (!feuille(a->fils[1]))
    {
        for (int i = 0; i < a->t; i++)
        {
            max_noeud = noeud_max_rec(get_fils(a, i), max_noeud);
        }
    }
    return max_noeud;
}

Arbre234 noeud_max(Arbre234 a)
{
    return noeud_max_rec(a, a);
}

void Afficher_Cles_Largeur(Arbre234 a)
{
    pfile_t f = creer_file();
    if (a != NULL)
        enfiler(f, a);
    while (file_vide(f) != 1)
    {
        pnoeud234 temp = defiler(f);
        for (int i = 0; i < temp->t; i++)
        {
            enfiler(f, get_fils(temp, i));
            if (i < temp->t - 1)
            {
                printf("%i ", get_cle(temp, i));
            }
        }
    }
    return;
}

void Affichage_Cles_Triees_Recursive(Arbre234 a)
{
    if (a != NULL && a->t != 0)
    {
        for (int i = 0; i < a->t - 1; ++i)
        {
            Affichage_Cles_Triees_Recursive(get_fils(a, i));
            printf(" %d |", get_cle(a, i));
            if (a->t < 3 || i == a->t - 2)
                Affichage_Cles_Triees_Recursive(get_fils(a, i + 1));
        }
    }
}

int getIndex(Arbre234 a)
{
    if (a->t > 0)
    {
        return a->t - 1;
    }
    else
    {
        return a->t;
    }
}

int top_type(ppile_t p)
{
    if (!pile_vide(p))
    {
        return p->tableau[p->top].type;
    }
    return -1;
}

void Affichage_Cles_Triees_NonRecursive(Arbre234 a)
{
    printf("\n");
    ppile_t p = creer_pile();
    empiler(p, a);
    while (!pile_vide(p))
    {
        if (top_type(p) == 1)
        {
            int courant_int = depiler_entier(p);
            printf("%d | ", courant_int);
        }
        else
        {
            Arbre234 arbre_courant = depiler(p);
            if (arbre_courant != NULL && arbre_courant->t != 0)
            {
                int index = getIndex(arbre_courant);
                for (int i = 0; i < index; i++)
                {
                    empiler(p, get_fils(arbre_courant, index - i));
                    empiler_entier(p, get_cle(arbre_courant, index - 1 - i));
                }
                empiler(p, get_fils(arbre_courant, 0));
            }
        }
    }
    printf("\n");
    detruire_pile(p);
}

void Detruire_Cle(Arbre234 *a, int cle)
{
    /*
      retirer la cle de l'arbre a
    */

    return;
}

void voir(Arbre234 a)
{
    printf("==== Afficher arbre ====\n");
    afficher_arbre(a, 0);
}

void nrbcle(Arbre234 a)
{
    printf("==== Le nombre de cles dans l'arbre ====\n");
    int nbrCles = NombreCles(a);
    printf("%d cles dans l'arbre\n", nbrCles);
}

void analys(Arbre234 a)
{
    printf("==== Voici l'analyse complète de l'arbre ====\n");
    int *feuilles = malloc(sizeof(int));
    int *noeud2 = malloc(sizeof(int));
    int *noeud3 = malloc(sizeof(int));
    int *noeud4 = malloc(sizeof(int));
    *feuilles = 0;
    *noeud2 = 0;
    *noeud3 = 0;
    *noeud4 = 0;
    AnalyseStructureArbre(a, feuilles, noeud2, noeud3, noeud4);
    printf("L'arbre possède %d feuilles, %d noeud2, %d noeud3, %d noeud4\n", *feuilles, *noeud2, *noeud3, *noeud4);
}
void testRechercheCle(Arbre234 a)
{
    printf("-----10-----\n");
    afficher_arbre(RechercherCle(a, 10), 0);
    printf("-----15-----\n");
    afficher_arbre(RechercherCle(a, 15), 0);
    printf("-----30-----\n");
    afficher_arbre(RechercherCle(a, 30), 0);
    printf("-----35-----\n");
    afficher_arbre(RechercherCle(a, 35), 0);
    printf("-----50-----\n");
    afficher_arbre(RechercherCle(a, 50), 0);
    printf("-----40-----\n");
    afficher_arbre(RechercherCle(a, 40), 0);
    printf("-----20-----\n");
    afficher_arbre(RechercherCle(a, 20), 0);
    printf("-----28-----\n");
    afficher_arbre(RechercherCle(a, 28), 0);
    printf("-----12-----\n");
    afficher_arbre(RechercherCle(a, 12), 0);
    printf("-----13-----\n");
    afficher_arbre(RechercherCle(a, 13), 0);
    printf("-----14-----\n");
    afficher_arbre(RechercherCle(a, 14), 0);
    printf("-----11-----\n");
    afficher_arbre(RechercherCle(a, 11), 0);
    printf("-----3-----\n");
    afficher_arbre(RechercherCle(a, 3), 0);
    printf("-----4-----\n");
    afficher_arbre(RechercherCle(a, 4), 0);
    printf("-----7-----\n");
    afficher_arbre(RechercherCle(a, 7), 0);
    printf("-----8-----\n");
    afficher_arbre(RechercherCle(a, 8), 0);
    printf("-----1-----\n");
    afficher_arbre(RechercherCle(a, 1), 0);
}
int main(int argc, char **argv)
{
    Arbre234 a;

    if (argc != 2)
    {
        fprintf(stderr, "il manque le parametre nom de fichier\n");
        exit(-1);
    }

    a = lire_arbre(argv[1]);
    afficher_arbre(a, 0);
    //  voir(a);
    //  nrbcle(a);
    //  analys(a);
    afficher_arbre(noeud_max(a), 0);
    //    printf("%d\n", CleMax(a));

    //    testRechercheCle(a);

    //    Afficher_Cles_Largeur(a);

    Affichage_Cles_Triees_Recursive(a);
    Affichage_Cles_Triees_NonRecursive(a);
}
