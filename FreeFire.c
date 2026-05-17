#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 20

/* =========================
   ESTRUTURAS
========================= */
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

/* =========================
   VARIÁVEIS GLOBAIS
========================= */
Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

No* mochilaLista = NULL;

/* Contadores de comparações */
int comparacoesSeqVetor = 0;
int comparacoesBinVetor = 0;
int comparacoesSeqLista = 0;

/* =========================
   FUNÇÕES – VETOR
========================= */
void inserirItemVetor(Item item) {
    if (totalVetor < MAX_ITENS) {
        mochilaVetor[totalVetor++] = item;
    }
}

void listarVetor() {
    printf("\n--- Mochila (Vetor) ---\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("%s | %s | %d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}

int buscarSequencialVetor(char nome[]) {
    comparacoesSeqVetor = 0;
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSeqVetor++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}

void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                Item temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
}

int buscarBinariaVetor(char nome[]) {
    int inicio = 0, fim = totalVetor - 1;
    comparacoesBinVetor = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinVetor++;

        int cmp = strcmp(nome, mochilaVetor[meio].nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            inicio = meio + 1;
    }
    return -1;
}

/* =========================
   FUNÇÕES – LISTA ENCADEADA
========================= */
void inserirItemLista(Item item) {
    No* novo = malloc(sizeof(No));
    novo->dados = item;
    novo->proximo = mochilaLista;
    mochilaLista = novo;
}

void listarLista() {
    printf("\n--- Mochila (Lista Encadeada) ---\n");
    No* atual = mochilaLista;
    while (atual) {
        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}

No* buscarSequencialLista(char nome[]) {
    comparacoesSeqLista = 0;
    No* atual = mochilaLista;

    while (atual) {
        comparacoesSeqLista++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

/* =========================
   PROGRAMA PRINCIPAL
========================= */
int main() {
    Item itens[] = {
        {"Pistola", "Arma", 1},
        {"Munição", "Munição", 30},
        {"KitMedico", "Cura", 2},
        {"Faca", "Arma", 1},
        {"Granada", "Explosivo", 3}
    };

    for (int i = 0; i < 5; i++) {
        inserirItemVetor(itens[i]);
        inserirItemLista(itens[i]);
    }

    listarVetor();
    listarLista();

    printf("\n=== BUSCA SEQUENCIAL ===\n");
    buscarSequencialVetor("Granada");
    buscarSequencialLista("Granada");

    printf("Comparações (Vetor): %d\n", comparacoesSeqVetor);
    printf("Comparações (Lista): %d\n", comparacoesSeqLista);

    printf("\n=== BUSCA BINÁRIA (VETOR) ===\n");
    ordenarVetor();
    buscarBinariaVetor("Granada");
    printf("Comparações (Binária): %d\n", comparacoesBinVetor);

    return 0;
}