
#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "Input.h"
#include "PriorityQueue.h"
#include <string>

class TestRunner {

  public:
    static void runAllTests(std::string *&testArray, int testArraySize) {
        PriorityQueue<int, std::string> priorityQueue(false);

        for (int i = 0; i < testArraySize; i++) {
            std::string *test = Input::getTest(testArray, ' ', i);
            runTest(test, priorityQueue);
            delete[] test;
        }
    }

  private:
    static void runTest(std::string *&                   test,
                        PriorityQueue<int, std::string> &priorityQueue) {
        // TODO: do something with `test` here...
    }
};

#endif // TEST_RUNNER_H
