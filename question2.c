#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *proximo;
} tPilhaSimples;

int pilhaVazia(tPilhaSimples *pilha) {
    return (pilha == NULL);
}

tPilhaSimples* criarNo(int dado) {
    tPilhaSimples* novo = (tPilhaSimples*) malloc(sizeof(tPilhaSimples));
    if (novo) {
        novo->dado = dado;
        novo->proximo = NULL;
    }
    return novo;
}

void empilhar(tPilhaSimples **pilha, int dado) {
    tPilhaSimples* novo = criarNo(dado);
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    novo->proximo = *pilha;
    *pilha = novo;
    printf("Número %d empilhado.\n", dado);
}

void desempilhar(tPilhaSimples **pilha) {
    if (pilhaVazia(*pilha)) {
        printf("A pilha está vazia!\n");
        return;
    }

    tPilhaSimples* temp = *pilha;
    *pilha = (*pilha)->proximo;
    printf("Número %d desempilhado.\n", temp->dado);
    free(temp);
}

void mostrarPilha(tPilhaSimples *pilha) {
    if (pilhaVazia(pilha)) {
        printf("A pilha está vazia!\n");
        return;
    }

    printf("Pilha:\n");
    tPilhaSimples *atual = pilha;
    while (atual != NULL) {
        printf("%d\n", atual->dado);
        atual = atual->proximo;
    }
}

void destruirPilha(tPilhaSimples **pilha) {
    tPilhaSimples *atual = *pilha;
    int count = 0;
    
    while (atual != NULL) {
        tPilhaSimples *temp = atual;
        atual = atual->proximo;
        free(temp);
        count++;
    }
    
    *pilha = NULL;
    printf("Pilha destruída! Nós liberados: %d\n", count);
}

void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Verificar se a pilha está vazia\n");
    printf("2. Empilhar número\n");
    printf("3. Desempilhar número\n");
    printf("4. Mostrar pilha\n");
    printf("5. Destruir pilha e finalizar\n");
    printf("Escolha uma opção: ");
}

int main() {
    tPilhaSimples *pilha = NULL;
    int opcao, valor;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (pilhaVazia(pilha))
                    printf("A pilha está vazia.\n");
                else
                    printf("A pilha não está vazia.\n");
                break;
            case 2:
                printf("Digite o valor a ser empilhado: ");
                scanf("%d", &valor);
                empilhar(&pilha, valor);
                break;
            case 3:
                desempilhar(&pilha);
                break;
            case 4:
                mostrarPilha(pilha);
                break;
            case 5:
                destruirPilha(&pilha);
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 5);

    return 0;
}
