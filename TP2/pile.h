
#ifndef PILE_H
#define PILE_H

#define MAX_PILE_SIZE 100
#define TYPE_ARBRE 0

#include "a234.h"


typedef struct
{
    int type;
    union entier_arbre234
    {
        Arbre234 node;
        int entier;
    } ent_abr;

} val_node;

typedef struct
{
    int top;
    val_node tableau[MAX_PILE_SIZE];
} pile_t, *ppile_t;

ppile_t creer_pile();

int detruire_pile(ppile_t p);

int pile_vide(ppile_t p);

int pile_pleine(ppile_t p);

pnoeud234 depiler(ppile_t p);
int depiler_entier(ppile_t p);

int empiler(ppile_t p, pnoeud234 pn);
int empiler_entier(ppile_t p, int pn);

#endif