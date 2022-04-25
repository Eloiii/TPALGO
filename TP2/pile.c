#include <stdlib.h>
#include <stdio.h>
#include "pile.h"

ppile_t creer_pile()
{
    ppile_t pile = (ppile_t)malloc(sizeof(ppile_t));
    pile->top = -1;
    return pile;
}

int detruire_pile(ppile_t p)
{
    if (p == NULL)
    {
        return 0;
    }
    free(p);
    return 1;
}

int pile_vide(ppile_t p)
{
    int pileVide = 1;
    if (p->top >= 0)
    {
        pileVide = 0;
    }
    return pileVide;
}

int pile_pleine(ppile_t p)
{
    int pilePleine = 0;
    if (p->top >= MAX_PILE_SIZE)
    {
        pilePleine = 1;
    }
    return pilePleine;
}

pnoeud234 depiler(ppile_t p)
{
    pnoeud234 element = NULL;
    if (p->top >= 0)
    {
        element = p->tableau[p->top].ent_abr.node;
        p->tableau[p->top].ent_abr.node = NULL;
        p->top = p->top - 1;
    }
    return element;
}

int depiler_entier(ppile_t p)
{
    if (pile_vide(p))
    {
        return -1;
    }
    int nb_entier = p->tableau[p->top].ent_abr.entier;
    p->tableau[p->top].ent_abr.entier = 0;
    p->top = p->top - 1;
    return nb_entier;
}

int empiler(ppile_t p, pnoeud234 pn)
{
    int succes = 0;
    if (p->top + 1 < MAX_PILE_SIZE)
    {
        p->top = p->top + 1;
        p->tableau[p->top].ent_abr.node = pn;
        p->tableau[p->top].type = 0;
        succes = 1;
    }
    return succes;
}

int empiler_entier(ppile_t p, int pn)
{
    int succes = 0;
    if (p->top + 1 < MAX_PILE_SIZE)
    {
        p->top = p->top + 1;
        p->tableau[p->top].ent_abr.entier = pn;
        p->tableau[p->top].type = 1;
        succes = 1;
    }
    return succes;
}
