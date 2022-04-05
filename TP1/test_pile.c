#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
#include "pile.h"


void test0() {
    ppile_t p = creer_pile();
    int res = pile_vide(p);
    if (res == 1) printf("test0 passed\n");
    else printf("test0 failed\n");
}

void test1() {
    ppile_t p = creer_pile();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_PILE_SIZE; i++) {
        pn->cle = i;
        empiler(p, pn);
    }
    int res = pile_pleine(p);
    if (res == 1) printf("test1 passed\n");
    else printf("test1 failed\n");
}

void test2() {
    ppile_t p = creer_pile();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_PILE_SIZE; i++) {
        pn->cle = i;
        empiler(p, pn);
        depiler(p);
    }
    int res = pile_vide(p);
    if (res == 1) printf("test2 passed\n");
    else printf("test2 failed\n");
}

void test3() {
    ppile_t p = creer_pile();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_PILE_SIZE; i++) {
        pn->cle = i;
        empiler(p, pn);
    }
    depiler(p);
    int res = p->sommet;
    if (res == MAX_PILE_SIZE - 1) printf("test3 passed\n");
    else printf("test3 failed\n");
}

int main() {
    test0();
    test1();
    test2();
    test3();
}