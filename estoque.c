#include "projeto.h"
#include <stdio.h>
#include <string.h>

#define MAX_REGISTROS 100
extern struct Peca estoque[MAX_REGISTROS];
extern int total_pecas;
extern struct Peca* buscar_peca_por_nome(const char* nome);

// Cadastra uma nova peça no estoque
void cadastrar_peca(void) {
    if (total_pecas >= MAX_REGISTROS) {
        printf("ERRO: Limite máximo de peças atingido (%d).\n", MAX_REGISTROS);
        return;
    }

    struct Peca nova_peca;

    printf("\n--- CADASTRO DE NOVA PEÇA ---\n");
    limpar_buffer_entrada();

    printf("Nome da peça: ");
    ler_string(nova_peca.nome, MAX_NOME_PECA);

    // Verifica se a peça já existe
    if (buscar_peca_por_nome(nova_peca.nome) != NULL) {
        printf("\nERRO: Peça com o nome %s já cadastrada. Use a opção de baixa/entrada.\n", nova_peca.nome);
        return;
    }

    printf("Quantidade em estoque: ");
    nova_peca.quantidade = ler_inteiro();

    printf("Preço de custo (R$): ");
    nova_peca.preco = ler_float();

    nova_peca.ativa = 1;

    estoque[total_pecas] = nova_peca;
    total_pecas++;

    printf("\nPeça cadastrada com sucesso! Estoque inicial: %s, %d\n", nova_peca.nome, nova_peca.quantidade);
}

// Lista todas as peças no estoque
void listar_pecas(void) {
    printf("\n--- ESTOQUE DE PEÇAS ---\n");
    if (total_pecas == 0) {
        printf("Nenhuma peça cadastrada no estoque.\n");
        return;
    }

    printf("Nome da Peça | Quantidade | Preço de Custo (R$)\n");
    printf("---|---|---\n");
    for (int i = 0; i < total_pecas; i++) {
        if (estoque[i].ativa) {
            printf("%s | %d | %.2f\n",
                   estoque[i].nome,
                   estoque[i].quantidade,
                   estoque[i].preco);
        }
    }
}

// Dá baixa na quantidade de uma peça no estoque
void dar_baixa_peca(void) {
    char nome_peca[MAX_NOME_PECA];
    int baixa;

    printf("\n--- BAIXA DE PEÇA NO ESTOQUE ---\n");
    listar_pecas();

    printf("Nome da Peça para dar baixa (0 para cancelar): ");
    limpar_buffer_entrada();
    ler_string(nome_peca, MAX_NOME_PECA);

    if (strcmp(nome_peca, "0") == 0) return;

    struct Peca *peca = buscar_peca_por_nome(nome_peca);
    if (peca == NULL) {
        printf("\nERRO: Peça com o nome %s não encontrada.\n", nome_peca);
        return;
    }

    printf("Peça selecionada: %s (Estoque atual: %d)\n", peca->nome, peca->quantidade);
    printf("Quantidade a ser baixada: ");
    baixa = ler_inteiro();

    if (baixa <= 0) {
        printf("\nQuantidade inválida. A baixa deve ser um número positivo.\n");
        return;
    }

    if (baixa > peca->quantidade) {
        printf("\nERRO: Quantidade a ser baixada (%d) é maior que o estoque atual (%d).\n", baixa, peca->quantidade);
        return;
    }

    peca->quantidade -= baixa;
    printf("\nBaixa de %d unidades da peça '%s' realizada com sucesso. Novo estoque: %d",
           baixa, peca->nome, peca->quantidade);
}

// Menu do Estoque (Pecas)
void menu_pecas(void) {
    int opcao;
    do {
        printf("\n--- MÓDULO DE ESTOQUE DE PEÇAS ---\n");
        printf("1. Cadastrar Nova Peça\n");
        printf("2. Listar Peças em Estoque\n");
        printf("3. Dar Baixa em Peça (Venda/Uso)\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1: cadastrar_peca(); break;
            case 2: listar_pecas(); break;
            case 3: dar_baixa_peca(); break;
            case 0: break;
            default: printf("\nOpção inválida. Tente novamente.\n");
        }
        if (opcao != 0) pausar_tela();
    } while (opcao != 0);
}
