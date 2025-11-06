# Sistema de Gerenciamento de Assistência Técnica Cleitinho TI

## Equipe Responsável

**Nome da Equipe:** 

**Participantes:**
- Gaspar Juvino |202402074047 
- Vitória Ketlin | 202402398903


**Cadeira: Estrutura de Dados** 

**Professor Responsável: Mauricio Neto** 

---

## Descrição do Projeto

Este é um sistema de gerenciamento para assistência técnica desenvolvido em linguagem C. O sistema permite o controle completo de clientes, serviços técnicos, estoque de peças e geração de relatórios, tudo através de uma interface de linha de comando.

### Funcionalidades

O sistema é dividido em 4 módulos principais:

#### 1. Módulo de Clientes
- Cadastro de novos clientes (nome, telefone, email, CPF)
- Busca de clientes por CPF ou nome
- Listagem de todos os clientes cadastrados
- Persistência de dados em arquivo

#### 2. Módulo de Serviços
- Cadastro de novos serviços com descrição do problema
- Acompanhamento de status (em andamento, pronto para retirada, etc.)
- Vinculação de serviços a clientes
- Geração de IDs únicos para cada serviço
- Atualização do status dos serviços

#### 3. Módulo de Estoque de Peças
- Cadastro de peças (nome, preço, quantidade)
- Controle de estoque
- Baixa de peças utilizadas nos serviços
- Listagem de peças em estoque
- Identificação de peças com baixo estoque

#### 4. Módulo de Relatórios
- Relatório de serviços prontos para retirada
- Relatório de peças com estoque baixo
- Relatório financeiro mensal

## Tecnologias Utilizadas

- Linguagem C
- Estruturas de dados
- Persistência de dados em arquivos binários
- Interface de linha de comando

## Como Executar o Projeto

### Pré-requisitos
- Compilador C (como GCC)
- Sistema operacional Linux ou Windows com ambiente compatível

### Passo a Passo

1. **Clone ou baixe o repositório** (se disponível) ou copie todos os arquivos para um diretório local.

2. **Compile o projeto**:
   Abra um terminal no diretório do projeto e execute o seguinte comando:

   ```bash
   gcc -o projeto main.c clientes.c servicos.c estoque.c relatorios.c projeto_util.c -lm
   ```

   Este comando compila todos os arquivos-fonte em um único executável chamado "projeto".

3. **Execute o programa**:
   Após a compilação bem-sucedida, execute o programa com:

   ```bash
   ./projeto
   ```

4. **Siga as instruções no menu**:
   - O sistema apresentará um menu principal com as opções:
     - 1. Módulo de Clientes
     - 2. Módulo de Serviços
     - 3. Módulo de Estoque de Peças
     - 4. Módulo de Relatórios
     - 0. Sair e Salvar

5. **Utilize as funcionalidades**:
   - Navegue pelos módulos usando os números indicados
   - Cada módulo tem seu próprio submenu com opções específicas
   - Os dados são automaticamente salvos ao sair do sistema

### Observações Importantes

- O sistema salva automaticamente todos os dados ao encerrar
- Os dados são persistidos em arquivos binários no mesmo diretório do executável
- O sistema inclui tratamento de entrada para evitar erros comuns
- A navegação entre menus é feita através de opções numéricas

## Estrutura do Projeto

- `main.c`: Contém a função principal e o menu principal
- `projeto.h`: Declaração de todas as funções do sistema
- `models.h`: Definição das estruturas de dados usadas no sistema
- `clientes.c`: Implementação das funcionalidades do módulo de clientes
- `servicos.c`: Implementação das funcionalidades do módulo de serviços
- `estoque.c`: Implementação das funcionalidades do módulo de estoque de peças
- `relatorios.c`: Implementação das funcionalidades do módulo de relatórios
- `projeto_util.c`: Funções utilitárias e de persistência de dados