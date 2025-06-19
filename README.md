# Projeto Final - Estruturas de Dados

## Visão Geral

Este projeto implementa e compara três estruturas de árvores de busca binária para indexação e busca de palavras em documentos de texto: **Binary Search Tree (BST)**, **AVL Tree** e **Red-Black Tree (RBT)**. O sistema oferece análise completa de performance, testes automatizados e ferramentas de benchmark para comparação entre as diferentes implementações.

## Estrutura do Projeto

```
projeto-final-ed/
├── src/                    # Código fonte principal
│   ├── bst.cpp/.h         # Implementação Binary Search Tree
│   ├── avl.cpp/.h         # Implementação AVL Tree
│   ├── rbt.cpp/.h         # Implementação Red-Black Tree
│   ├── data.cpp/.h        # Módulo de leitura de dados
│   ├── main_*.cpp         # Programas principais para cada estrutura
│   └── utils/             # Utilitários e estruturas auxiliares
│       ├── tree_utils.h   # Estruturas base (Node, BinaryTree)
│       ├── bench_utils.h  # Estruturas de estatísticas
│       ├── cli_utils.h    # Interface de linha de comando
│       ├── value_utils.h  # Funções de ordenação
│       └── less_than.h    # Comparadores personalizados
├── test/                  # Sistema de testes automatizados
│   ├── test_*.cpp         # Testes unitários para cada estrutura
│   ├── treetest.h/.cpp    # Framework de testes personalizado
│   └── README_TESTS.md    # Documentação dos testes
├── benchmark/             # Programas de benchmark
│   ├── bench_*.cpp        # Medição de performance
│   └── results/          # Resultados dos benchmarks (CSV)
├── analysis/              # Análise de dados e visualização
│   ├── *.py              # Scripts Python para análise
│   └── graphs/           # Gráficos de performance gerados
├── data/                 # Dataset de documentos de texto
│   └── *.txt            # Arquivos numerados (0.txt até 1139.txt)
└── Makefile             # Sistema de compilação
```

## Compilação

O projeto utiliza um sistema de compilação baseado em Makefile que compila automaticamente todos os executáveis necessários.

### Pré-requisitos

- **Compilador**: GCC/G++ com suporte ao C++17
- **Sistema Operacional**: Linux, macOS ou Windows (com ferramentas Unix)

### Comando de Compilação

```bash
make
```

Este comando:
- Cria o diretório `build/` automaticamente
- Compila todos os arquivos fonte com flags otimizadas
- Gera os executáveis na pasta `build/`

### Limpeza dos Arquivos Compilados

```bash
make clean
```

## Executáveis Gerados

Após a compilação, os seguintes executáveis estarão disponíveis em `build/`:

### Programas Principais
- **`build/bst`** - Binary Search Tree
- **`build/avl`** - AVL Tree  
- **`build/rbt`** - Red-Black Tree

### Programas de Teste
- **`build/test_bst`** - Testes unitários BST
- **`build/test_avl`** - Testes unitários AVL
- **`build/test_rbt`** - Testes unitários RBT

### Programas de Benchmark
- **`build/bench_bst`** - Benchmark BST
- **`build/bench_avl`** - Benchmark AVL
- **`build/bench_rbt`** - Benchmark RBT

## Utilização dos Programas Principais

Os programas principais seguem uma interface padronizada de linha de comando:

```bash
./build/<programa> <comando> <n_docs> <diretorio>
```

### Parâmetros

- **`<programa>`**: Um dos executáveis (`bst`, `avl`, `rbt`)
- **`<comando>`**: 
  - `search` - Modo interativo de busca por palavras
  - `stats` - Geração de estatísticas de performance durante indexação
- **`<n_docs>`**: Número de documentos a processar (inteiro positivo)
- **`<diretorio>`**: Caminho para a pasta contendo os arquivos `.txt`

### Exemplos de Uso

#### Modo de Busca Interativa
```bash
./build/bst search 100 data/
./build/avl search 500 data/
./build/rbt search 1000 data/
```

No modo `search`, o programa:
1. Carrega e indexa os documentos especificados
2. Entra em modo interativo para busca de palavras
3. Retorna os IDs dos documentos que contêm cada palavra buscada
4. Exibe estatísticas de performance da busca

#### Modo de Estatísticas
```bash
./build/bst stats 100 data/
./build/avl stats 500 data/  
./build/rbt stats 1000 data/
```

No modo `stats`, o programa:
1. Processa os documentos coletando métricas detalhadas
2. Exibe estatísticas de inserção (comparações, rotações, profundidade)
3. Mostra estatísticas da árvore final (altura, balanceamento)
4. Apresenta tempos de execução em microssegundos

## Sistema de Testes

### Execução dos Testes

```bash
./build/test_bst    # Testa Binary Search Tree
./build/test_avl    # Testa AVL Tree
./build/test_rbt    # Testa Red-Black Tree
```

### Framework de Testes

O projeto inclui um framework de testes personalizado (`TreeTest`) que oferece:

- **Estrutura TestCase**: Organização dos metadados de teste
- **Funções Assertivas**: `assertTrue`, `assertFalse`, `assertNull`, `assertNotNull`
- **Medição Automática**: Tempo de execução de cada teste
- **Relatórios Coloridos**: Verde para sucesso, vermelho para falha
- **Estatísticas Finais**: Resumo com contadores de sucesso/falha

### Testes Implementados

Cada estrutura de dados possui testes abrangentes incluindo:
- Criação e inicialização da árvore
- Inserção de elementos únicos e duplicados
- Busca de elementos existentes e inexistentes
- Operações de balanceamento (AVL/RBT)
- Validação de propriedades estruturais
- Liberação de memória

## Sistema de Benchmarks

### Execução dos Benchmarks

```bash
./build/bench_bst    # Benchmark Binary Search Tree
./build/bench_avl    # Benchmark AVL Tree
./build/bench_rbt    # Benchmark Red-Black Tree
```

### Métricas Coletadas

Os benchmarks medem:
- **Tempo de Execução**: Inserções e buscas em microssegundos
- **Número de Comparações**: Operações de comparação de strings
- **Profundidade de Operações**: Profundidade alcançada nas operações
- **Rotações**: Contadores específicos (LL, RR, LR, RL) para árvores balanceadas
- **Recolorações**: Operações de recoloração em Red-Black Trees
- **Estatísticas da Árvore**: Altura, número de nós, fator de balanceamento

### Resultados

Os resultados são salvos em `benchmark/results/`:
- `bst.csv` - Resultados Binary Search Tree
- `avl.csv` - Resultados AVL Tree  
- `rbt.csv` - Resultados Red-Black Tree

## Análise de Dados

### Scripts de Análise

A pasta `analysis/` contém scripts Python para processamento dos resultados:
- `bst.py` - Análise específica para BST
- `avl.py` - Análise específica para AVL
- `rbt.py` - Análise específica para RBT
- `all.py` - Análise comparativa entre todas as estruturas

### Visualizações

Os gráficos gerados são salvos em `analysis/graphs/`:
- `bst.png` - Gráficos de performance BST
- `avl.png` - Gráficos de performance AVL
- `rbt.png` - Gráficos de performance RBT
- `all.png` - Comparação visual entre estruturas

## Conjunto de Dados

O diretório `data/` contém mais de 1100 arquivos de texto numerados sequencialmente (`0.txt` até `1139.txt`). Cada arquivo representa um documento com palavras que serão indexadas pelas estruturas de dados.

### Formato dos Dados
- Arquivos de texto simples
- Uma ou mais palavras por arquivo
- Numeração sequencial para facilitar processamento em lotes

## Estruturas de Dados Implementadas

### Binary Search Tree (BST)
- Implementação clássica sem balanceamento automático
- Operações: inserção, busca, destruição
- Complexidade: O(log n) médio, O(n) pior caso

### AVL Tree
- Árvore binária auto-balanceada
- Rotações automáticas (LL, RR, LR, RL)
- Complexidade: O(log n) garantido
- Controle rigoroso de altura

### Red-Black Tree (RBT)
- Árvore binária semi-balanceada
- Propriedades de coloração (vermelho/preto)
- Nó sentinela NIL para simplificação
- Complexidade: O(log n) garantido
- Menos rotações que AVL

## Funcionalidades Técnicas

### Indexação de Documentos
Cada palavra é associada a uma lista de IDs de documentos onde aparece, permitindo:
- Busca eficiente por palavra
- Recuperação de todos os documentos relevantes
- Análise de frequência de palavras

### Coleta de Métricas
Sistema abrangente de coleta de estatísticas:
- Tempo de execução em microssegundos
- Contadores de operações (comparações, rotações)
- Estatísticas agregadas (média, desvio padrão, min/max)
- Métricas específicas por tipo de árvore

### Gestão de Memória
- Alocação dinâmica controlada
- Verificação de falhas de alocação
- Liberação automática de recursos
- Prevenção de vazamentos de memória

## Requisitos do Sistema

- **Compilador**: GCC 7.0+ ou Clang 5.0+ com suporte C++17
- **Memória**: Mínimo 512MB RAM recomendado
- **Armazenamento**: 50MB para dados e executáveis
- **Sistema**: Linux, macOS, Windows (WSL/Cygwin)

## Licença e Autoria

Este projeto foi desenvolvido como trabalho final da disciplina de Estruturas de Dados. O código implementa algoritmos clássicos da literatura de estruturas de dados com foco em análise comparativa de performance.

---

**Nota**: Para execução em sistemas Windows, recomenda-se o uso do Windows Subsystem for Linux (WSL) ou ferramentas como Cygwin/MinGW que fornecem ambiente Unix compatível.
```
│
├── data/
│   └── *.txt                 # Documentos .txt para indexação
│
├── docs/
│   └── *.pdf                 # Documentos .txt para indexação
│
├── src/
│   ├── utils/
│   │   ├── tree_utils.cpp / tree_utils.h       # Structs (Node, etc.) e funções aux.
│   │   └── bench_utils.cpp/ bench_utils.h      # Structs e funções para benchmarck
│   ├── main_bst.cpp          # CLI da BST
│   ├── main_avl.cpp          # CLI da AVL
│   ├── main_rbt.cpp          # CLI da RBT
│   ├── bst.cpp / bst.h       # Implementação da BST
│   ├── avl.cpp / avl.h       # Implementação da AVL
│   ├── rbt.cpp / rbt.h       # Implementação da RBT
│   └── data.cpp / data.h     # Leitura de arquivos
│
├── test/
│   ├── treetest.h            # Cabeçalho do framework de testes
│   ├── treetest.cpp          # Implementação do framework de testes
│   ├── test_bst.cpp          # Testes da BST
│   ├── test_avl.cpp          # Testes da AVL
│   └── test_rbt.cpp          # Testes da RBT
│
├── benchmark/ 
│   ├── results/
│   │   ├── bst.csv           # Resultados da BST
│   │   ├── avl.csv           # Resultados da AVL
│   │   └── rbt.csv           # Resultados da RBT
│   ├── treebench.cpp / treebench.h                # Implementação do framework de benchmark 
│   ├── bench_bst.cpp         # Testes da BST
│   ├── bench_avl.cpp         # Testes da AVL
│   └── bench_rbt.cpp         # Testes da RBT
│ 
├── analysis/
│   ├── graphs/
│   │   └── *.png             # Gráficos resultantes
│   ├── bst.py                # Análise da BST
│   ├── avl.py                # Análise da AVL
│   ├── rbt.py                # Análise da RBT
│   └── all.py                # Comparação entre todas as árvores
│
├── .gitignore
├── Makefile
└── README.md                 # Este arquivo
```