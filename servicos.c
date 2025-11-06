#include "projeto.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

// Variáveis globais (declaradas em projeto_util.c)
#define MAX_REGISTROS 100
extern struct Servico servicos[MAX_REGISTROS];
extern int total_servicos;
extern int proximo_id_servico;
extern struct Cliente* buscar_cliente_por_cpf(const char* cpf);
extern struct Servico* encontrar_servico_por_id(int id);
extern int gerar_id_servico(void);

void cadastrar_servico(void) {
    if (total_servicos >= MAX_REGISTROS) {
        printf("ERRO: Limite máximo de serviços atingido (%d).\n", MAX_REGISTROS);
        return;
    }

    struct Servico novo_servico;
    char cpf_cliente[MAX_CPF];

    printf("\n--- REGISTRO DE NOVO SERVIÇO ---\n");
    limpar_buffer_entrada();

    printf("CPF do Cliente (0 para cancelar): ");
    ler_string(cpf_cliente, MAX_CPF);

    if (strcmp(cpf_cliente, "0") == 0) return;

    struct Cliente *cliente = buscar_cliente_por_cpf(cpf_cliente);
    if (cliente == NULL) {
        printf("\nERRO: Cliente com CPF %s não encontrado.\n", cpf_cliente);
        return;
    }

    // Preenche os dados do novo serviço
    novo_servico.id = gerar_id_servico();
    strcpy(novo_servico.cpf_cliente, cpf_cliente);

    printf("Cliente selecionado: %s\n", cliente->nome);

    printf("Descrição do problema/equipamento (máx %d caracteres): ", MAX_DESCRICAO_PROBLEMA - 1);
    ler_string(novo_servico.descricao_problema, MAX_DESCRICAO_PROBLEMA);

    printf("Valor a ser cobrado (R$): ");
    novo_servico.valor = ler_float();

    strcpy(novo_servico.status, "Na bancada");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(novo_servico.data_entrada, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    novo_servico.urgente = 0; // Não urgente por padrão
    novo_servico.ativo = 1;

    servicos[total_servicos] = novo_servico;
    total_servicos++;

    printf("\nServiço registrado com sucesso! (ID: [33m%d[0m) Status inicial: [33m%s[0m\n",
           novo_servico.id, novo_servico.status);
}

void atualizar_status_servico(void) {
    printf("\n--- ATUALIZAR STATUS DE SERVIÇO ---\n");
    printf("ID do Serviço (0 para cancelar): ");
    int id_servico = ler_inteiro();

    if (id_servico == 0) return;

    struct Servico *servico = encontrar_servico_por_id(id_servico);
    if (servico == NULL) {
        printf("\nERRO: Serviço com ID %d não encontrado.\n", id_servico);
        return;
    }

    printf("Serviço ID %d (Cliente CPF %s) - Status atual: %s\n",
           servico->id, servico->cpf_cliente, servico->status);

    printf("\nNovos Status Possíveis:\n");
    printf("1. Na bancada\n");
    printf("2. Aguardando peça\n");
    printf("3. Pronto para retirada\n");
    printf("4. Entregue\n");
    printf("Escolha o novo status: ");

    int opcao_status = ler_inteiro();
    char novo_status[MAX_STATUS];

    switch (opcao_status) {
        case 1: strcpy(novo_status, "Na bancada"); break;
        case 2: strcpy(novo_status, "Aguardando peça"); break;
        case 3: strcpy(novo_status, "Pronto para retirada"); break;
        case 4: strcpy(novo_status, "Entregue"); break;
        default:
            printf("\n[31mOpção de status inválida. Cancelando atualização.[0m\n");
            return;
    }

    strcpy(servico->status, novo_status);
    printf("\nStatus do Serviço ID [33m%d[0m atualizado para: %s\n", servico->id, servico->status);
}

void listar_servicos(void) {
    printf("\n--- LISTA DE SERVIÇOS ---\n");
    if (total_servicos == 0) {
        printf("Nenhum serviço registrado.\n");
        return;
    }

    printf("ID | Cliente (CPF) | Descrição | Valor (R$) | Status | Data Entrada\n");
    printf("---|---|---|---|---|---\n");
    for (int i = 0; i < total_servicos; i++) {
        if (servicos[i].ativo) {
            printf("%d | %s | %.30s... | %.2f | %s | %s\n",
                   servicos[i].id,
                   servicos[i].cpf_cliente,
                   servicos[i].descricao_problema,
                   servicos[i].valor,
                   servicos[i].status,
                   servicos[i].data_entrada);
        }
    }
}

void menu_servicos(void) {
    int opcao;
    do {
        printf("\n[34m--- MÓDULO DE SERVIÇOS ---[0m\n");
        printf("1. Registrar Novo Serviço\n");
        printf("2. Atualizar Status de Serviço\n");
        printf("3. Listar Todos os Serviços\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1: cadastrar_servico(); break;
            case 2: atualizar_status_servico(); break;
            case 3: listar_servicos(); break;
            case 0: break;
            default: printf("\nOpção inválida. Tente novamente.\n");
        }
        if (opcao != 0) pausar_tela();
    } while (opcao != 0);
}
