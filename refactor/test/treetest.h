#ifndef TREETEST_H
#define TREETEST_H
#include <vector>
#include <string>
#include <chrono>

/** 
 * TreeTest - Um simples framework de testes para o projeto
 * ----------------------------------
 * Para criar um teste, basta criar uma função de tipo TestCase.
 * Dentro dela, faça um initTest com o nome da função, e guarde o tempo inicial.
 * Em seguida, utilize as funções assertivas como assertTrue, assertFalse, etc.
 * Essas funções irão atualizar o TestCase com o resultado da verificação.
 * Chame endTest passando o TestCase e o tempo inicial.
 * Finalize com o retorno do TestCase.
 * 
 * Exemplo:
 * TestCase myTest() {
 *     auto initialTime = std::chrono::high_resolution_clock::now();
 *     TestCase test = initTest("myTest");
 *     assertTrue(test, condition, "Condition failed"); 
 *     endTest(test, initialTime);
 *     return test;
 * }
 * ----------------------------------
 * Para executar todos os testes e imprimir os resultados, basta chamar initTestCases().
 * Em seguida, adicione os testes com addTest passando o vetor retornado por initTestCases()
 * Por fim, imprima os resultados com printTestResults.
 * 
 * Exemplo:
 * int main(){
 * auto allTests = initTestCases();
 * addTest(allTests, myTest());
 * printTestResults(allTests);
 * return 0;
 * }
 * 
*/
namespace TreeTest {
    // Estrutura do teste
    /**
     * @struct TestCase
     * @brief Metadados de um teste individual.
     *
     * @var name  Identificador textual do teste.
     * @var executionTime  Duração em **microssegundos** contabilizada por ::endTest.
     * @var passed  Verdadeiro se todas as assertivas passaram.
     */
    struct TestCase {
        const char* name;
        double executionTime;
        bool passed;
    };

    // Funções auxiliares
    /**
     * @brief Imprime @p val em verde.
     * @tparam T Tipo imprimível via operator<<.
     */
    template <typename T>
    void printGreen(const T& val);

    /**
     * @brief Imprime @p val em vermelho.
     * @tparam T Tipo imprimível via operator<<.
     */
    template <typename T>
    void printRed(const T& val);

    // Funções de Teste
    /**
     * @brief Inicializa e devolve o vetor que armazenará todos os testes.
     * @return Vetor vazio de TestCase pronto para receber ::addTest.
     */
    std::vector<TestCase> initTestCases();
    /**
     * @brief Cria um TestCase marcado como "passou".
    * @param name Identificador textual do teste.
    * @return Estrutura inicializada.
    */
    TestCase initTest(const char* name);
    /**
     * @brief Fecha o teste calculando o tempo total decorrido.
     * @param test        TestCase a ser atualizado.
     * @param initialTime Ponto de partida medido antes da lógica de teste.
     */
    void endTest(TestCase& test, std::chrono::system_clock::time_point initialTime);
    /**
     * @brief Adiciona um TestCase ao vetor "mestre".
     */
    void addTest(std::vector<TestCase>& allTests, TestCase test);
    /**
     * @brief Percorre @p tests, imprime o resultado individual e o resumo final.
     */
    void printTestResults(const std::vector<TestCase>& tests);

    // Assertivas
    /**
     * @brief Falha se @p condition for `false`.
     * @param test           TestCase de destino.
     * @param condition      Condição a verificar.
     * @param failureMessage Mensagem exibida em caso de falha.
     */
    void assertTrue(TestCase& test, bool condition, const char* failureMessage);
    /**
     * @brief Falha se @p condition for `true`.
     * @param test           TestCase de destino.
     * @param condition      Condição a verificar.
     * @param failureMessage Mensagem exibida em caso de falha.
     */
    void assertFalse(TestCase& test, bool condition, const char* failureMessage);
    /**
     * @brief Falha se @p pointer for `nullptr`.
     * @param test           TestCase de destino.
     * @param pointer        Ponteiro a verificar.
     * @param failureMessage Mensagem exibida em caso de falha.
     */
    void assertNotNull(TestCase& test, void* pointer, const char* failureMessage);
    /**
     * @brief Falha se @p pointer **não** for `nullptr`.
     * @param test           TestCase de destino.
     * @param pointer        Ponteiro a verificar.
     * @param failureMessage Mensagem exibida em caso de falha.
     */
    void assertNull(TestCase& test, void* pointer, const char* failureMessage);
}

#endif // TREETEST_H