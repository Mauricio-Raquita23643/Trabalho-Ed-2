
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"
#include "tcep.h"

void *aloca_cep(const char *cep, const char *cidade, const char *estado);
void carregar_ceps(thash *h, const char *arquivo, int limite);
void insere1000();
void insere6100();
void carregar_lista_ceps_txt(thash *h, const char *arquivo, int limite);

void exemplo_simples() {
    thash h;
    hash_constroi(&h, 10, get_key_cep, 0.7f, 0); // 0 = linear

    hash_insere(&h, aloca_cep("12345000", "Campo Grande", "MS"));
    hash_insere(&h, aloca_cep("12346000", "Dourados", "MS"));

    tcep *c = hash_busca(h, "12345000");
    if (c) printf("CEP encontrado: %s - %s/%s\n", c->prefixo, c->cidade, c->estado);

    hash_apaga(&h);
}

void busca_ocupacao(int ocupacao_percent, int hash_type) {
    thash h;
    int nbuckets = 6100;
    int total = nbuckets * ocupacao_percent / 100;
    hash_constroi(&h, nbuckets, get_key_cep, 0.99f, hash_type);
    carregar_lista_ceps_txt(&h, "dados/Lista_de_CEPs.txt", total);

    hash_busca(h, "30140071"); 
    hash_apaga(&h);
}


void busca10() { busca_ocupacao(10, 0); }
void busca20() { busca_ocupacao(20, 0); }
void busca30() { busca_ocupacao(30, 0); }
void busca40() { busca_ocupacao(40, 0); }
void busca50() { busca_ocupacao(50, 0); }
void busca60() { busca_ocupacao(60, 0); }
void busca70() { busca_ocupacao(70, 0); }
void busca80() { busca_ocupacao(80, 0); }
void busca90() { busca_ocupacao(90, 0); }
void busca99() { busca_ocupacao(99, 0); }

void busca10_duplo() { busca_ocupacao(10, 1); }
void busca20_duplo() { busca_ocupacao(20, 1); }
void busca30_duplo() { busca_ocupacao(30, 1); }
void busca40_duplo() { busca_ocupacao(40, 1); }
void busca50_duplo() { busca_ocupacao(50, 1); }
void busca60_duplo() { busca_ocupacao(60, 1); }
void busca70_duplo() { busca_ocupacao(70, 1); }
void busca80_duplo() { busca_ocupacao(80, 1); }
void busca90_duplo() { busca_ocupacao(90, 1); }
void busca99_duplo() { busca_ocupacao(99, 1); }

int main() {
    exemplo_simples();

    printf("Testando com 1000 buckets (crescimento dinâmico)...\n");
    insere1000();
    printf("Testando com 6100 buckets fixos...\n");
    insere6100();


    for (int i = 0; i < 20; i++) {
        busca10(); busca20(); busca30(); busca40(); busca50(); busca60(); busca70(); busca80(); busca90(); busca99();
        busca10_duplo(); busca20_duplo(); busca30_duplo(); busca40_duplo(); busca50_duplo(); busca60_duplo(); busca70_duplo(); busca80_duplo(); busca90_duplo(); busca99_duplo();
    }
    return 0;
}
