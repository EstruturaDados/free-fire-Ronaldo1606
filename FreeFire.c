#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

/* 
   Struct que representa um item do inventário.
   Cada item possui nome, tipo e quantidade.
*/
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

/* Vetor que representa a mochila */
Item mochila[MAX_ITENS];

/* Controla quantos itens estão cadastrados */
int totalItens = 0;

/* Prototipação das funções */
void inserirItem();
void removerItem();
void listarItens();
void buscarItem();

/* Função principal */
int main() {
    int opcao;

    do {
        printf("\n===== INVENTÁRIO DO JOGADOR =====\n");
        printf("1 - Cadastrar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Buscar item\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpa buffer

        switch (opcao) {
            case 1:
                inserirItem();
                listarItens();
                break;
            case 2:
                removerItem();
                listarItens();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                buscarItem();
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

/* Função para inserir um novo item na mochila */
void inserirItem() {
    if (totalItens >= MAX_ITENS) {
        printf("\nMochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    printf("\n=== Cadastro de Item ===\n");

    printf("Nome do item: ");
    fgets(mochila[totalItens].nome, 30, stdin);
    mochila[totalItens].nome[strcspn(mochila[totalItens].nome, "\n")] = '\0';

    printf("Tipo do item (arma, munição, cura, etc): ");
    fgets(mochila[totalItens].tipo, 20, stdin);
    mochila[totalItens].tipo[strcspn(mochila[totalItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[totalItens].quantidade);
    getchar();

    totalItens++;

    printf("\nItem cadastrado com sucesso!\n");
}

/* Função para remover um item pelo nome */
void removerItem() {
    char nomeBusca[30];
    int encontrado = 0;

    if (totalItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;

            /* Desloca os itens para preencher o espaço */
            for (int j = i; j < totalItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }

            totalItens--;
            printf("\nItem removido com sucesso!\n");
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
}

/* Função para listar todos os itens da mochila */
void listarItens() {
    if (totalItens == 0) {
        printf("\nMochila vazia.\n");
        return;
    }

    printf("\n=== Itens na Mochila ===\n");
    for (int i = 0; i < totalItens; i++) {
        printf("\nItem %d\n", i + 1);
        printf("Nome: %s\n", mochila[i].nome);
        printf("Tipo: %s\n", mochila[i].tipo);
        printf("Quantidade: %d\n", mochila[i].quantidade);
    }
}

/* Função de busca sequencial por nome */
void buscarItem() {
    char nomeBusca[30];
    int encontrado = 0;

    printf("\nDigite o nome do item a ser buscado: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < totalItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("\nItem não encontrado.\n");
    }
}