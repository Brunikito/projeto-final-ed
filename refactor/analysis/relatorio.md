# Relatório Projeto Final

# Sobre o projeto

Este projeto consiste na implementação de um **índice invertido**, uma estrutura de dados fundamental para sistemas de busca, utilizando três tipos de árvores binárias em C++: a Árvore Binária de Busca (BST) simples, a Árvore AVL e a Árvore Rubro-Negra (RBT), ambas autobalanceadas.

O objetivo principal é realizar uma **análise comparativa de desempenho** entre elas. Para isso, o programa mede métricas como tempo de inserção e busca, número de comparações e altura da árvore ao processar um grande volume de documentos de texto.

O sistema é operado via linha de comando, permitindo indexar os documentos e realizar buscas por palavras específicas. O resultado é um estudo prático sobre as vantagens e desvantagens de cada estrutura de árvore em um cenário de aplicação real.

# 1 - Estruturas

Conforme especificado no enunciado do trabalho, todas as implementações de árvore compartilham um conjunto de `structs` como base.

## 1.1 - `Node` e `BinaryTree`

Cada `Node` das armazenam a palavra, uma lista de IDs de documentos, ponteiros para os nós adjacentes e metadados para as lógicas de balanceamento.

```cpp
struct Node {
    std::string word;
    std::vector<int> documentIds;
    Node* parent;
    Node* left;
    Node* right;
    int height;    // Usado na AVL e BST
    int isRed;     // Usado na RBT (0 para preto, 1 para vermelho)
};

struct BinaryTree {
    Node* root;
    Node* NIL;  // Nó sentinela usado na RBT
};
```

## 1.2 - BST

### **Relatório de Análise da Implementação da Árvore de Busca Binária (BST)**

### 1.2.1 - Visão Geral

O projeto é uma implementação em C++ de uma Árvore de Busca Binária (BST) clássica, cujo propósito é funcionar como um índice invertido, mapeando palavras a uma lista de documentos onde elas aparecem. A arquitetura geral do software é notável: ela combina uma implementação de BST fundamentalmente simples e *não balanceada* com um conjunto extremamente sofisticado de ferramentas para medição de desempenho e análise estrutural da árvore.

### 1.2.2 - Arquitetura e Componentes

O código é bem modularizado, dividindo as responsabilidades em diferentes namespaces e arquivos:

- **Namespace `BST` (`bst.h`, `bst.cpp`)**: Contém a lógica central da árvore. Define a interface pública para criar, inserir, buscar e destruir a árvore.
- **Namespace `DATA` (`data.h`, `data.cpp`)**: Responsável por toda a etapa de pré-processamento dos dados. Suas funções leem arquivos de um diretório, ordenam-nos e extraem as palavras que serão inseridas na árvore.
- **Utilitários de Árvore (`tree_utils.h`, `tree_utils.cpp`)**: Fornece as definições das estruturas de dados essenciais (`Node`, `BinaryTree`). Além disso, oferece um robusto conjunto de funções para análise estatística (cálculo de altura, largura, verificação de balanceamento) e para a visualização da árvore em formato de texto.
- **Utilitários de Valores (`value_utils.h`)**: Uma biblioteca de funções genéricas (template) que oferece operações matemáticas e algoritmos de ordenação como o `heapSort`.

### 1.2.3 Estruturas de Dados

As estruturas, definidas em `tree_utils.h`, são a base do sistema:

- **`struct Node`**: Representa um nó da árvore.
    - `word` (`std::string`): A chave de ordenação e busca.
    - `documentIds` (`std::vector<int>`): A lista de IDs de documentos, que efetivamente torna a árvore um índice invertido.
    - `parent`, `left`, `right`: Ponteiros que formam a estrutura da árvore.
    - `height` e `isRed`: Campos para altura e cor, respectivamente. Os comentários no código indicam explicitamente que eles **não são usados na BST**, mas sim preparados para futuras implementações de árvores AVL e Rubro-Negra.
- **`struct BinaryTree`**: Um contêiner para a árvore que armazena o ponteiro para a `root` e um ponteiro `NIL`, que também é marcado como **não usado na BST**.
- **`struct InsertResult` e `SearchResult`**: Estruturas para retornar métricas detalhadas de cada operação. Elas incluem `executionTime`, `numComparisons` e, nas versões mais recentes do código, `insertDepth` e `searchDepth` para registrar a profundidade da operação na árvore.

### 1.2.4 Funcionalidades Principais (Namespace `BST`)

A lógica da árvore, conforme descrita em `bst.h` e implementada em `bst.cpp`:

- **`create()`**: Aloca e retorna uma nova `BinaryTree` com a raiz nula.
- **`insert()`**: Insere uma palavra na árvore. Se a palavra já existe, apenas o `documentId` é adicionado ao vetor do nó existente. Se é uma nova palavra, um nó é criado na posição correta. Notavelmente, após a criação de um novo nó, a função percorre os ancestrais até a raiz para **atualizar o campo `height`**, embora essa informação não seja usada para balancear a árvore.
- **`search()`**: Implementa o algoritmo de busca padrão, navegando pela árvore com base na comparação de strings. Retorna uma estrutura `SearchResult` com o resultado e estatísticas detalhadas.
- **`destroy()`**: Libera toda a memória da árvore de forma segura, usando uma função auxiliar recursiva (`destroyNode`) que executa um percurso em pós-ordem para deletar os nós.

### 1.2.5 Pré-processamento de Dados (Namespace `DATA`)

O módulo `data.cpp` é crucial para entender o comportamento do sistema.

- A função `readFiles` lista os arquivos de um diretório e os ordena para garantir uma ordem de processamento consistente.
- Para cada arquivo, ela extrai as palavras e, em seguida, **ordena essas palavras** (usando `sortWords` ou `ValueUtils::heapSort`, dependendo da versão do arquivo) antes de retorná-las.

### 1.2.6 Análise Crítica da Implementação

**Pontos Fortes:**

- **Instrumentação para Comparação**: O sistema foi projetado para uma análise de performance detalhada. O retorno de `numComparisons`, `executionTime` e `insertDepth` em cada operação permite uma medição precisa da eficiência.
- **Estrutura de Análise Robusta**: O conjunto de funções em `tree_utils` para calcular altura, balanceamento, perfeição, completude e uso de memória é extremamente poderoso para avaliar a qualidade estrutural da árvore resultante.
- **Código Modular e Documentado**: A separação em namespaces e os comentários claros no estilo Doxygen facilitam a compreensão e a manutenção do código.

**Pontos Fracos e Falhas de Design:**

- **A Falha Fundamental: Ausência de Autobalanceamento**: A implementação é de uma BST clássica, que não realiza qualquer tipo de rotação ou reestruturação para manter o balanceamento. Esta é a sua maior vulnerabilidade.
- **Cenário de Pior Caso Induzido pelo Próprio Sistema**: O ponto mais crítico é que o módulo de pré-processamento **ordena as palavras de cada documento antes da inserção**. Inserir dados pré-ordenados em uma BST simples é o método canônico para gerar uma árvore degenerada (com a forma de uma lista ligada). Isso significa que a arquitetura do sistema ativamente cria as piores condições possíveis para a estrutura de dados escolhida, resultando em um desempenho de busca e inserção de complexidade O(n) em vez de O(logn).
- **Computação Desperdiçada**: A função `insert` gasta tempo de CPU para atualizar o campo `height` de todos os ancestrais de um novo nó. Como esse valor não é usado para acionar um balanceamento, esse cálculo é totalmente supérfluo para a funcionalidade da árvore, representando um desperdício de recursos.

## 1.3 - AVL

### 1.3.1 Visão Geral

O código implementa uma Árvore AVL, que é uma Árvore de Busca Binária (BST) auto-balanceada. O objetivo da estrutura, assim como a BST analisada anteriormente, é funcionar como um índice invertido, mapeando palavras a uma lista de IDs de documentos. A principal diferença e vantagem desta implementação é a sua capacidade de manter a árvore balanceada através de rotações, garantindo um desempenho eficiente e previsível para as operações de inserção e busca. A implementação utiliza o campo `height` dos nós para calcular o fator de balanceamento e acionar as rotações necessárias.

### 1.3.2 Estrutura e Funções Principais

A implementação está contida no namespace `AVL` e é definida em `avl.h` e `avl.cpp`. Suas funções principais podem ser divididas em operações de gerenciamento da árvore e mecânicas de autobalanceamento.

**Operações de Gerenciamento:**

- **`create()`**: Aloca memória para uma nova `BinaryTree`, inicializando sua raiz como nula.
- **`insert()`**: A função de interface pública para inserção. Ela inicia a medição do tempo, chama a função recursiva `insertNode` para realizar a inserção e o rebalanceamento, e retorna uma estrutura `InsertResult` com estatísticas detalhadas.
- **`search()`**: Realiza uma busca padrão de BST. Por a árvore ser balanceada, seu desempenho é otimizado. A função retorna uma estrutura `SearchResult`.
- **`destroy()`**: Libera toda a memória alocada pela árvore, utilizando uma função auxiliar recursiva (`destroyNode`) que percorre a árvore em pós-ordem para deletar todos os nós de forma segura.

**Mecânicas de Autobalanceamento:**

- **`height()` e `updateHeight()`**: Funções para obter e atualizar a altura de um nó. A altura de um nó é definida como 1+max(altura do filho esquerdo, altura do filho direito).
- **`getBalance()`**: Calcula o fator de balanceamento de um nó, que é a diferença entre a altura da subárvore direita e a altura da subárvore esquerda (altura(direita)−altura(esquerda)).
- **`rightRotate()` e `leftRotate()`**: Implementam as rotações simples à direita e à esquerda, respectivamente. Essas são as operações fundamentais para reestruturar a árvore e corrigir desbalanceamentos. O código inclui diagramas ASCII que ilustram as rotações.
- **`rebalance()`**: Esta é a função central do mecanismo de autobalanceamento. Após uma inserção, ela verifica o fator de balanceamento de um nó. Se o fator for menor que -1 ou maior que 1, a função determina o tipo de rotação necessária (simples ou dupla) e a executa para restaurar o balanceamento da árvore.
- **`insertNode()`**: Uma função recursiva que realiza a inserção de um novo nó de maneira semelhante a uma BST padrão. No entanto, após a inserção, em cada passo da "volta" da recursão, ela chama `updateHeight` e `rebalance` para garantir que a propriedade AVL seja mantida em todos os nós ancestrais.

### 1.3.3 Lógica de Inserção e Rebalanceamento

O processo de inserção na Árvore AVL é o seguinte:

1. A função `insert` chama `insertNode`, que desce recursivamente na árvore para encontrar a posição correta para a nova palavra, assim como em uma BST comum.
2. Se a palavra já existe, o ID do documento é simplesmente adicionado ao vetor do nó existente.
3. Se a palavra não existe, um novo nó é criado e inserido.
4. Na "subida" da recursão, para cada nó no caminho de volta à raiz, sua altura é atualizada e a função `rebalance` é chamada.
5. A função `rebalance` verifica o fator de balanceamento. Se um desbalanceamento é detectado (fator `> 1` ou `< -1`), as seguintes ações são tomadas:
    - **Desbalanceamento à Esquerda (`balance < -1`)**:
        - Se o fator de balanceamento do filho esquerdo for positivo, uma rotação dupla (Esquerda-Direita) é executada: primeiro uma rotação à esquerda no filho esquerdo, seguida por uma rotação à direita no nó atual. A estatística `numRotations.LR` é incrementada.
        - Caso contrário, uma rotação simples à Direita é executada. A estatística `numRotations.RR` é incrementada.
    - **Desbalanceamento à Direita (`balance > 1`)**:
        - Se o fator de balanceamento do filho direito for negativo, uma rotação dupla (Direita-Esquerda) é executada: primeiro uma rotação à direita no filho direito, seguida por uma rotação à esquerda no nó atual. A estatística `numRotations.RL` é incrementada.
        - Caso contrário, uma rotação simples à Esquerda é executada. A estatística `numRotations.LL` é incrementada.

### 1.3.4 Pré-processamento de Dados (Namespace `DATA`)

O módulo `data.cpp` é crucial para entender o comportamento do sistema.

- A função `readFiles` lista os arquivos de um diretório e os ordena para garantir uma ordem de processamento consistente.
- Para cada arquivo, ela extrai as palavras e, em seguida, **ordena essas palavras** (usando `sortWords` ou `ValueUtils::heapSort`, dependendo da versão do arquivo) antes de retorná-las.

### 1.3.5 Mecanismos Internos e Funcionalidades de Autobalanceamento

Estas são as funções auxiliares que implementam a lógica central da Árvore AVL, garantindo que ela se mantenha balanceada após cada inserção.

- **Gerenciamento de Altura:**
    - **`int height(Node* node, InsertResult& stats)`**: Retorna a altura de um nó. Se o nó for nulo, retorna 0.
    - **`void updateHeight(Node* node, InsertResult& stats)`**: Recalcula e atualiza o campo `height` de um nó com base na altura máxima de seus filhos, mais um.
- **Cálculo de Balanceamento:**
    - **`int getBalance(Node* node, InsertResult& stats)`**: Calcula o "fator de balanceamento" de um nó, que é a diferença entre a altura da subárvore direita e a da subárvore esquerda. Um valor diferente de -1, 0 ou 1 indica que o nó está desbalanceado.
- **Operações de Rotação:**
    - **`Node* rightRotate(Node* y, InsertResult& stats)`**: Executa uma rotação simples para a direita. Esta operação é usada para corrigir um desbalanceamento "à esquerda" (casos Esquerda-Esquerda). A função rearranja os ponteiros dos nós e seus pais e, em seguida, atualiza suas alturas. O código-fonte inclui um diagrama ASCII que ilustra essa manobra.
    - **`Node* leftRotate(Node* y, InsertResult& stats)`**: Executa uma rotação simples para a esquerda, usada para corrigir um desbalanceamento "à direita" (casos Direita-Direita). Assim como a rotação à direita, ela atualiza os ponteiros e as alturas dos nós envolvidos.
- **Lógica de Rebalanceamento e Inserção:**
    - **`Node* rebalance(Node* node, InsertResult& stats)`**: É o cérebro do mecanismo de autobalanceamento. Esta função verifica o fator de balanceamento de um nó e, se ele estiver desbalanceado, determina qual tipo de rotação é necessária:
        - **Rotação Simples (Direita ou Esquerda)**: Para casos de desbalanceamento Esquerda-Esquerda ou Direita-Direita.
        - **Rotação Dupla (Esquerda-Direita ou Direita-Esquerda)**: Para casos de desbalanceamento Esquerda-Direita ou Direita-Esquerda. Uma rotação dupla consiste em uma rotação no filho seguida por uma rotação no próprio nó.
        - A função também incrementa contadores específicos (`numRotations.LR`, `numRotations.RR`, etc.) para registrar o tipo de rotação realizada.
    - **`Node* insertNode(Node* root, ...)`**: É a função recursiva que efetivamente insere o nó na árvore. Ela desce até a posição correta como uma BST padrão e, no caminho de volta da recursão, chama `updateHeight` e `rebalance` para cada nó ancestral, garantindo que a propriedade de balanceamento da AVL seja mantida em toda a árvore.

### 1.3.6 Análise e Conclusões

**Pontos Fortes:**

- **Desempenho Garantido**: A principal vantagem desta implementação é a garantia de que a altura da árvore seja mantida em O($logn$), onde n é o número de nós. Isso assegura que as operações de inserção e busca tenham uma complexidade de tempo de pior caso de O(logn), eliminando o risco de degeneração da árvore que existia na implementação da BST simples.
- **Implementação Correta**: A lógica para cálculo de altura, fator de balanceamento e as quatro manobras de rotação (simples e duplas) está corretamente implementada de acordo com o algoritmo clássico da Árvore AVL.
- **Instrumentação Detalhada**: Assim como a BST, a implementação da AVL coleta estatísticas detalhadas, incluindo o número de rotações de cada tipo (`numRotations`), o que é extremamente útil para análises de desempenho e fins acadêmicos.
- **Manutenção de Ponteiros de Pai**: A implementação atualiza corretamente os ponteiros `parent` durante as rotações, uma etapa importante que é por vezes omitida em implementações mais simples, mas que é crucial para certas aplicações ou algoritmos iterativos.

**Limitações:**

- **Complexidade de Implementação**: A lógica da AVL é inerentemente mais complexa que a de uma BST simples, como pode ser visto pelo número de funções auxiliares dedicadas ao balanceamento.
- **Overhead de Rotações**: Cada inserção pode desencadear até duas rotações (no caso de rotação dupla) para manter o balanceamento. Embora isso garanta um bom desempenho assintótico, o custo constante de inserção na AVL é ligeiramente maior que na BST devido às verificações de balanceamento e possíveis rotações.

**Conclusão:**

A implementação da Árvore AVL é uma solução robusta e eficiente para o problema do índice invertido. Ela resolve a falha fundamental da implementação da BST simples ao introduzir o mecanismo de autobalanceamento, garantindo um desempenho logarítmico estável, mesmo para grandes volumes de dados ou para dados de entrada ordenados. É uma estrutura de dados superior à BST para aplicações que exigem desempenho previsível e escalável.

## 1.4 - RBT

### **Relatório de Análise da Implementação da Árvore Rubro-Negra (RBT)**

### 1. Visão Geral

O código implementa uma Árvore Rubro-Negra, um outro tipo de árvore de busca binária autobalanceada. Assim como as implementações de BST e AVL, seu propósito é servir como um índice invertido. O balanceamento na RBT não é alcançado através de um fator de balanceamento de altura (como na AVL), mas sim através de um conjunto de propriedades baseadas na coloração dos nós (vermelho ou preto). Após cada inserção, a árvore é verificada e reestruturada através de rotações e re-colorações para garantir que essas propriedades sejam mantidas.

Uma característica fundamental desta implementação é o uso de um **nó sentinela `NIL`**, que representa todas as folhas da árvore, simplificando a lógica de balanceamento.

### 2. Funcionalidades Públicas (API do Namespace `RBT`)

Estas são as funções expostas pela interface `rbt.h` para manipulação da árvore.

- **`BinaryTree* create()`**
    - **Funcionalidade**: Aloca memória para a árvore e, crucialmente, cria um nó sentinela `NIL`. Este nó `NIL` é preto e serve como filho para todos os nós que não têm um filho real (as folhas), além de ser seu próprio pai e filho. A raiz da árvore inicialmente aponta para este nó `NIL`.
- **`InsertResult insert(BinaryTree* tree, const std::string& word, int documentId)`**
    - **Funcionalidade**: É a função de interface para inserção. Ela orquestra o processo: primeiro chama `insertNode` para realizar uma inserção padrão de BST e colorir o novo nó como vermelho. Se um novo nó foi de fato criado, ela então chama `fixInsert` para corrigir quaisquer violações das propriedades da RBT. Finalmente, ela garante que a raiz da árvore seja sempre preta, uma das propriedades fundamentais da RBT. Retorna a estrutura `InsertResult` com estatísticas da operação.
- **`SearchResult search(BinaryTree* tree, const std::string& word)`**
    - **Funcionalidade**: Executa uma busca eficiente ($O(logn)$) pela árvore. A busca é iterativa e usa o nó `NIL` como condição de parada, em vez de `nullptr`.
- **`void destroy(BinaryTree* tree)`**
    - **Funcionalidade**: Libera toda a memória associada à árvore. Ela utiliza a função recursiva `destroyNode`, que usa o `NIL` como caso base, e ao final deleta também o próprio nó sentinela `NIL`.

### 3. Mecanismos Internos e Lógica de Autobalanceamento

A "magia" da RBT reside em sua lógica interna de inserção e correção, que mantém a árvore aproximadamente balanceada.

- **Inserção Inicial (`insertNode`)**
    - **Funcionalidade**: Diferente da AVL, a inserção aqui é **iterativa**. A função percorre a árvore para encontrar a posição correta para a nova palavra.
    - Um novo nó é criado com seus filhos apontando para o `NIL`.
    - Crucialmente, todo novo nó inserido é inicialmente colorido como **VERMELHO** (`isRed = true`). Se essa coloração violar as propriedades da RBT (especificamente, um pai vermelho), a função `fixInsert` é chamada para corrigir.
- **Lógica de Correção (`fixInsert`)**
    - **Funcionalidade**: Este é o coração do algoritmo de balanceamento da RBT. A função opera em um laço que continua enquanto o pai do nó atual também for vermelho (uma violação da "propriedade do vermelho"). A lógica de correção depende da cor do "tio" do nó (o irmão do pai):
        - **Caso 1: Tio é VERMELHO**: Este é o caso mais simples. O pai e o tio são recoloridos para preto, e o avô é recolorido para vermelho. O problema é então "movido" para cima na árvore, e o laço continua a partir do avô.
        - **Caso 2: Tio é PRETO**: Este caso é mais complexo e requer rotações.
            - Se o nó forma um "triângulo" com seu pai e avô, uma rotação inicial é feita para transformá-lo em um caso de "linha".
            - Em seguida, uma rotação é realizada no avô e as cores do pai e do avô são trocadas. Isso resolve a violação da propriedade do vermelho, e o laço termina.
- **Operações de Rotação (`leftRotate` e `rightRotate`)**
    - **Funcionalidade**: São as mesmas operações estruturais vistas na AVL, usadas para rearranjar subárvores. No contexto da RBT, elas são chamadas pela `fixInsert` para resolver os casos em que o tio do nó inserido é preto.

### 4. Análise e Conclusões

**Pontos Fortes:**

- **Desempenho de Inserção Eficiente**: As árvores RBT geralmente superam as árvores AVL em cenários com muitas inserções. O número de rotações para uma única inserção é baixo (no máximo duas), enquanto a maioria das correções envolve apenas re-colorações, que são operações mais rápidas.
- **Desempenho de Busca Garantido**: Assim como a AVL, a RBT garante uma altura logarítmica ($O(logn)$), o que se traduz em um desempenho de busca, inserção e remoção no pior caso de $O(logn)$.
- **Implementação Clássica e Robusta**: O código segue fielmente o algoritmo canônico da RBT, incluindo o uso inteligente do nó sentinela `NIL`, que elimina a necessidade de muitas verificações de ponteiros nulos, tornando o código mais limpo e menos propenso a erros.

**Limitações e Complexidade:**

- **Algoritmo Mais Complexo**: As regras de balanceamento da RBT (análise de casos do tio, re-colorações e rotações) são consideradas menos intuitivas do que o fator de balanceamento numérico da AVL, o que pode tornar o código mais difícil de entender e depurar.
- **Balanceamento Menos Rígido**: Uma RBT não é tão estritamente balanceada quanto uma AVL. O caminho mais longo do topo à base pode ser até duas vezes o comprimento do caminho mais curto. Isso pode, em teoria, levar a tempos de busca ligeiramente mais lentos em média, embora a complexidade assintótica permaneça a mesma.

**Conclusão:**

A implementação da RBT é uma solução de alto desempenho e industrialmente comprovada para o problema de manter uma árvore de busca balanceada. Ela oferece garantias de desempenho logarítmico semelhantes à AVL, mas com um custo potencialmente menor para operações de escrita (inserções). A escolha entre RBT e AVL muitas vezes se resume a uma troca entre a complexidade do algoritmo e as otimizações para operações de leitura (AVL) versus escrita (RBT).

# 2. Divisão de tarefas

## Bruno Cavalli

### Contribuições:

- Bruno Cavalli assumiu a frente da instrumentação de benchmarks e da implementação inicial da AVL. Ele começou organizando a estrutura básica do repositório, criando diretórios e realocando arquivos para as pastas corretas. Em seguida, concentrou-se na leitura do corpus: escreveu rotinas que percorrem diretórios e carregam milhares de documentos-texto, permitindo que o índice invertido fosse alimentado com um fluxo contínuo de dados reais.
- No âmbito dos algoritmos, Bruno desenvolveu a inserção, as rotações e o balanceamento da AVL, além de testes unitários específicos para validar as funções de altura e fator de balanceamento. Depois de sucessivas tentativas, refinou a lógica da árvore para torná-la compatível com o framework de testes do grupo. Paralelamente, implementou os benchmarks da BST e, em seguida, da AVL, padronizando a coleta de métricas de tempo, número de comparações e altura da árvore. Para facilitar a análise posterior, acrescentou ao bench_bst uma exportação automática de resultados em formato CSV, o que permitiu gerar gráficos diretamente no Python ou em planilhas.
- Bruno também deu manutenção ao módulo value_utils, documentando e ampliando suas funções, e manteve o repositório limpo ao remover arquivos executáveis e temporários. Durante todo o processo, sincronizou a sua bruno2branch com as branches principais (main e blzrefactor), resolvendo conflitos ligados a benchmarks e leitura de dados. Graças ao seu trabalho, a equipe pôde colher dados brutos confiáveis para a análise comparativa e contar com uma AVL funcional e testada.
- Benchmarks e geração de dados brutos
- Implementou o benchmark da BST e, em seguida, do benchmark da AVL, padronizando a coleta de tempo, altura e comparações.
- Adicionou exportação automática para CSV no bench_bst, facilitando a criação de gráficos no relatório.
- Implementação e testes da AVL
- Desenvolveu as funções de inserção, rotações e balanceamento da AVL; criou testes unitários para getBalance e height.
- Refinou a AVL após tentativas iniciais, resolvendo erros de lógica e garantindo compatibilidade com o framework de testes.
- Leitura de corpus e utilitários
- Escreveu rotinas de leitura de arquivos na main e no módulo data, possibilitando indexar diretórios inteiros de documentos.
- Documentou e expandiu value_utils.
- Estrutura inicial do repositório
- Criou diretórios base e organizou arquivos nas pastas corretas logo no começo do projeto.
- Integração e sincronização
- Fez merges frequentes de blzrefactor e main para a sua bruno2branch, resolvendo conflitos relacionados a benchmarks e leitura de dados.
- Sincronizou suas contribuições com as de outros membros, mantendo o fluxo de trabalho contínuo.
- Limpeza e manutenção
- Removeu arquivos executáveis de teste e temporários, mantendo o repositório enxuto.
- Atualizou documentação auxiliar no README.

## Bruno Rosa

### Contribuições:

- Durante o desenvolvimento do projeto, Kauan Kevem atuou como líder de documentação e integração de código. Coube-lhe garantir que todas as estruturas de dados — BST, AVL e RBT — e os módulos auxiliares estivessem plenamente documentados e padronizados. Ele redigiu e refinou os cabeçalhos (*.h) de cada componente, incluindo descrições detalhadas, exemplos de uso e tags Doxygen para facilitar a leitura e a geração automática de referências. Manteve o [README.md](http://readme.md/) constantemente atualizado com instruções claras de compilação e execução, contribuindo decisivamente para a reprodutibilidade do trabalho.
- Além da documentação, Kauan desempenhou o papel de integrador de branches, realizando múltiplos merges entre as ramificações main, kauan, blzbranch e kauanrefactor, resolvendo conflitos e assegurando um histórico de commits limpo e coerente. Cada integração envolveu revisão criteriosa do código produzido pelos colegas, verificando a compatibilidade com as especificações do projeto e alinhando os comentários técnicos às implementações finais. Dessa forma, garantiu que toda nova funcionalidade viesse acompanhada de documentação atualizada, permitindo que o restante da equipe se concentrasse nas otimizações de desempenho, nos testes de unidade e na análise comparativa das estruturas.
- Documentação técnica completa
- Escreveu e padronizou cabeçalhos (*.h) de todos os módulos centrais (bst, avl, rbt, tree_utils, data, bench_utils, treetest, less_than), inserindo descrições, pré-condições, pós-condições, exemplos de uso e tags Doxygen.
- Realizou revisões sucessivas (mais de 10 commits entre 4 e 18/06) para harmonizar estilo, corrigir imprecisões e manter consistência entre declarações e implementações.
- Manutenção do README e guias de uso
- Atualizou o [README.md](http://readme.md/) com instruções de compilação (make), execução dos binários e exemplos de chamadas da CLI (search, stats), garantindo reprodutibilidade para avaliadores e colegas.
- Integração de branches e controle de versões
- Conduziu múltiplos merges (main, kauan, blzbranch, kauanrefactor), resolvendo conflitos de código e documentação.
- Validou cada integração com revisões de código (“pull-request review”) e commits assinados/“Verified”, mantendo o histórico linear e rastreável.
- Padronização de estilo e comentários
- Criou convenções de nomenclatura e comentários que foram adotadas por todo o time.
- Inseriu exemplos mínimos nos cabeçalhos para uso automático em testes unitários.
- Suporte à equipe
- Disponibilizou templates de docstring e checklist de boas práticas, agilizando o trabalho de quem focou em algoritmos e benchmark.
- Atuou como ponto de contato para dúvidas sobre Doxygen e estrutura de pastas.