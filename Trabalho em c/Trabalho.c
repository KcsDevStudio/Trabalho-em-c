#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Antônio Kayo César Do Nascimento Cavalcante */
//2024 0221 6988
/* MARLON MENDES GONÇALVES*/
//MATRICULA : 202403279444

typedef struct fruta {
    int codigo;
    char nome[20];
    int quantidade;
    struct fruta* proximo;
} Fruta;

Fruta* criarFruta(int codigo, char nome[], int quantidade) {
    Fruta* nova_fruta = (Fruta*) malloc(sizeof(Fruta));
    nova_fruta->codigo = codigo;
    strcpy(nova_fruta->nome, nome);
    nova_fruta->quantidade = quantidade;
    nova_fruta->proximo = NULL;
    return nova_fruta;
}

int frutaExiste(Fruta* cabeca, int codigo) {
    Fruta* atual = cabeca;
    while (atual != NULL) {
        if (atual->codigo == codigo) return 1;
        atual = atual->proximo;
    }
    return 0;
}

void adicionarFruta(Fruta** cabeca_ref, int codigo, char nome[], int quantidade) {
    if (frutaExiste(*cabeca_ref, codigo)) {
        printf("Código já existe!\n");
        return;
    }
    Fruta* nova_fruta = criarFruta(codigo, nome, quantidade);
    if (*cabeca_ref == NULL) {
        *cabeca_ref = nova_fruta;
        return;
    }
    Fruta* ultima = *cabeca_ref;
    while (ultima->proximo != NULL) {
        ultima = ultima->proximo;
    }
    ultima->proximo = nova_fruta;
    printf("Fruta cadastrada com sucesso!\n");
}

void listarFrutas(Fruta* cabeca) {
    if (cabeca == NULL) {
        printf("Nenhuma fruta cadastrada!\n");
        return;
    }
    Fruta* atual = cabeca;
    while (atual != NULL) {
        printf("Código: %d, Nome: %s, Quantidade: %d\n", atual->codigo, atual->nome, atual->quantidade);
        atual = atual->proximo;
    }
}

Fruta* buscarFruta(Fruta* cabeca, int codigo) {
    Fruta* atual = cabeca;
    while (atual != NULL) {
        if (atual->codigo == codigo) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

void atualizarFruta(Fruta* cabeca, int codigo, char nome[], int quantidade) {
    Fruta* fruta = buscarFruta(cabeca, codigo);
    if (fruta == NULL) {
        printf("Fruta não encontrada!\n");
        return;
    }
    strcpy(fruta->nome, nome);
    fruta->quantidade = quantidade;
    printf("Fruta atualizada com sucesso!\n");
}

void excluirFruta(Fruta** cabeca_ref, int codigo) {
    Fruta* atual = *cabeca_ref;
    Fruta* anterior = NULL;
    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->proximo;
    }
    if (atual == NULL) {
        printf("Fruta não encontrada!\n");
        return;
    }
    if (atual->quantidade > 0) {
        printf("Não é possível excluir a fruta com estoque disponível!\n");
        return;
    }
    if (anterior == NULL) {
        *cabeca_ref = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }
    free(atual);
    printf("Fruta excluída com sucesso!\n");
}

void venderFruta(Fruta* cabeca, int codigo, int quantidade) {
    Fruta* fruta = buscarFruta(cabeca, codigo);
    if (fruta == NULL) {
        printf("Fruta não encontrada!\n");
        return;
    }
    if (fruta->quantidade < quantidade) {
        printf("Quantidade insuficiente no estoque!\n");
        return;
    }
    fruta->quantidade -= quantidade;
    printf("Venda realizada com sucesso!\n");
    FILE* arquivo = fopen("vendas.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "Fruta Vendida: %s, Quantidade: %d\n", fruta->nome, quantidade);
        fclose(arquivo);
    } else {
        printf("Erro ao abrir o arquivo de vendas!\n");
    }
}

void menu() {
    printf("\nMenu:\n");
    printf("1. Cadastrar fruta\n");
    printf("2. Listar frutas\n");
    printf("3. Buscar fruta\n");
    printf("4. Alterar fruta\n");
    printf("5. Excluir fruta\n");
    printf("6. Vender fruta\n");
    printf("7. Sair\n");
}

int main() {
    Fruta* cabeca = NULL;
    int opcao, codigo, quantidade;
    char nome[20];

    do {
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                printf("Digite o nome da fruta: ");
                scanf("%s", nome);
                printf("Digite a quantidade: ");
                scanf("%d", &quantidade);
                adicionarFruta(&cabeca, codigo, nome, quantidade);
                break;

            case 2:
                listarFrutas(cabeca);
                break;

            case 3:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                Fruta* fruta = buscarFruta(cabeca, codigo);
                if (fruta != NULL) {
                    printf("Código: %d, Nome: %s, Quantidade: %d\n", fruta->codigo, fruta->nome, fruta->quantidade);
                } else {
                    printf("Fruta não encontrada!\n");
                }
                break;

            case 4:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                printf("Digite o novo nome da fruta: ");
                scanf("%s", nome);
                printf("Digite a nova quantidade: ");
                scanf("%d", &quantidade);
                atualizarFruta(cabeca, codigo, nome, quantidade);
                break;

            case 5:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                excluirFruta(&cabeca, codigo);
                break;

            case 6:
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                printf("Digite a quantidade a ser vendida: ");
                scanf("%d", &quantidade);
                venderFruta(cabeca, codigo, quantidade);
                break;

            case 7:
                printf("Saindo...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 7);

    return 0;
}
