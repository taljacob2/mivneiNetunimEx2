
#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "Input.h"
#include <string>

class TestRunner {

  private:
    static void runTest(std::string *&test) {
        // TODO: do something with `test` here...
    }

  public:
    static void runAllTests(std::string *&testArray, int testArraySize) {
        char delimiter = ' ';
        for (int i = 0; i < testArraySize; i++) {
            std::string *test = Input::getTest(testArray, delimiter, i);
            runTest(test);
            delete[] test;
        }
    }
};

#endif // TEST_RUNNER_H