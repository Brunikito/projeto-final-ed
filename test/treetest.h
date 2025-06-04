/** 
 * TreeTest - A simple testing framework for the project
 * Para criar um teste, basta criar uma função de tipo TestCase
 * Dentro dela, faça um initTest com o nome da função
 * execute as verificações necessárias passando o TestCase
 * e finalize com o retorno do TestCase.
 * Exemplo:
 * TestCase myTest() {
 *     auto initialTime = std::chrono::high_resolution_clock::now();
 *     TestCase test = initTest("myTest");
 *     assertTrue(&test, condition, "Condition failed");
 *     endTest(&test, initialTime);
 *     return test;
 * }
 *
 * Para rodar todos os testes, basta chamar initTestCases(),
 * adicionar os testes criados ao vetor retornado e chamar printTestResults(tests).
 * Exemplo:
 * 
 * int main(){
 * auto allTests = initTestCases();
 * addTest(&alltTests, myTest());
 * printTestResults(&allTests);
 * return 0;
 * }
 * 
*/

#ifndef TREETEST_H
#define TREETEST_H
#include <vector>
#include <string>

namespace TreeTest {
    // Estrutura do teste
    struct TestCase {
        const char* name;
        double executionTime;
        bool passed;
    };

    // Funções auxiliares
    template <typename T>
    void printGreen(const T& val);

    template <typename T>
    void printRed(const T& val);

    // Funções de Teste
    std::vector<TestCase> initTestCases();
    TestCase initTest(const char* name);
    void endTest(TestCase& test);
    void addTest(std::vector<TestCase>& allTests, TestCase test);
    void printTestResults(const std::vector<TestCase>& tests);

    // Assertivas
    void assertTrue(TestCase& test, bool condition, const char* failureMessage);
    void assertFalse(TestCase& test, bool condition, const char* failureMessage);
    void assertNotNull(TestCase& test, void* pointer, const char* failureMessage);
    void assertNull(TestCase& test, void* pointer, const char* failureMessage);
}

#endif // TREETEST_H