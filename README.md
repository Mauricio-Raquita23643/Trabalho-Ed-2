# Trabalho-Ed-2

# Comparação de Métodos de Inserção e Busca em Tabelas Hash

## Descrição

Este projeto realiza uma análise comparativa de desempenho entre diferentes métodos de inserção e busca em tabelas hash, utilizando uma grande base de dados de CEPs brasileiros. O objetivo é avaliar a eficiência de diferentes estratégias de hashing e colisão, além de analisar o impacto do redimensionamento dinâmico da tabela.

## Estrutura do Projeto

- `main.c`: Função principal do programa.
- `hash.c` / `hash.h`: Implementação das funções de tabela hash, incluindo inserção, busca, remoção, redimensionamento e funções de hash.
- `tcep.h`: Definição da estrutura de dados para armazenar informações de CEP.
- `insercao_comparativa.c`: Código para testes comparativos de inserção e busca.
- `Makefile`: Script para compilação do projeto.
- `dados/Lista_de_CEPs.txt`: Lista de faixas de CEPs por município.
- `dados/ceps.csv`: Base de dados de CEPs para testes.
- `relatorio.txt`: Relatório de perfilamento de desempenho (gprof).
- `programa` / `programa.exe`: Executável gerado.
- `.vscode/`: Configurações do Visual Studio Code.

## Como Compilar

Para compilar o projeto, utilize o comando abaixo no terminal:

```sh
make
```

O executável será gerado com o nome `programa` (Linux) ou `programa.exe` (Windows).

## Como Executar

Execute o programa passando os arquivos de dados conforme necessário. Exemplo:

```sh
./programa
```

O programa irá carregar os dados de CEP, construir a tabela hash e realizar os testes de inserção e busca, gerando estatísticas de desempenho.

## Principais Funções

- `carregar_lista_ceps_txt`: Carrega a lista de CEPs do arquivo texto.
- `hash_insere`: Insere elementos na tabela hash.
- `hash_busca`: Realiza buscas na tabela hash.
- `hash_apaga`: Remove elementos da tabela hash.
- `hash_constroi`: Inicializa/constroi a tabela hash.
- `redimensiona_tabela`: Redimensiona a tabela hash dinamicamente.
- `get_key_cep`: Gera a chave para o CEP.
- Funções de teste: `busca10`, `busca20`, ..., `busca99`, e suas versões `_duplo`.

## Relatório de Desempenho

O arquivo [`relatorio.txt`](relatorio.txt) contém o perfilamento do programa utilizando o `gprof`. Os principais gargalos de desempenho identificados foram:

- **hash_insere**: 39.86% do tempo total.
- **carregar_lista_ceps_txt**: 27.27% do tempo total.
- **hashf**: 20.28% do tempo total.
- **aloca_cep**: 3.50% do tempo total.

Esses dados indicam que a maior parte do tempo é gasta na inserção de elementos na tabela hash e no carregamento dos dados.

## Como Gerar o Relatório de Perfilamento

Para gerar o relatório de perfilamento, compile com as flags de profiling e execute:

```sh
make clean
gcc -pg -o programa main.c hash.c insercao_comparativa.c
./programa
gprof programa gmon.out > relatorio.txt
```

## Autores

- [Mauricio Raquita]

