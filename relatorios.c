#include "projeto.h"
#include <stdio.h>
#include <string.h>

#define MAX_REGISTROS 100
extern struct Servico servicos[MAX_REGISTROS];
extern int total_servicos;
extern struct Peca estoque[MAX_REGISTROS];
extern int total_pecas;

void relatorio_prontos_para_retirada(void) {
    printf("\n--- RELATÓRIO: SERVIÇOS PRONTOS PARA RETIRADA ---\n");
    int encontrados = 0;

    printf("ID | Cliente (CPF) | Descrição | Valor (R$) | Data Entrada\n");
    printf("---|---|---|---|---\n");

    for (int i = 0; i < total_servicos; i++) {
        if (servicos[i].ativo && strcmp(servicos[i].status, "Pronto para retirada") == 0) {
            printf("%d | %s | %.30s... | %.2f | %s\n",
                   servicos[i].id,
                   servicos[i].cpf_cliente,
                   servicos[i].descricao_problema,
                   servicos[i].valor,
                   servicos[i].data_entrada);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhum serviço encontrado com o status 'Pronto para retirada'.\n");
    }
}

void relatorio_pecas_estoque_baixo(void) {
    printf("\n--- RELATÓRIO: PEÇAS COM ESTOQUE BAIXO ( < 5 UNIDADES) ---\n");
    int encontrados = 0;

    printf("Nome da Peça | Quantidade | Preço de Custo (R$)\n");
    printf("---|---|---\n");

    for (int i = 0; i < total_pecas; i++) {
        if (estoque[i].ativa && estoque[i].quantidade < 5) {
            printf("%s | %d | %.2f\n",
                   estoque[i].nome,
                   estoque[i].quantidade,
                   estoque[i].preco);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("\nNenhuma peça encontrada com estoque baixo.\n");
    }
}

void relatorio_financeiro_mensal(void) {
    printf("\n--- RELATÓRIO FINANCEIRO MENSAL ---\n");
    
    printf("Digite o mês que deseja consultar (1 a 12): ");
    int mes_busca = ler_inteiro();

    if (mes_busca < 1 || mes_busca > 12) {
        printf("\nMês inválido. Por favor, digite um número entre 1 e 12.\n");
        return;
    }

    float total_faturado = 0.0;
    int encontrados = 0;

    for (int i = 0; i < total_servicos; i++) {
        
        if (servicos[i].ativo && strcmp(servicos[i].status, "Entregue") == 0) {
            
            int dia, mes_servico, ano;
            
            int result = sscanf(servicos[i].data_entrada, "%d/%d/%d", &dia, &mes_servico, &ano);
            
            if (result == 3 && mes_servico == mes_busca) {
              
                total_faturado += servicos[i].valor;
                encontrados++;
            }
        }
    }

    if (encontrados > 0) {
        printf("\nTotal faturado no mês %d: R$ %.2f\n", mes_busca, total_faturado);
        printf("(Baseado em %d serviço(s) marcado(s) como 'Entregue'.)\n", encontrados);
    } else {
        printf("\nNenhum serviço 'Entregue' foi encontrado para o mês %d.\n", mes_busca);
    }
}

void menu_relatorios(void) {
    int opcao;
    do {
        printf("\n--- MÓDULO DE RELATÓRIOS ---\n");
        printf("1. Serviços Prontos para Retirada\n");
        printf("2. Peças com Estoque Baixo\n");

        printf("3. Relatório Financeiro Mensal\n");
        printf("0. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1: relatorio_prontos_para_retirada(); break;
            case 2: relatorio_pecas_estoque_baixo(); break;
            case 3: relatorio_financeiro_mensal(); break; 
            case 0: break;
            default: printf("\nOpção inválida. Tente novamente.\n");
        }
        if (opcao != 0) pausar_tela();
    } while (opcao != 0);
}