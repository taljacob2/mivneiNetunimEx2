
#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "Input.h"
#include <string>

class TestRunner {

  public:
    static void runAllTests(std::string *&testArray, int testArraySize) {
        for (int i = 0; i < testArraySize; i++) {
            std::string *test = Input::getTest(testArray, ' ', i);
            runTest(test);
            delete[] test;
        }
    }

  private:
    static void runTest(std::string *&test) {
        // TODO: do something with `test` here...
    }
};

#endif // TEST_RUNNER_H
