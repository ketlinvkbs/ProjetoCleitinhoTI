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
int proximo_id_servico = 1; // Mantendo o controle de ID para serviços

struct Peca estoque[MAX_REGISTROS];
int total_pecas = 0;

#define ARQUIVO_CLIENTES "clientes.dat"
#define ARQUIVO_SERVICOS "servicos.dat"
#define ARQUIVO_ESTOQUE "estoque.dat"

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
        // Tratar erro de leitura, se necessário
        str[0] = '\0';
        return;
    }
    // Remover o newline se estiver presente
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    } else {
        // Se o newline não foi lido, o buffer precisa ser limpo
        limpar_buffer_entrada();
    }
}

void carregar_clientes(void) {
    FILE *f;
    int count;

    f = fopen(ARQUIVO_CLIENTES, "rb");
    if (f) {
        count = fread(&total_clientes, sizeof(int), 1, f);
        if (count == 1 && total_clientes > 0) {
            fread(clientes, sizeof(struct Cliente), total_clientes, f);
        } else {
            total_clientes = 0;
        }
        fclose(f);
    }
}

void salvar_clientes(void) {
    FILE *f;

    f = fopen(ARQUIVO_CLIENTES, "wb");
    if (f) {
        fwrite(&total_clientes, sizeof(int), 1, f);
        fwrite(clientes, sizeof(struct Cliente), total_clientes, f);
        fclose(f);
    } else {
        printf("ERRO: Não foi possível salvar os dados dos clientes.\n");
    }
}

void carregar_servicos(void) {
    FILE *f;
    int count;

    f = fopen(ARQUIVO_SERVICOS, "rb");
    if (f) {
        count = fread(&total_servicos, sizeof(int), 1, f);
        if (count == 1 && total_servicos > 0) {
            fread(servicos, sizeof(struct Servico), total_servicos, f);
            proximo_id_servico = servicos[total_servicos - 1].id + 1;
        } else {
            total_servicos = 0;
            proximo_id_servico = 1;
        }
        fclose(f);
    }
}

void salvar_servicos(void) {
    FILE *f;

    f = fopen(ARQUIVO_SERVICOS, "wb");
    if (f) {
        fwrite(&total_servicos, sizeof(int), 1, f);
        fwrite(servicos, sizeof(struct Servico), total_servicos, f);
        fclose(f);
    } else {
        printf("ERRO: Não foi possível salvar os dados dos serviços.\n");
    }
}

void carregar_pecas(void) {
    FILE *f;
    int count;

    f = fopen(ARQUIVO_ESTOQUE, "rb");
    if (f) {
        count = fread(&total_pecas, sizeof(int), 1, f);
        if (count == 1 && total_pecas > 0) {
            fread(estoque, sizeof(struct Peca), total_pecas, f);
        } else {
            total_pecas = 0;
        }
        fclose(f);
    }
}

void salvar_pecas(void) {
    FILE *f;

    f = fopen(ARQUIVO_ESTOQUE, "wb");
    if (f) {
        fwrite(&total_pecas, sizeof(int), 1, f);
        fwrite(estoque, sizeof(struct Peca), total_pecas, f);
        fclose(f);
    } else {
        printf("ERRO: Não foi possível salvar os dados do estoque.\n");
    }
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
