
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
        invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
                test, priorityQueue);
    }

  private:
    static void invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
            std::string *&                   test,
            PriorityQueue<int, std::string> &priorityQueue) {
        char methodLetterToInvokeInPriorityQueue = test[0][0];
        if (methodLetterToInvokeInPriorityQueue == 'a') {
            std::cout << priorityQueue.max();
        } else if (methodLetterToInvokeInPriorityQueue == 'b') {
            std::cout << priorityQueue.deleteMax();
        } else if (methodLetterToInvokeInPriorityQueue == 'c') {
            std::cout << priorityQueue.min();
        } else if (methodLetterToInvokeInPriorityQueue == 'd') {
            std::cout << priorityQueue.deleteMin();
        } else if (methodLetterToInvokeInPriorityQueue == 'e') {
            priorityQueue.createEmpty();
        } else if (methodLetterToInvokeInPriorityQueue == 'f') {
            Entry<int, std::string> entry(stoi(test[1]), test[2]);
            priorityQueue.insert(entry);
        } else if (methodLetterToInvokeInPriorityQueue == 'g') {
            std::cout << priorityQueue.median();
        }
    }
};

#endif // TEST_RUNNER_H
