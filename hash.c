
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "tcep.h"

uint32_t hashf(const char* str, uint32_t h){
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

uint32_t hashf2(const char *str) {
    uint32_t h = 0;
    for (; *str; ++str)
        h = 31 * h + *str;
    return (h % 97) + 1; 
}

char *get_key_cep(void *reg) {
    return ((tcep *)reg)->prefixo;
}

int hash_constroi(thash *h, int nbuckets, char *(*get_key)(void *), float ocupacao_max, int hash_type) {
    h->table = calloc(sizeof(void *), nbuckets + 1);
    if (!h->table) return EXIT_FAILURE;

    h->max = nbuckets + 1;
    h->size = 0;
    h->deleted = (uintptr_t)&(h->size);
    h->get_key = get_key;
    h->ocupacao_max = ocupacao_max;
    h->hash_type = hash_type;

    return EXIT_SUCCESS;
}

int redimensiona_tabela(thash *h) {
    thash nova;
    int novo_tamanho = (h->max - 1) * 2;
    if (hash_constroi(&nova, novo_tamanho, h->get_key, h->ocupacao_max, h->hash_type) != EXIT_SUCCESS) return EXIT_FAILURE;

    for (int i = 0; i < h->max; i++) {
        if (h->table[i] != 0 && h->table[i] != h->deleted) {
            hash_insere(&nova, (void *)h->table[i]);
        }
    }
    free(h->table);
    *h = nova;
    return EXIT_SUCCESS;
}

int hash_insere(thash *h, void *bucket) {
    if ((float)(h->size + 1) / h->max > h->ocupacao_max) {
        if (redimensiona_tabela(h) != EXIT_SUCCESS) return EXIT_FAILURE;
    }

    uint32_t hash = hashf(h->get_key(bucket), 0x12345678);
    int pos = hash % h->max;
    int passo = (h->hash_type == 1) ? hashf2(h->get_key(bucket)) % h->max : 1;

    while (h->table[pos] != 0 && h->table[pos] != h->deleted) {
        pos = (pos + passo) % h->max;
    }

    h->table[pos] = (uintptr_t)bucket;
    h->size++;
    return EXIT_SUCCESS;
}

void *hash_busca(thash h, const char *key) {
    uint32_t hash = hashf(key, 0x12345678);
    int pos = hash % h.max;
    int passo = (h.hash_type == 1) ? hashf2(key) % h.max : 1;

    while (h.table[pos] != 0) {
        if (h.table[pos] != h.deleted && strcmp(h.get_key((void *)h.table[pos]), key) == 0)
            return (void *)h.table[pos];
        pos = (pos + passo) % h.max;
    }
    return NULL;
}

int hash_remove(thash *h, const char *key) {
    uint32_t hash = hashf(key, 0x12345678);
    int pos = hash % h->max;
    int passo = (h->hash_type == 1) ? hashf2(key) % h->max : 1;

    while (h->table[pos] != 0) {
        if (h->table[pos] != h->deleted && strcmp(h->get_key((void *)h->table[pos]), key) == 0) {
            free((void *)h->table[pos]);
            h->table[pos] = h->deleted;
            h->size--;
            return EXIT_SUCCESS;
        }
        pos = (pos + passo) % h->max;
    }
    return EXIT_FAILURE;
}

void hash_apaga(thash *h) {
    for (int i = 0; i < h->max; i++) {
        if (h->table[i] != 0 && h->table[i] != h->deleted) {
            free((void *)h->table[i]);
        }
    }
    free(h->table);
}
