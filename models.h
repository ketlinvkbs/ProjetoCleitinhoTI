// estrutura dos dados
#ifndef MODELS_H
#define MODELS_H

// Contantes
#define MAX_NOME 100
#define MAX_TELEFONE 15
#define MAX_EMAIL 100
#define MAX_CPF 15
#define MAX_NOME_PECA 100
#define MAX_DESCRICAO_PROBLEMA 200
#define MAX_STATUS 30
#define MAX_DATA 11


// Estrutura dos dados

struct Cliente 
{
    char nome[MAX_NOME];
    char telefone[MAX_TELEFONE];
    char email[MAX_EMAIL];
    char cpf[MAX_CPF];
    int ativo;
};

struct Peca 
{
    char nome[MAX_NOME_PECA];
    float preco;
    int quantidade;
    int ativa;
};

struct Servico
{
    int id;
    char cpf_cliente[MAX_CPF];
    char descricao_problema[MAX_DESCRICAO_PROBLEMA];
    float valor;
    char status[MAX_STATUS];
    char data_entrada[MAX_DATA];
    int urgente;
    int ativo;
};

#endif // MODELS_H