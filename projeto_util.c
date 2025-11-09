#include "projeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_REGISTROS 100 

struct Cliente clientes[MAX_REGISTROS];
int total_clientes = 0;

struct Servico servicos[MAX_REGISTROS];
int total_servicos = 0;
int proximo_id_servico = 1;

struct Peca estoque[MAX_REGISTROS];
int total_pecas = 0;

#define ARQUIVO_CLIENTES "clientes.txt"
#define ARQUIVO_SERVICOS "servicos.txt"
#define ARQUIVO_ESTOQUE "estoque.txt"

void limpar_buffer_entrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_inteiro(void) {
    int num;
    while (scanf("%d", &num) != 1) {
        printf("Entrada inválida. Por favor, digite um número inteiro: ");
        limpar_buffer_entrada();
    }
    limpar_buffer_entrada();
    return num;
}

float ler_float(void) {
    float num;
    while (scanf("%f", &num) != 1) {
        printf("Entrada inválida. Por favor, digite um número decimal: ");
        limpar_buffer_entrada();
    }
    limpar_buffer_entrada();
    return num;
}

void ler_string(char *str, int max_len) {
    if (fgets(str, max_len, stdin) == NULL) {
        str[0] = '\0';
        return;
    }
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        limpar_buffer_entrada();
    }
}


void salvar_clientes(void) {
    FILE *f = fopen(ARQUIVO_CLIENTES, "w");
    if (!f) {
        printf("ERRO: Não foi possível salvar os dados dos clientes.\n");
        return;
    }
    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].ativo) {
            fprintf(f, "%s;%s;%s;%s\n",
                    clientes[i].cpf,
                    clientes[i].nome,
                    clientes[i].telefone,
                    clientes[i].email);
        }
    }
    fclose(f);
}

void salvar_servicos(void) {
    FILE *f = fopen(ARQUIVO_SERVICOS, "w");
    if (!f) {
        printf("ERRO: Não foi possível salvar os dados dos serviços.\n");
        return;
    }
    // Salva o próximo ID na primeira linha
    fprintf(f, "%d\n", proximo_id_servico); 
    
    for (int i = 0; i < total_servicos; i++) {
        if (servicos[i].ativo) {
            // Salva os campos na ordem correta, com descrição por último
            fprintf(f, "%d;%s;%f;%s;%s;%d;%s\n",
                    servicos[i].id,
                    servicos[i].cpf_cliente,
                    servicos[i].valor,
                    servicos[i].status,
                    servicos[i].data_entrada,
                    servicos[i].urgente,
                    servicos[i].descricao_problema
            );
        }
    }
    fclose(f);
}

void salvar_pecas(void) {
    FILE *f = fopen(ARQUIVO_ESTOQUE, "w");
    if (!f) {
        printf("ERRO: Não foi possível salvar os dados do estoque.\n");
        return;
    }
    for (int i = 0; i < total_pecas; i++) {
        if (estoque[i].ativa) {
            fprintf(f, "%s;%d;%f\n",
                    estoque[i].nome,
                    estoque[i].quantidade,
                    estoque[i].preco); 
        }
    }
    fclose(f);
}


void carregar_clientes(void) {
    FILE *f = fopen(ARQUIVO_CLIENTES, "r"); 
    if (!f) return; 
    total_clientes = 0;
    char linha[1024]; 

    while (fgets(linha, sizeof(linha), f) != NULL && total_clientes < MAX_REGISTROS) {
   
        int result = sscanf(linha, "%[^;];%[^;];%[^;];%[^\n]\n",
                            clientes[total_clientes].cpf,
                            clientes[total_clientes].nome,
                            clientes[total_clientes].telefone,
                            clientes[total_clientes].email);
        
        if (result == 4) { 
            clientes[total_clientes].ativo = 1;
            total_clientes++;
        }
    }
    fclose(f);
}

void carregar_servicos(void) {
    FILE *f = fopen(ARQUIVO_SERVICOS, "r");
    if (!f) return;

    total_servicos = 0;
    char linha[1024];

    if (fgets(linha, sizeof(linha), f) != NULL) {
        sscanf(linha, "%d\n", &proximo_id_servico);
    } else {
        proximo_id_servico = 1; 
        fclose(f);
        return;
    }

    while (fgets(linha, sizeof(linha), f) != NULL && total_servicos < MAX_REGISTROS) {
        int result = sscanf(linha, "%d;%[^;];%f;%[^;];%[^;];%d;%[^\n]\n",
                            &servicos[total_servicos].id,
                            servicos[total_servicos].cpf_cliente,
                            &servicos[total_servicos].valor,
                            servicos[total_servicos].status,
                            servicos[total_servicos].data_entrada,
                            &servicos[total_servicos].urgente,
                            servicos[total_servicos].descricao_problema
                            );
                            
        if (result == 7) {
            servicos[total_servicos].ativo = 1;
            total_servicos++;
        }
    }
    fclose(f);
}

void carregar_pecas(void) {
    FILE *f = fopen(ARQUIVO_ESTOQUE, "r");
    if (!f) return;
    
    total_pecas = 0;
    char linha[1024];

    while (fgets(linha, sizeof(linha), f) != NULL && total_pecas < MAX_REGISTROS) {

        int result = sscanf(linha, "%[^;];%d;%f\n",
                            estoque[total_pecas].nome,
                            &estoque[total_pecas].quantidade,
                            &estoque[total_pecas].preco);
        
        if (result == 3) {
            estoque[total_pecas].ativa = 1;
            total_pecas++;
        }
    }
    fclose(f);
}

void carregar_dados(void) {
    carregar_clientes();
    carregar_servicos();
    carregar_pecas();
}

void salvar_dados(void) {
    salvar_clientes();
    salvar_servicos();
    salvar_pecas();
}

// Funções de Busca
struct Cliente* buscar_cliente_por_cpf(const char* cpf) {
    for (int i = 0; i < total_clientes; i++) {
        if (clientes[i].ativo && strcmp(clientes[i].cpf, cpf) == 0) {
            return &clientes[i];
        }
    }
    return NULL;
}

struct Peca* buscar_peca_por_nome(const char* nome) {
    for (int i = 0; i < total_pecas; i++) {
        if (estoque[i].ativa && strcmp(estoque[i].nome, nome) == 0) {
            return &estoque[i];
        }
    }
    return NULL;
}

struct Servico* encontrar_servico_por_id(int id) {
    for (int i = 0; i < total_servicos; i++) {
        if (servicos[i].ativo && servicos[i].id == id) {
            return &servicos[i];
        }
    }
    return NULL;
}

int gerar_id_servico(void) {
    return proximo_id_servico++;
}

void pausar_tela(void) {
    printf("\nPressione ENTER para continuar...");
    limpar_buffer_entrada();
    getchar();
}