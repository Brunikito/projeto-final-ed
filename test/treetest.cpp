#include "treetest.h"
#include <vector>
#include <string>
#include <chrono>
#include <iostream>

namespace TreeTest {
    // Funções auxiliares
    template <typename T>
    void printGreen(const T& val) {
        std::cout << "\033[32m" << val << "\033[0m";
    }
    template <typename T>
    void printRed(const T& val) {
        std::cout << "\033[31m" << val << "\033[0m";
    }

    // Funções de Teste
    std::vector<TestCase> initTestCases(){
        return std::vector<TestCase>{};
    }
    TestCase initTest(const char* name){
        TestCase test;
        test.name = name;
        test.passed = true;
        test.executionTime = 0;
        return test;
    }
    void endTest(TestCase& test, std::chrono::_V2::system_clock::time_point initialTime){
        auto currentTime = std::chrono::high_resolution_clock::now();
        test.executionTime = std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(currentTime - initialTime).count();
    }
    void addTest(std::vector<TestCase>& allTests, TestCase test){
        allTests.push_back(test);
    }
    void printTestResults(const std::vector<TestCase>& tests){
        std::cout << "\nRunning Tests\n" << "-------------\n" << std::endl;
        int passedCount = 0;
        int failedCount = 0;
        double totalExecutionTime = 0;
        const char* totalExecutionTimeUnit = "us";
        
        for (auto test : tests){
            double executionTimeCorrect = test.executionTime;
            totalExecutionTime += test.executionTime;
            const char* executionTimeUnit = "us";
            if (test.executionTime > 1'000){
                executionTimeCorrect /= 1'000;
                executionTimeUnit = "ms";
            }
            if (test.executionTime > 1000){
                executionTimeCorrect /= 1000;
                executionTimeUnit = "s";
            }
            if (test.executionTime > 60){
                executionTimeCorrect /= 60;
                executionTimeUnit = "min";
            }
            if (test.executionTime > 60){
                executionTimeCorrect /= 60;
                executionTimeUnit = "h";
            }

            if (test.passed){
                printGreen("Test ");
                printGreen(test.name);
                printGreen(" passed in ");
                printGreen(executionTimeCorrect);
                printGreen(executionTimeUnit);
                printGreen(".\n");
                passedCount++;
            } else {
                printRed("Test ");
                printRed(test.name);
                printRed(" failed in ");
                printRed(executionTimeCorrect);
                printRed(executionTimeUnit);
                printRed(".\n");
                failedCount++;
            }
            std::cout << "-----------" << std::endl;
        }

        // Imprime o resumo (passou em verde e falhou em vermelho)
        std::cout << "\nSummary:\n";
        if (totalExecutionTime > 1'000){
            totalExecutionTime /= 1'000;
            totalExecutionTimeUnit = "ms";
        }
        if (totalExecutionTime > 1'000){
            totalExecutionTime /= 1'000;
            totalExecutionTimeUnit = "s";
        }
        if (totalExecutionTime > 60){
            totalExecutionTime /= 60;
            totalExecutionTimeUnit = "min";
        }
        if (totalExecutionTime > 60){
            totalExecutionTime /= 60;
            totalExecutionTimeUnit = "h";
        }

        std::cout << "Total Execution Time: " << totalExecutionTime << totalExecutionTimeUnit << std::endl;
        std::cout << passedCount << "Tests Passed." << std::endl;
        std::cout << failedCount << "Tests Failed." << std::endl;

        if (failedCount == 0) {
            printGreen("All tests passed!\n");
            return;
        }
        printRed("Some tests failed.\n");
    }

    // Assertivas
    void assertTrue(TestCase& test, bool condition, const char* failureMessage){
        if (!condition) {
            printRed(test.name);
            printRed(" failed: ");
            printRed(failureMessage);
            std::cout << std::endl;
            test.passed = false;
        }
    }
    void assertFalse(TestCase& test, bool condition, const char* failureMessage){
        if (condition) {
            printRed(test.name);
            printRed(" failed: ");
            printRed(failureMessage);
            std::cout << std::endl;
            test.passed = false;
        }
    }
    void assertNotNull(TestCase& test, void* pointer, const char* failureMessage){
        if (pointer == nullptr) {
            printRed(test.name);
            printRed(" failed: ");
            printRed(failureMessage);
            std::cout << std::endl;
            test.passed = false;
        }
    }
    void assertNull(TestCase& test, void* pointer, const char* failureMessage){
        if (pointer != nullptr) {
            printRed(test.name);
            printRed(" failed: ");
            printRed(failureMessage);
            std::cout << std::endl;
            test.passed = false;
        }
    }
}