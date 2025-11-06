#include <stdio.h>
#include "projeto.h"

// Funções de persistência (declaradas em projeto_util.c)
extern void carregar_dados(void);
extern void salvar_dados(void);
extern int ler_inteiro(void);
extern void menu_clientes(void);
extern void menu_servicos(void);
extern void menu_pecas(void);
extern void menu_relatorios(void);

// Menu

void menu_principal(void) {
    int opcao;
    do {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("1. Módulo de Clientes\n");
        printf("2. Módulo de Serviços\n");
        printf("3. Módulo de Estoque de Peças\n");
        printf("4. Módulo de Relatórios\n");
        printf("0. Sair e Salvar\n");
        printf("Escolha uma opção: ");
        opcao = ler_inteiro();

        switch (opcao) {
            case 1: menu_clientes(); break;
            case 2: menu_servicos(); break;
            case 3: menu_pecas(); break;
            case 4: menu_relatorios(); break;
            case 0:
                salvar_dados();
                printf("Dados salvos com sucesso. Encerrando o sistema.\n");
                break;
            default:
                printf("\nOpção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);
}

// Função principal
int main(void) {
    printf("Iniciando Sistema de Gerenciamento de Assistência Técnica...\n");
    carregar_dados();
    menu_principal();
    return 0;
}
