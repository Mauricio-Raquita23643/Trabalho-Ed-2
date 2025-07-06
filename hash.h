#ifndef HASH_H
#define HASH_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"


typedef struct {
    uintptr_t *table;
    int size;
    int max;
    uintptr_t deleted;
    char *(*get_key)(void *);

    float ocupacao_max; 
    int hash_type;      
} thash;

int hash_constroi(thash *h, int nbuckets, char *(*get_key)(void *), float ocupacao_max, int hash_type);
int hash_insere(thash *h, void *bucket);
void *hash_busca(thash h, const char *key);
int hash_remove(thash *h, const char *key);
void hash_apaga(thash *h);
char *get_key_cep(void *reg);

#endif
