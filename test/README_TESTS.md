# Testes BST - README

## Visão Geral

Este arquivo `test_bst.cpp` contém uma suíte completa de testes para a implementação da Árvore Binária de Busca (BST) utilizando o framework de teste personalizado `TreeTest`.

## Arquivo Criado

- **test_bst.cpp**: Arquivo principal de testes com 12 casos de teste abrangentes

## Testes Implementados

### 1. Testes Básicos de Estrutura
- **testCreateTree**: Verifica a criação correta da árvore
- **testDestroyTree**: Testa a destruição segura da árvore

### 2. Testes de Inserção
- **testInsertFirstElement**: Inserção do primeiro elemento em árvore vazia
- **testInsertDuplicateWord**: Inserção de palavra duplicada (deve adicionar novo documentId)
- **testMultipleInserts**: Inserção múltipla criando estrutura de árvore
- **testPerformanceWithManyElements**: Teste de desempenho com 15 elementos

### 3. Testes de Busca
- **testSearchEmptyTree**: Busca em árvore vazia
- **testSearchFoundElement**: Busca encontrando elemento existente
- **testSearchNotFoundElement**: Busca não encontrando elemento
- **testSearchInSpecificPosition**: Busca em posição específica da árvore

### 4. Testes de Robustez
- **testInsertNullTree**: Inserção com ponteiro de árvore NULL
- **testSearchNullTree**: Busca com ponteiro de árvore NULL

## Como Compilar

```bash
cd "/c/Users/guguo/OneDrive/Área de Trabalho/FGV/estrutura_de_dados/projeto-final-ed"
g++ -o test_bst test/test_bst.cpp test/treetest.cpp src/bst.cpp -I. -std=c++11
```

## Como Executar

```bash
./test_bst
```

## Saída Esperada

```
Running Tests
-------------
Test testCreateTree passed in 0us.
-----------
Test testInsertFirstElement passed in 0us.
-----------
Test testInsertDuplicateWord passed in 0us.
-----------
Test testMultipleInserts passed in 0us.
-----------
Test testSearchEmptyTree passed in 0us.
-----------
Test testSearchFoundElement passed in 0us.
-----------
Test testSearchNotFoundElement passed in 0us.
-----------
Test testSearchInSpecificPosition passed in 0us.
-----------
Test testPerformanceWithManyElements passed in 0us.
-----------
Test testDestroyTree passed in 0us.
-----------
Test testInsertNullTree passed in 0us.
-----------
Test testSearchNullTree passed in 0us.
-----------

Summary:
12 Tests Passed.
0 Tests Failed.
All tests passed!
```

## Características dos Testes

### Cobertura Funcional
- ✅ Criação e destruição de árvore
- ✅ Inserção em árvore vazia
- ✅ Inserção de elementos duplicados
- ✅ Inserção múltipla formando estrutura de árvore
- ✅ Busca em árvore vazia
- ✅ Busca encontrando elementos
- ✅ Busca não encontrando elementos
- ✅ Tratamento de casos de erro (árvore NULL)

### Métricas Testadas
- ✅ Número de comparações
- ✅ Tempo de execução
- ✅ Integridade dos documentIds
- ✅ Estrutura correta da árvore
- ✅ Comportamento com casos extremos

### Validações
- ✅ Ponteiros não nulos quando esperado
- ✅ Ponteiros nulos quando esperado
- ✅ Valores corretos de retorno
- ✅ Estrutura de dados consistente
- ✅ Tratamento de erros

## Framework de Teste Utilizado

O arquivo utiliza o framework `TreeTest` que fornece:
- **Estrutura TestCase**: Para organizar informações do teste
- **Funções de Assert**: assertTrue, assertFalse, assertNull, assertNotNull
- **Medição de Tempo**: Automaticamente mede tempo de execução
- **Relatórios Coloridos**: Verde para sucesso, vermelho para falha
- **Estatísticas**: Resumo final com contadores de sucesso/falha

## Arquivos Relacionados

- `test/treetest.h`: Header do framework de teste
- `test/treetest.cpp`: Implementação do framework de teste  
- `src/bst.h`: Header da BST sendo testada
- `src/bst.cpp`: Implementação da BST sendo testada

## Status do Projeto

✅ **CONCLUÍDO**: Arquivo test_bst.cpp funcional e todos os testes passando
