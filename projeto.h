// funçoes gerais
#ifndef PROJETO_H
#define PROJETO_H
#include "models.h"

// Utilidades gerais

void limpar_buffer_entrada(void);

void ler_string(char*buffer, int tamanho);

int ler_inteiro(void);

float ler_float(void);

void pausar_tela(void);

// Clientes 

void carregar_clientes(void);

void salvar_clientes(void);

void menu_clientes(void);

void cadastrar_cliente(void);

void buscar_cliente_cpf(void);

void buscar_cliente_nome(void);

void listar_clientes(void);

struct Cliente* buscar_cliente_por_cpf(const char* cpf);

// Pecas

void carregar_pecas(void);
void salvar_pecas(void);
void menu_pecas(void);
void cadastrar_peca(void);
void dar_baixa_peca(void);
void listar_pecas(void);
struct Peca* buscar_peca_por_nome(const char* nome);

// Servicos

void carregar_servicos(void);
void salvar_servicos(void);
void menu_servicos(void);
void cadastrar_servico(void);
void atualizar_status_servico(void);
void listar_servicos(void);
int gerar_id_servico(void);

// Relatorios

void menu_relatorios(void);
void relatorio_prontos_para_retirada(void);
void relatorio_pecas_estoque_baixo(void);
void relatorio_financeiro_mensal(void);

#endif // PROJETO_H