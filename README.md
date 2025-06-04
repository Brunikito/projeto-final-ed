# Trabalho A2: Índice Invertido com BST - Entrega 1

Implementação da Entrega 1 do Trabalho A2, focada na construção de um índice invertido utilizando uma **Árvore Binária de Busca (BST)**, leitura de dados e CLI para busca.

## 1. Funcionalidades da Entrega 1

* Implementação da Árvore Binária de Busca (BST) para o índice invertido.
* Leitura e processamento de arquivos `.txt` de um diretório.
* CLI para indexar documentos e buscar palavras: `./bst search <n_docs> <diretório>`.

## 2. Estrutura de Arquivos (Entrega 1)

```
projeto-final/
│
├── src/
│   ├── main_bst.cpp          # CLI da BST
│   ├── bst.cpp               # Implementação da BST
│   ├── bst.h                 # Cabeçalho da BST
│   ├── tree_utils.cpp        # Structs (Node, etc.) e funções aux.
│   ├── tree_utils.h          # Cabeçalho de tree_utils
│   ├── data.cpp              # Leitura de arquivos
│   ├── data.h                # Cabeçalho de data
│
├── data/                     # Documentos .txt para indexação
│
└── README.md                 # Este arquivo
```

## 3. Como Compilar

É necessário um compilador C++ (ex: g++). No diretório raiz do projeto:

```bash
# Exemplo com g++
g++ src/main_bst.cpp src/bst.cpp src/tree_utils.cpp src/data.cpp -o bst -std=c++17
```

Isso gera o executável `bst` no diretório raiz.

## 4. Como Executar

Após compilar, execute o comando de busca:

```bash
./bst search <n_docs> <diretório_documentos>
```

Onde:

* `<n_docs>`: Número de documentos a indexar.
* `<diretório_documentos>`: Caminho para a pasta com os arquivos `.txt`.

Exemplo:

```bash
./bst search 1000 ./data/corpus
```

O programa indexará os documentos e permitirá buscas por palavras.

## 5. Dependências

* Compilador C++17.
* Bibliotecas padrão C++: `std::vector`, `std::string`, `chrono`, `iostream`, `fstream`.

## 6. Integrantes do Grupo

* [Artur Vidal Krause](https://github.com/arturvidalkrause)
* [Bruno Luis Zerbinato Rosa](https://github.com/Brunikito)
* [Bruno Cavalli](https://github.com/BrunoCavalli)
* [Gustavo Oliveira](https://github.com/GuOliv2306)
* [Kauan Kevem Sousa Farias](https://github.com/kauankevem)
