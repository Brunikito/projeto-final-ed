/** 
 * TreeTest - A simple testing framework for the project
 * Para criar um teste, basta criar uma função de tipo TestCase
 * Dentro dela, faça um initTest com o nome da função
 * execute as verificações necessárias passando o TestCase
 * e finalize com o retorno do TestCase.
 * Exemplo:
 * TestCase myTest() {
 *     TestCase test = initTest("myTest");
 *     assertTrue(test, condition, "Condition failed");
 *     return test;
 * }
 *
 * Para rodar todos os testes, basta chamar initTestCases(),
 * adicionar os testes criados ao vetor retornado e chamar printTestResults(tests).
*/

#ifndef TREETEST_H
#define TREETEST_H
#include <vector>
#include <string>

namespace TreeTest {
    struct TestCase {
        const char* name;
        double executionTime;
        bool passed;
    };

    std::vector<TestCase> initTestCases();
    TestCase initTest(const char* name);
    void assertTrue(TestCase& test, bool condition, const char* message);
    void assertFalse(TestCase& test, bool condition, const char* message);
    void assertNotNull(TestCase& test, void* pointer, const char* message);
    void assertNull(TestCase& test, void* pointer, const char* message);
    
    void printGreen(const std::string& text);
    void printRed(const std::string& text);

    void printTestResults(const std::vector<TestCase>& tests);
}

#endif // TREETEST_H