#ifndef SIMPLE_TREETEST_H
#define SIMPLE_TREETEST_H
#include <iostream>
#include <chrono>

struct TestCase {
    const char* name;
    double executionTime;
    bool passed;
};

class SimpleTestFramework {
private:
    int totalTests = 0;
    int passedTests = 0;
    
public:
    TestCase initTest(const char* name) {
        TestCase test;
        test.name = name;
        test.passed = true;
        test.executionTime = 0;
        return test;
    }
    
    void endTest(TestCase& test, std::chrono::high_resolution_clock::time_point initialTime) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        test.executionTime = std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(currentTime - initialTime).count();
    }
    
    void assertTrue(TestCase& test, bool condition, const char* failureMessage) {
        if (!condition) {
            std::cout << "FALHOU: " << test.name << " - " << failureMessage << std::endl;
            test.passed = false;
        }
    }
    
    void assertFalse(TestCase& test, bool condition, const char* failureMessage) {
        if (condition) {
            std::cout << "FALHOU: " << test.name << " - " << failureMessage << std::endl;
            test.passed = false;
        }
    }
    
    void assertNotNull(TestCase& test, void* pointer, const char* failureMessage) {
        if (pointer == nullptr) {
            std::cout << "FALHOU: " << test.name << " - " << failureMessage << std::endl;
            test.passed = false;
        }
    }
    
    void assertNull(TestCase& test, void* pointer, const char* failureMessage) {
        if (pointer != nullptr) {
            std::cout << "FALHOU: " << test.name << " - " << failureMessage << std::endl;
            test.passed = false;
        }
    }
    
    void runTest(TestCase test) {
        totalTests++;
        if (test.passed) {
            passedTests++;
            std::cout << "✓ PASSOU: " << test.name << " (" << test.executionTime << " μs)" << std::endl;
        } else {
            std::cout << "✗ FALHOU: " << test.name << " (" << test.executionTime << " μs)" << std::endl;
        }
    }
    
    void printSummary() {
        std::cout << "\n=== RESUMO DOS TESTES ===" << std::endl;
        std::cout << "Total de testes: " << totalTests << std::endl;
        std::cout << "Testes que passaram: " << passedTests << std::endl;
        std::cout << "Testes que falharam: " << (totalTests - passedTests) << std::endl;
        if (passedTests == totalTests) {
            std::cout << "✓ TODOS OS TESTES PASSARAM!" << std::endl;
        } else {
            std::cout << "✗ ALGUNS TESTES FALHARAM!" << std::endl;
        }
    }
};

#endif // SIMPLE_TREETEST_H
