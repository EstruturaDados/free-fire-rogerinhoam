#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constante para a capacidade máxima da mochila
#define MAX_ITENS 10

// --- Definição da Struct ---
// A struct Item representa um objeto dentro do jogo.
// Agrupa dados de texto (nome, tipo) e numéricos (quantidade).

typedef struct {
    char nome[30];
    char tipo[20]; // Ex: Arma, Municao, Cura
    int quantidade;
} Item;

// --- Protótipos das Funções ---
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);
void limparBuffer(); // Função auxiliar para limpeza de entrada

int main() {
    // Vetor de structs representando a mochila
    Item mochila[MAX_ITENS];
    
    // Variável de controle da quantidade atual de itens
    int totalItens = 0;
    int opcao;

    do {
        // Interface do Usuário
        printf("\n=== MOCHILA DE LOOT (%d/%d) ===\n", totalItens, MAX_ITENS);
        printf("1. Coletar Item (Cadastrar)\n");
        printf("2. Jogar Fora (Remover)\n");
        printf("3. Abrir Mochila (Listar)\n");
        printf("4. Procurar Item (Buscar)\n");
        printf("0. Sair do Jogo\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer(); // Limpa o \n deixado pelo scanf

        switch (opcao) {
            case 1:
                inserirItem(mochila, &totalItens);
                listarItens(mochila, totalItens); // Lista após operação conforme requisito
                break;
            case 2:
                removerItem(mochila, &totalItens);
                listarItens(mochila, totalItens);
                break;
            case 3:
                listarItens(mochila, totalItens);
                break;
            case 4:
                buscarItem(mochila, totalItens);
                break;
            case 0:
                printf("Saindo do inventario...\n");
                break;
            default:
                printf("\n[!] Opcao invalida.\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

// Função para cadastrar um novo item na mochila
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n[!] A mochila esta cheia! Voce precisa remover algo antes.\n");
        return;
    }

    printf("\n--- Coletando Novo Recurso ---\n");
    
    printf("Nome do item: ");
    // O espaço antes do %[^\n] ignora espaços em branco iniciais
    scanf(" %[^\n]", mochila[*total].nome);
    
    printf("Tipo (Arma/Municao/Cura/Ferramenta): ");
    scanf(" %[^\n]", mochila[*total].tipo);
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);

    (*total)++; // Incrementa o contador total de itens
    printf("[+] Item adicionado com sucesso!\n");
}

// Função para remover um item pelo nome
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n[!] A mochila esta vazia.\n");
        return;
    }

    char nomeBusca[30];
    int encontrado = 0;
    int i, j;

    printf("\n--- Descartar Item ---\n");
    printf("Digite o nome do item para remover: ");
    scanf(" %[^\n]", nomeBusca);

    // Busca sequencial para encontrar o índice do item
    for (i = 0; i < *total; i++) {
        // strcmp retorna 0 se as strings forem iguais
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = 1;
            
            // Lógica de remoção em lista sequencial (Shifting):
            // Move todos os itens à direita uma posição para a esquerda
            // para cobrir o "buraco" deixado pelo item removido.
            
            for (j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            
            (*total)--; // Decrementa o total de itens
            printf("[-] Item '%s' removido da mochila.\n", nomeBusca);
            break; // Encerra o loop após remover
        }
    }

    if (!encontrado) {
        printf("[!] Item nao encontrado na mochila.\n");
    }
}

// Função para listar todos os itens
void listarItens(Item mochila[], int total) {
    printf("\n--- Conteudo da Mochila ---\n");
    if (total == 0) {
        printf("(Mochila Vazia)\n");
        return;
    }

    printf("%-20s | %-15s | %s\n", "NOME", "TIPO", "QTD");
    printf("----------------------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        printf("%-20s | %-15s | %d\n", 
            mochila[i].nome, 
            mochila[i].tipo, 
            mochila[i].quantidade);
    }
    printf("----------------------------------------------------\n");
}

// Função de busca sequencial por nome
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\n[!] A mochila esta vazia.\n");
        return;
    }

    char nomeBusca[30];
    int encontrado = 0;

    printf("\n--- Procurar Item ---\n");
    printf("Digite o nome do item: ");
    scanf(" %[^\n]", nomeBusca);

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n[V] Item Localizado:\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            encontrado = 1;
            break; // Para a busca ao encontrar
        }
    }

    if (!encontrado) {
        printf("[X] Item nao encontrado.\n");
    }
}

// Função auxiliar para limpar buffer do teclado
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}