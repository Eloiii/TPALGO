#include <stdlib.h>
#include <stdio.h>

#include "file.h"

pfile_t creer_file() {
    pfile_t file = malloc(sizeof(file_t));
    file->tete = -1;
    file->queue = -1;
    return file;
}

int detruire_file(pfile_t f) {
    free(f);
    return 1;
}

int file_vide(pfile_t f) {
    return (f->tete == -1);
}

int file_pleine(pfile_t f) {
    return (f->queue + 1) % MAX_FILE_SIZE == f->tete;
}

psommet_t defiler(pfile_t f) {
    if (file_vide(f))
        return NULL;
    psommet_t removed = f->Tab[f->tete];
    f->Tab[f->tete] = NULL;
    f->tete = (f->tete + 1) % MAX_FILE_SIZE;
    if (f->tete > f->queue) {
        f->tete = -1;
        f->queue = -1;
    }
    return removed;
}

int enfiler(pfile_t f, psommet_t p) {
    if (file_pleine(f))
        return 0;
    if (f->tete == -1)
        f->tete = 0;
    f->queue = (f->queue + 1) % MAX_FILE_SIZE;
    f->Tab[f->queue] = p;
    return 1;
}
