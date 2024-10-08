#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *proximo;
} tFilaSimples;

typedef struct {
    tFilaSimples *inicio;
    tFilaSimples *fim;
} tFila;

// Função para verificar se a fila está vazia
int filaVazia(tFila *fila) {
    return (fila->inicio == NULL);
}

// Função para criar um novo nó
tFilaSimples* criarNo(int dado) {
    tFilaSimples* novo = (tFilaSimples*) malloc(sizeof(tFilaSimples));
    if (novo) {
        novo->dado = dado;
        novo->proximo = NULL;
    }
    return novo;
}

// Função para enfileirar um número
void enfileirar(tFila *fila, int dado) {
    tFilaSimples* novo = criarNo(dado);
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    if (filaVazia(fila)) {
        fila->inicio = novo;
    } else {
        fila->fim->proximo = novo;
    }
    fila->fim = novo;
    printf("Número %d enfileirado.\n", dado);
}

// Função para desenfileirar um número
void desenfileirar(tFila *fila) {
    if (filaVazia(fila)) {
        printf("A fila está vazia!\n");
        return;
    }

    tFilaSimples *temp = fila->inicio;
    fila->inicio = fila->inicio->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;  // Se o último nó foi removido, ajustar o fim para NULL
    }

    printf("Número %d desenfileirado.\n", temp->dado);
    free(temp);
}

// Função para mostrar os elementos da fila
void mostrarFila(tFila *fila) {
    if (filaVazia(fila)) {
        printf("A fila está vazia!\n");
        return;
    }

    printf("Fila:\n");
    tFilaSimples *atual = fila->inicio;
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para destruir a fila e liberar memória
void destruirFila(tFila *fila) {
    tFilaSimples *atual = fila->inicio;
    int count = 0;
    
    while (atual != NULL) {
        tFilaSimples *temp = atual;
        atual = atual->proximo;
        free(temp);
        count++;
    }

    fila->inicio = NULL;
    fila->fim = NULL;
    printf("Fila destruída! Nós liberados: %d\n", count);
}

// Função para exibir o menu de opções
void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Verificar se a fila está vazia\n");
    printf("2. Enfileirar número\n");
    printf("3. Desenfileirar número\n");
    printf("4. Mostrar fila\n");
    printf("5. Destruir fila e finalizar\n");
    printf("Escolha uma opção: ");
}

int main() {
    tFila fila;
    fila.inicio = NULL;
    fila.fim = NULL;

    int opcao, valor;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (filaVazia(&fila))
                    printf("A fila está vazia.\n");
                else
                    printf("A fila não está vazia.\n");
                break;
            case 2:
                printf("Digite o valor a ser enfileirado: ");
                scanf("%d", &valor);
                enfileirar(&fila, valor);
                break;
            case 3:
                desenfileirar(&fila);
                break;
            case 4:
                mostrarFila(&fila);
                break;
            case 5:
                destruirFila(&fila);
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
