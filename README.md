# Refatoração do código das etapas anteriores

## TODO

### cli_utils + main_* (acho que o mais indicado seja o Artur)
Sei que já estava trabalhando em refatorar o seu código. Aqui eu só deixei um pouco mais focado na etapa de benchmark e relatório. Sinta-se livre.

TL;DR:
- Leia os novos utils e adapte o código antigo (ou o seu código em desenvolvimento)

### BST, AVL, RBT (acredito que o Bruno seja o mais indicado)
BST e AVL já estão implementadas. É só uma adaptação para as novas estatísticas (não deve ser um problema). A RBT precisa ser implementada do zero. Qualquer dúvida pode me chamar.

TL;DR:
- Adaptar BST e AVL;
- Implementar RBT;
- Me chamar em caso de dúvidas.

### test_* (acredito que o mais indicado seja o Gustavo e o Kauan)
Os testes da parte anterior não devem deixar de funcionar, mas devem ser adaptados para incluir os novos atributos das structures.
Além disso, seria bom adicionar mais alguns testes, e testar as funções auxiliares (em um test_*_utils.h/cpp), para garantir que eu não fiz nada de errado (o que pode ser bem comum até). Se tiver algo de errado, entrem em contato comigo para que eu possa resolver (ou se quiserem se aventurar tentando, o código está o mais legível possível).

TL;DR:
- Adaptar os testes;
- Adicionar alguns testes novos;
- Testar as funções auxiliares e data;
- Me contatar se algo der errado.

### Documentação (qualquer um consegue contribuir bem)
Documentar os novos códigos gerados (utils e data). Conforme forem implementando novos códigos (trees, main_*, etc), ir comentando eles também (no .h).

#### IMPORTANTE
Adicionar todos os comandos de compilação no README.

Mais tarde eu vou criar um makefile, mas por enquanto salve assim (no nosso envio, terá ambas as formas de compilação, pois o makefile não funciona direito no windows, a menos que use o mingw32-make)

### Benchmark e Relatório
Precisamos que as etapas acima estejam todas concluidas (exceto documentação) para poder começar a fazer os benchmarks e os relatórios. Eu tentei estruturar de uma forma que teríamos o mínimo de trabalho para isso.