#include "projeto.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>


#define MAX_REGISTROS 100
extern struct Cliente clientes[MAX_REGISTROS];
extern int total_clientes;
extern struct Cliente* buscar_cliente_por_cpf(const char* cpf);

// Cadastra um novo cliente
void cadastrar_cliente(void) {
    if (total_clientes >= MAX_REGISTROS) {
        printf("ERRO: Limite máximo de clientes atingido (%d).\n", MAX_REGISTROS);
        return;
    }

    struct Cliente novo_cliente;

    printf("\n--- CADASTRO DE NOVO CLIENTE ---\n");
    limpar_buffer_entrada();

    printf("Nome: ");
    ler_string(novo_cliente.nome, MAX_NOME);

    printf("Telefone: ");
    ler_string(novo_cliente.telefone, MAX_TELEFONE);

    printf("E-mail: ");
    ler_string(novo_cliente.email, MAX_EMAIL);

    printf("CPF: ");
    ler_string(novo_cliente.cpf, MAX_CPF);

    // Verifica se o CPF já existe
    if (buscar_cliente_por_cpf(novo_cliente.cpf) != NULL) {
        printf("\nERRO: Já existe um cliente com o CPF %s.\n", novo_cliente.cpf);
        return;
    }

    novo_cliente.ativo = 1; // Cliente ativo por padrão

    clientes[total_clientes] = novo_cliente;
    total_clientes++;

    printf("\nCliente cadastrado com sucesso!\n", novo_cliente.nome);
}

// Busca um cliente pelo CPF
void buscar_cliente_cpf(void) {
    char cpf_busca[MAX_CPF];
    printf("\n--- BUSCAR CLIENTE POR CPF ---\n");
    limpar_buffer_entrada();
    printf("Digite o CPF do cliente: ");
    ler_string(cpf_busca, MAX_CPF);

    struct Cliente* cliente = buscar_cliente_por_cpf(cpf_busca);

    if (cliente != NULL) {
        printf("\nCliente encontrado:\n");
        printf("Nome: %s\n", cliente->nome);
        printf("Telefone: %s\n", cliente->telefone);
        printf("E-mail: %s\n", cliente->email);
        printf("CPF: %s\n", cliente->cpf);
    } else {
        printf("\nNenhum cliente encontrado com o CPF %s.\n", cpf_busca);
    }
}

// Busca um cliente pelo nome
void buscar_cliente_nome(void) {
    char nome_busca[MAX_NOME];
    printf("\n--- BUSCAR CLIENTE POR NOME ---\n");
    limpar_buffer_entrada();
    printf("Digite o nome (ou parte do nome) do cliente: ");
    ler_string(nome_busca, MAX_NOME);

    int encontrados = 0;
    printf("\nResultados da busca por %s: \n", nome_busca);

    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].ativo && strcasestr(clientes[i].nome, nome_busca) != NULL) {
            printf("--------------------------\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("E-mail: %s\n", clientes[i].email);
            printf("CPF: %s\n", clientes[i].cpf);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum cliente encontrado com o nome '%s'.\n", nome_busca);
    }
}

// Lista todos os clientes cadastrados
void listar_clientes(void) {
    printf("\n--- LISTA DE CLIENTES ---\n");
    if (total_clientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].ativo) {
            printf("--------------------------\n");
            printf("Nome: %s\n", clientes[i].nome);
            printf("Telefone: %s\n", clientes[i].telefone);
            printf("E-mail: %s\n", clientes[i].email);
            printf("CPF: %s\n", clientes[i].cpf);
        }
    }
}

// Menu de Clientes
void menu_clientes(void) {
    int opcao;
    do {
        printf("\n[34m--- MÓDULO DE CLIENTES ---[0m\n");
        printf("1. Cadastrar Novo Cliente\n");
        printf("2. Buscar Cliente por CPF\n");
        printf("3. Buscar Cliente por Nome\n");
        printf("4. Listar Todos os Clientes\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1: cadastrar_cliente(); break;
            case 2: buscar_cliente_cpf(); break;
            case 3: buscar_cliente_nome(); break;
            case 4: listar_clientes(); break;
            case 0: break;
            default: printf("\nOpção inválida. Tente novamente.\n");
        }
        if (opcao != 0) pausar_tela();
    } while (opcao != 0);
}
