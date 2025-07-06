#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "tcep.h"


void carregar_lista_ceps_txt(thash *h, const char *arquivo, int limite);


void *aloca_cep(const char *cep, const char *cidade, const char *estado) {
    tcep *novo = malloc(sizeof(tcep));
    strncpy(novo->prefixo, cep, 8);
    novo->prefixo[8] = '\0';
    strncpy(novo->cidade, cidade, 49);
    novo->cidade[49] = '\0';
    strncpy(novo->estado, estado, 2);
    novo->estado[2] = '\0';
    return novo;
}

void carregar_ceps(thash *h, const char *arquivo, int limite) {
    FILE *f = fopen(arquivo, "r");
    if (!f) { perror("Erro ao abrir arquivo"); exit(EXIT_FAILURE); }

    char linha[128];
    fgets(linha, sizeof(linha), f);
    int count = 0;
    while (fgets(linha, sizeof(linha), f) && (limite < 0 || count < limite)) {
        char cep[9], cidade[50], estado[3];
        sscanf(linha, "%8[^,],%49[^,],%2s", cep, cidade, estado);
        void *novo = aloca_cep(cep, cidade, estado);
        hash_insere(h, novo);
        count++;
    }
    fclose(f);
}

void insere1000() {
    thash h;
    hash_constroi(&h, 1000, get_key_cep, 0.7f, 0); 
    carregar_lista_ceps_txt(&h, "dados/Lista_de_CEPs.txt", -1);
    hash_apaga(&h);
}

void insere6100() {
    thash h;
    hash_constroi(&h, 6100, get_key_cep, 0.7f, 0);
    carregar_lista_ceps_txt(&h, "dados/Lista_de_CEPs.txt", -1);
    hash_apaga(&h);
}


void carregar_lista_ceps_txt(thash *h, const char *arquivo, int limite) {
    FILE *f = fopen(arquivo, "r");
    if (!f) { perror("Erro ao abrir arquivo"); exit(EXIT_FAILURE); }
    char linha[256];
    int count = 0;

    fgets(linha, sizeof(linha), f);
    while (fgets(linha, sizeof(linha), f) && (limite < 0 || count < limite)) {
        char estado[3] = "", cidade[50] = "", cep[9] = "";
 
        if (sscanf(linha, "%2s %49[^0-9] %*s %8s", estado, cidade, cep) == 3) {
            
            for (int i = strlen(cidade) - 1; i >= 0 && (cidade[i] == ' ' || cidade[i] == '\t'); i--) cidade[i] = '\0';
            void *novo = aloca_cep(cep, cidade, estado);
            hash_insere(h, novo);
            count++;
        }
    }
    fclose(f);
}
