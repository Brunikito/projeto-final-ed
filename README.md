# Trabalho A2: Índice Invertido com BST - Entrega 1

Implementação da Entrega 1 do Trabalho A2, focada na construção de um índice invertido utilizando uma **Árvore Binária de Busca (BST)**, leitura de dados e CLI para busca.

## Resumo da Entrega
Para compilar os arquivos, basta ir até a pasta raíz do repositório, e executar:
```bash
g++ test/test_bst.cpp test/treetest.cpp src/bst.cpp -I. -std=c++17 -o test_tree_bst
```
```bash
g++ src/main_bst.cpp src/bst.cpp src/tree_utils.cpp src/data.cpp -std=c++17 -o run_bst
```

Para executar os arquivos, também na raíz do repositório, basta fazer o seguinte:

Para rodar os testes:
```bash
./test_tree_bst
```

Para executar o CLI no modo de busca simples do índice invertido:
```bash
./run_bst search <n_docs> <diretório>
```

Exemplo: `./run_bst search 128 ./data`.

Para executar o CLI no modo de busca com estatísticas do índice invertido:
```bash
./run_bst stats <n_docs> <diretório>
```

Exemplo: `./run_bst stats 128 ./data`.

> **Obs.:** o diretório padrão dos arquivos nesse projeto é o `./data`, mas ainda sim ele **deve** ser passado para o CLI.

## 1. Funcionalidades da Entrega 1

* Implementação da Árvore Binária de Busca (BST) para o índice invertido.
* Leitura e processamento de arquivos `.txt` de um diretório.
* Testes da implementação da árvore: `./test_tree_bst` .
* CLI para indexar documentos e buscar palavras: `./run_bst search <n_docs> <diretório>` e `./run_bst stats <n_docs> <diretório>`.

## 2. Estrutura de Arquivos (Entrega 1)

```
projeto-final/
│
│
├── data/
│   ...
│   └── *.txt                 # Documentos .txt para indexação
│
├── src/
│   ├── main_bst.cpp          # CLI da BST
│   ├── main_avl.cpp          # CLI da AVL
│   ├── main_rbt.cpp          # CLI da RBT
│   ├── bst.cpp               # Implementação da BST
│   ├── avl.cpp               # Implementação da AVL
│   ├── rbt.cpp               # Implementação da RBT
│   ├── bst.h                 # Cabeçalho da BST
│   ├── avl.h                 # Cabeçalho da AVL
│   ├── rbt.h                 # Cabeçalho da RBT
│   ├── tree_utils.cpp        # Structs (Node, etc.) e funções aux.
│   ├── tree_utils.h          # Cabeçalho de tree_utils
│   ├── data.cpp              # Leitura de arquivos
│   └── data.h                # Cabeçalho de data
│
├── test/
│   ├── treetest.h            # Cabeçalho do framework de testes
│   ├── treetest.cpp          # Implementação do framework de testes
│   ├── test_bst.cpp          # Testes da BST
│   ├── test_avl.cpp          # Testes da AVL
│   └── test_rbt.cpp          # Testes da RBT
│
├── .gitignore
└── README.md                 # Este arquivo
```

## 3. Como Compilar

É necessário um compilador C++ (ex: g++). No diretório raiz do projeto:

```bash
# Exemplo com g++
g++ test/test_bst.cpp test/treetest.cpp src/bst.cpp -I. -std=c++17 -o test_tree_bst
```

Isso gera o executável `test_tree_bst` no diretório raíz.

```bash
# Exemplo com g++
g++ src/main_bst.cpp src/bst.cpp src/tree_utils.cpp src/data.cpp -std=c++17 -o run_bst
```

Isso gera o executável `run_bst` no diretório raíz.

## 4. Como Executar
Faça tudo a seguir na pasta raíz do repositório.

### Testes:
Após compilar, execute os testes:
```bash
./test_tree_bst
```

### Índice Invertido:
Após compilar, execute o comando de busca:

```bash
./run_bst search <n_docs> <diretório_documentos>
```

Ou o comando de busca com estatísticas:

```bash
./run_bst stats <n_docs> <diretório_documentos>
```

Onde:

* `<n_docs>`: Número de documentos a indexar.
* `<diretório_documentos>`: Caminho para a pasta com os arquivos `.txt`.

Exemplo:

```bash
./run_bst search 1000 ./data
```

```bash
./run_bst stats 1000 ./data
```

O programa indexará os documentos e permitirá buscas por palavras.

> O diretório padrão dos arquivos `.txt` do nosso projeto é o diretório `./data`, mas ainda assim, ele **deve** ser passado para o CLI.

## 5. Dependências

* Compilador C++17.
* Bibliotecas padrão C++: `std::vector`, `std::string`, `std::chrono`, `std::iostream`, `std::fstream`.

## 6. Integrantes do Grupo

* [Artur Vidal Krause](https://github.com/arturvidalkrause)
* [Bruno Luis Zerbinato Rosa](https://github.com/Brunikito)
* [Bruno Cavalli](https://github.com/BrunoCavalli)
* [Gustavo Oliveira](https://github.com/GuOliv2306)
* [Kauan Kevem Sousa Farias](https://github.com/kauankevem)
