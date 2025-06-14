projeto-final/
│
├── data/
│   └── *.txt                 # Documentos .txt para indexação
│
├── docs/
│   └── *.pdf                 # Documentos .txt para indexação
│
├── src/
│   ├── utils/
│   │   ├── tree_utils.cpp / tree_utils.h        # Structs (Node, etc.) e funções aux.
│   │   └── bench_utils.cpp/ bench_utils.h    # Structs e funções para benchmarck
│   ├── main_bst.cpp          # CLI da BST
│   ├── main_avl.cpp          # CLI da AVL
│   ├── main_rbt.cpp          # CLI da RBT
│   ├── bst.cpp               # Implementação da BST
│   ├── avl.cpp               # Implementação da AVL
│   ├── rbt.cpp               # Implementação da RBT
│   ├── bst.h                 # Cabeçalho da BST
│   ├── avl.h                 # Cabeçalho da AVL
│   ├── rbt.h                 # Cabeçalho da RBT
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
├── benchmark/ 
│   ├── results/
│   │   ├── bst.csv           # Resultados da BST
│   │   ├── avl.csv           # Resultados da AVL
│   │   └── rbt.csv           # Resultados da RBT
│   ├── treebench.h           # Cabeçalho do framework de benchmark 
│   ├── treebench.cpp         # Implementação do framework de benchmark 
│   ├── bench_bst.cpp         # Testes da BST
│   ├── bench_avl.cpp         # Testes da AVL
│   └── bench_rbt.cpp         # Testes da RBT
│ 
├── analysis/
│   ├── graphs/
│   │   ├── bst.png           # Gráfico da BST
│   │   ├── avl.png           # Gráfico da AVL
│   │   ├── rbt.png           # Gráfico da RBT
│   │   └── all.png           # Comparação entre todas as árvores
│   ├── bst.py                # Análise da BST
│   ├── avl.py                # Análise da AVL
│   ├── rbt.py                # Análise da RBT
│   └── all.py                # Comparação entre todas as árvores
│
├── .gitignore
├── Makefile
└── README.md                 # Este arquivo
```