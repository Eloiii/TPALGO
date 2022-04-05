#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
#include "file.h"


void test0() {
    pfile_t f = creer_file();
    int res = file_vide(f);
    if (res == 1) printf("test0 passed\n");
    else printf("test0 failed\n");
}

void test1() {
    pfile_t f = creer_file();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pn->cle = i;
        enfiler(f, pn);
    }
    int res = file_pleine(f);
    if (res == 1) printf("test1 passed\n");
    else printf("test1 failed\n");
}

void test2() {
    pfile_t f = creer_file();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pn->cle = i;
        enfiler(f, pn);
        defiler(f);
    }
    int res = file_vide(f);
    if (res == 1) printf("test2 passed\n");
    else printf("test2 failed\n");
}

void test3() {
    pfile_t f = creer_file();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pn->cle = i;
        enfiler(f, pn);
    }
    defiler(f);
    int res = f->queue;
    if (res == MAX_FILE_SIZE - 1) printf("test3 passed\n");
    else printf("test3 failed\n");
}

void test4() {
    pfile_t f = creer_file();

    pnoeud_t p1 = malloc(sizeof(pnoeud_t));
    p1->cle = 2;
    pnoeud_t p2 = malloc(sizeof(pnoeud_t));
    p2->cle = 8;
    pnoeud_t p3 = malloc(sizeof(pnoeud_t));
    p3->cle = 4;
    pnoeud_t p4 = malloc(sizeof(pnoeud_t));
    p4->cle = 16;

    enfiler(f, p1);
    enfiler(f, p2);
    enfiler(f, p3);
    enfiler(f, p4);

    pnoeud_t dequeued = defiler(f);
    if (dequeued != p1) {
        printf("test 4 failed\n");
        return;
    }
    dequeued = defiler(f);
    if (dequeued != p2) {
        printf("test 4 failed\n");
        return;
    }
    dequeued = defiler(f);
    if (dequeued != p3) {
        printf("test 4 failed\n");
        return;
    }
    dequeued = defiler(f);
    if (dequeued != p4) {
        printf("test 4 failed\n");
        return;
    }
    if (file_vide(f))
        printf("test 4 passed\n");
    else
        printf("test 4 failed\n");

}

void test5() {
    pfile_t f = creer_file();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_FILE_SIZE + 1; i++) {
        pn->cle = i;
        if (i == MAX_FILE_SIZE) {
            if (!enfiler(f, pn)) {
                printf("test 5 passed\n");
                return;
            }
        } else
            enfiler(f, pn);
    }
    printf("test 5 failed\n");
}

void test6() {
    pfile_t f = creer_file();
    pnoeud_t pn = malloc(sizeof(pnoeud_t));
    for (int i = 0; i < MAX_FILE_SIZE; i++) {
        pn->cle = i;
        enfiler(f, pn);
    }
    defiler(f);
    defiler(f);
    pn->cle = 88;
    enfiler(f, pn);
    pn->cle = 99;
    enfiler(f, pn);
    pn->cle = 111;
    if (!enfiler(f, pn))
        printf("test 6 passed\n");
    else
        printf("test 6 failed\n");


}

int main() {
    test0();
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
}