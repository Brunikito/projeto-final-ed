## Estrutura de Arquivos

```
projeto-final-ed/
│
...
├── test/
│   ├── treetest.h            # Cabeçalho do framework de testes
│   ├── treetest.cpp          # Implementação do framework de testes
│   ├── test_bst.cpp          # Testes da BST
│   ├── test_avl.cpp          # Testes da AVL
│   └── test_rbt.cpp          # Testes da RBT
└── ...
```


## Framework de Teste Utilizado

O arquivo utiliza o framework `TreeTest` que fornece:
- **Estrutura TestCase**: Para organizar informações do teste
- **Funções de Assert**: assertTrue, assertFalse, assertNull, assertNotNull
- **Medição de Tempo**: Automaticamente mede tempo de execução
- **Relatórios Coloridos**: Verde para sucesso, vermelho para falha
- **Estatísticas**: Resumo final com contadores de sucesso/falha
