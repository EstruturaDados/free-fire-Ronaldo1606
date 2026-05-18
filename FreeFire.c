#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 20

/* =========================
   STRUCT PRINCIPAL
========================= */
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

/* =========================
   VARIÁVEIS GLOBAIS
========================= */
long comparacoes = 0;

/* =========================
   PROTÓTIPOS
========================= */
void bubbleSortNome(Componente[], int);
void insertionSortTipo(Componente[], int);
void selectionSortPrioridade(Componente[], int);
int buscaBinariaPorNome(Componente[], int, char[]);
void mostrarComponentes(Componente[], int);
double medirTempo(void (*algoritmo)(Componente[], int), Componente[], int);
void limparQuebraLinha(char *);

/* =========================
   FUNÇÕES AUXILIARES
========================= */
void limparQuebraLinha(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void mostrarComponentes(Componente v[], int n) {
    printf("\n--- COMPONENTES DA TORRE ---\n");
    for (int i = 0; i < n; i++) {
        printf("%2d. %-20s | %-12s | Prioridade: %d\n",
               i + 1, v[i].nome, v[i].tipo, v[i].prioridade);
    }
}

/* =========================
   BUBBLE SORT (NOME)
========================= */
void bubbleSortNome(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                Componente temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

/* =========================
   INSERTION SORT (TIPO)
========================= */
void insertionSortTipo(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 1; i < n; i++) {
        Componente chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (strcmp(v[j].tipo, chave.tipo) > 0) {
                v[j + 1] = v[j];
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
    }
}

/* =========================
   SELECTION SORT (PRIORIDADE)
========================= */
void selectionSortPrioridade(Componente v[], int n) {
    comparacoes = 0;
    for (int i = 0; i < n - 1; i++) {
        int menor = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (v[j].prioridade < v[menor].prioridade) {
                menor = j;
            }
        }
        Componente temp = v[i];
        v[i] = v[menor];
        v[menor] = temp;
    }
}

/* =========================
   BUSCA BINÁRIA (NOME)
========================= */
int buscaBinariaPorNome(Componente v[], int n, char nome[]) {
    int inicio = 0, fim = n - 1;
    long compBusca = 0;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        compBusca++;

        int cmp = strcmp(nome, v[meio].nome);
        if (cmp == 0) {
            printf("\n Componente encontrado com %ld comparações!\n", compBusca);
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }

    printf("\n Componente NÃO encontrado (%ld comparações).\n", compBusca);
    return -1;
}

/* =========================
   MEDIÇÃO DE TEMPO
========================= */
double medirTempo(void (*algoritmo)(Componente[], int), Componente v[], int n) {
    clock_t inicio = clock();
    algoritmo(v, n);
    clock_t fim = clock();
    return (double)(fim - inicio) / CLOCKS_PER_SEC;
}

/* =========================
   FUNÇÃO PRINCIPAL
========================= */
int main() {
    Componente componentes[MAX];
    int total, opcao;
    char chave[30];
    double tempo;

    printf("Quantos componentes deseja cadastrar (até 20)? ");
    scanf("%d", &total);
    getchar();

    if (total > MAX || total <= 0) {
        printf("Quantidade inválida.\n");
        return 0;
    }

    for (int i = 0; i < total; i++) {
        printf("\nComponente %d\n", i + 1);

        printf("Nome: ");
        fgets(componentes[i].nome, 30, stdin);
        limparQuebraLinha(componentes[i].nome);

        printf("Tipo: ");
        fgets(componentes[i].tipo, 20, stdin);
        limparQuebraLinha(componentes[i].tipo);

        printf("Prioridade (1 a 10): ");
        scanf("%d", &componentes[i].prioridade);
        getchar();
    }

    printf("\nEscolha o algoritmo de ordenação:\n");
    printf("1 - Bubble Sort (Nome)\n");
    printf("2 - Insertion Sort (Tipo)\n");
    printf("3 - Selection Sort (Prioridade)\n");
    printf("Opção: ");
    scanf("%d", &opcao);
    getchar();

    switch (opcao) {
        case 1:
            tempo = medirTempo(bubbleSortNome, componentes, total);
            printf("\nBubble Sort executado!");
            break;
        case 2:
            tempo = medirTempo(insertionSortTipo, componentes, total);
            printf("\nInsertion Sort executado!");
            break;
        case 3:
            tempo = medirTempo(selectionSortPrioridade, componentes, total);
            printf("\nSelection Sort executado!");
            break;
        default:
            printf("\nOpção inválida!");
            return 0;
    }

    printf("\nComparações realizadas: %ld", comparacoes);
    printf("\nTempo de execução: %.6f segundos\n", tempo);

    mostrarComponentes(componentes, total);

    if (opcao == 1) {
        printf("\nDigite o nome do componente-chave: ");
        fgets(chave, 30, stdin);
        limparQuebraLinha(chave);
        buscaBinariaPorNome(componentes, total, chave);
    }

    printf("\n Torre de fuga pronta para montagem!\n");
    return 0;
}