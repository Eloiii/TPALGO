#include <stdlib.h>
#include "abr.h"
#include "pile.h"
#include <stdio.h>

ppile_t creer_pile() {
    ppile_t pile = malloc(sizeof(pile_t));
    pile->sommet = 0;
    return pile;
}

int detruire_pile(ppile_t p) {
    free(p);
    return 1;
}

int pile_vide(ppile_t p) {
    if (p->sommet == 0) return 1;
    else return 0;
}

int pile_pleine(ppile_t p) {
    if (p->sommet == MAX_PILE_SIZE) return 1;
    else return 0;
}

pnoeud_t depiler(ppile_t p) {
    if (p->sommet == 0) return NULL;
    else {
        pnoeud_t elem = p->Tab[--p->sommet];
        p->Tab[p->sommet] = NULL;
        return elem;
    }
}


int empiler(ppile_t p, pnoeud_t pn) {
//    printf("%d\n", pn->cle);
    if (!pile_pleine(p)) {
        p->Tab[p->sommet] = pn;
        p->sommet++;
        return 1;
    }
    return 0;
}
