#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura da lista encadeada
typedef struct Item {
    char *nome;
    int quantidade;
    struct Item* proximo;
} Item;

Item* inicio = NULL;

// Criar novo item
Item* criarItem(const char* nome, int quantidade) {
    Item* novo = (Item*)malloc(sizeof(Item));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o item.\n");
        exit(1);
    }

    novo->nome = (char*)malloc(strlen(nome) + 1);
    if (novo->nome == NULL) {
        printf("Erro ao alocar memória para o nome.\n");
        free(novo);
        exit(1);
    }

    strcpy(novo->nome, nome);
    novo->quantidade = quantidade;
    novo->proximo = NULL;

    return novo;
}

// Adicionar item
void adicionarItem() {
    char nome[100];
    int quantidade;

    printf("Nome do item: ");
    scanf(" %[^\n]", nome);
    printf("Quantidade: ");
    scanf("%d", &quantidade);

    Item* novo = criarItem(nome, quantidade);

    if (inicio == NULL) {
        inicio = novo;
    } else {
        Item* temp = inicio;
        while (temp->proximo != NULL) {
            temp = temp->proximo;
        }
        temp->proximo = novo;
    }

    printf("Item adicionado com sucesso!\n");
}

// Listar itens
void listarItens() {
    if (inicio == NULL) {
        printf("Lista de compras vazia.\n");
        return;
    }

    printf("\n--- Lista de Compras ---\n");
    Item* temp = inicio;
    int i = 1;
    while (temp != NULL) {
        printf("%d. %s - %d unidade(s)\n", i++, temp->nome, temp->quantidade);
        temp = temp->proximo;
    }
}

// Buscar item
void buscarItem() {
    char nome[100];
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nome);

    Item* temp = inicio;
    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            printf("Item encontrado: %s - %d unidade(s)\n", temp->nome, temp->quantidade);
            return;
        }
        temp = temp->proximo;
    }

    printf("Item não encontrado.\n");
}

// Editar item
void editarItem() {
    char nome[100];
    printf("Digite o nome do item a editar: ");
    scanf(" %[^\n]", nome);

    Item* temp = inicio;
    while (temp != NULL) {
        if (strcmp(temp->nome, nome) == 0) {
            char novoNome[100];
            int novaQtd;

            printf("Novo nome: ");
            scanf(" %[^\n]", novoNome);
            printf("Nova quantidade: ");
            scanf("%d", &novaQtd);

            free(temp->nome);
            temp->nome = (char*)malloc(strlen(novoNome) + 1);
            strcpy(temp->nome, novoNome);
            temp->quantidade = novaQtd;

            printf("Item editado com sucesso!\n");
            return;
        }
        temp = temp->proximo;
    }

    printf("Item não encontrado.\n");
}

// Remover item
void removerItem() {
    char nome[100];
    printf("Digite o nome do item a remover: ");
    scanf(" %[^\n]", nome);

    Item *atual = inicio, *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            if (anterior == NULL) {
                inicio = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual->nome);
            free(atual);
            printf("Item removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado.\n");
}

// Esvaziar lista
void esvaziarLista() {
    Item* temp = inicio;
    while (temp != NULL) {
        Item* apagar = temp;
        temp = temp->proximo;
        free(apagar->nome);
        free(apagar);
    }
    inicio = NULL;
    printf("Lista esvaziada com sucesso!\n");
}

// Menu
void menu() {
    int opcao;
    do {
        printf("\n--- Menu Lista de Compras ---\n");
        printf("1. Adicionar item\n");
        printf("2. Listar itens\n");
        printf("3. Remover item\n");
        printf("4. Editar item\n");
        printf("5. Buscar item\n");
        printf("6. Esvaziar lista\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: adicionarItem(); break;
            case 2: listarItens(); break;
            case 3: removerItem(); break;
            case 4: editarItem(); break;
            case 5: buscarItem(); break;
            case 6: esvaziarLista(); break;
            case 7: esvaziarLista(); printf("Saindo...\n"); break;
            default: printf("Opção inválida.\n");
        }
    } while (opcao != 7);
}

// Função principal obrigatória
int main() {
    menu();
    return 0;
}
