#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *anterior, *proximo;
} tListaDupla;

tListaDupla* criarNo(int dado) {
    tListaDupla* novo = (tListaDupla*) malloc(sizeof(tListaDupla));
    if (novo) {
        novo->dado = dado;
        novo->anterior = NULL;
        novo->proximo = NULL;
    }
    return novo;
}

int listaVazia(tListaDupla *lista) {
    return (lista == NULL);
}

void inserirOrdenado(tListaDupla **lista, int dado) {
    tListaDupla *novo = criarNo(dado);
    if (!novo) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    if (listaVazia(*lista)) {
        *lista = novo;
        return;
    }

    tListaDupla *atual = *lista;

    // Inserir no início
    if (dado < atual->dado) {
        novo->proximo = atual;
        atual->anterior = novo;
        *lista = novo;
        return;
    }

    // Inserir no meio ou no fim
    while (atual->proximo != NULL && atual->proximo->dado < dado) {
        atual = atual->proximo;
    }

    novo->proximo = atual->proximo;
    novo->anterior = atual;

    if (atual->proximo != NULL) {
        atual->proximo->anterior = novo;
    }

    atual->proximo = novo;
}

void removerElemento(tListaDupla **lista, int dado) {
    if (listaVazia(*lista)) {
        printf("Lista vazia!\n");
        return;
    }

    tListaDupla *atual = *lista;

    // Procurar o nó a ser removido
    while (atual != NULL && atual->dado != dado) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        printf("Elemento %d não encontrado!\n", dado);
        return;
    }

    // Ajustar os ponteiros e remover o nó
    if (atual->anterior != NULL) {
        atual->anterior->proximo = atual->proximo;
    } else {
        *lista = atual->proximo;
    }

    if (atual->proximo != NULL) {
        atual->proximo->anterior = atual->anterior;
    }

    free(atual);
    printf("Elemento %d removido!\n", dado);
}

void pesquisarElemento(tListaDupla *lista, int dado) {
    tListaDupla *atual = lista;
    int indice = 0;
    while (atual != NULL) {
        if (atual->dado == dado) {
            printf("Elemento %d encontrado no indice %d!\n", dado, indice);
            return;
        }
        atual = atual->proximo;
        indice++;
    }
    printf("Elemento %d não encontrado!\n", dado);
}

void listarCrescente(tListaDupla *lista) {
    tListaDupla *atual = lista;
    printf("Lista em ordem crescente: ");
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

void listarDecrescente(tListaDupla *lista) {
    if (listaVazia(lista)) {
        printf("Lista vazia!\n");
        return;
    }

    // Ir para o final da lista
    tListaDupla *atual = lista;
    while (atual->proximo != NULL) {
        atual = atual->proximo;
    }

    // Listar em ordem decrescente
    printf("Lista em ordem decrescente: ");
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->anterior;
    }
    printf("\n");
}

void destruirLista(tListaDupla **lista) {
    tListaDupla *atual = *lista;
    int count = 0;
    while (atual != NULL) {
        tListaDupla *temp = atual;
        atual = atual->proximo;
        free(temp);
        count++;
    }
    *lista = NULL;
    printf("Lista destruída! Nós liberados: %d\n", count);
}

void menu() {
    printf("\n--- MENU ---\n");
    printf("1. Verificar se a lista está vazia\n");
    printf("2. Inserir elemento (em ordem)\n");
    printf("3. Remover elemento\n");
    printf("4. Pesquisar elemento\n");
    printf("5. Listar elementos em ordem crescente\n");
    printf("6. Listar elementos em ordem decrescente\n");
    printf("7. Destruir lista e finalizar\n");
    printf("Escolha uma opção: ");
}

int main() {
    tListaDupla *lista = NULL;
    int opcao, valor;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (listaVazia(lista))
                    printf("A lista está vazia.\n");
                else
                    printf("A lista não está vazia.\n");
                break;
            case 2:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                inserirOrdenado(&lista, valor);
                break;
            case 3:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                removerElemento(&lista, valor);
                break;
            case 4:
                printf("Digite o valor a ser pesquisado: ");
                scanf("%d", &valor);
                pesquisarElemento(lista, valor);
                break;
            case 5:
                listarCrescente(lista);
                break;
            case 6:
                listarDecrescente(lista);
                break;
            case 7:
                destruirLista(&lista);
                printf("Programa finalizado.\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
