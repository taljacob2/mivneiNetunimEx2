
#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "Entry.h"
#include "Input.h"
#include "Polymorpher.h"
#include "PriorityQueue.h"
#include <string>

class TestRunner {

  public:
    template<typename E>
    static void runAllTests(BaseArray<std::string> &testArray) {
        auto                 priorityQueue = PriorityQueue<E>();
        PriorityQueueAdt<E> &priorityQueueAdt =
                Polymorpher::polymorphLValue<PriorityQueueAdt<E>,
                                             PriorityQueue<E>>(priorityQueue);

        for (unsigned long i = 0; i < testArray.size(); i++) {
            BaseArray<std::string> test = Input::getTest(testArray, ' ', i);
            runTest<E>(test, priorityQueueAdt);
        }

        // priorityQueueAdt.print(std::cout); // TODO: bug here.
    }

  private:
    template<typename E>
    static void runTest(BaseArray<std::string> &test,
                        PriorityQueueAdt<E> &   priorityQueueAdt) {
        // TODO: do something with `test` here...
        invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
                test, priorityQueueAdt);
    }

  private:
    template<typename E>
    static void invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
            BaseArray<std::string> &test,
            PriorityQueueAdt<E> &   priorityQueueAdt) {
        // TODO: print debug
        // std::cout << test;

        try {
            char methodLetterToInvokeInPriorityQueue = test.getElement(0)[0];
            if (methodLetterToInvokeInPriorityQueue == 'a') {
                std::cout << priorityQueueAdt.max();
            } else if (methodLetterToInvokeInPriorityQueue == 'b') {
                std::cout << priorityQueueAdt.deleteMax();
            } else if (methodLetterToInvokeInPriorityQueue == 'c') {
                std::cout << priorityQueueAdt.min();
            } else if (methodLetterToInvokeInPriorityQueue == 'd') {
                std::cout << priorityQueueAdt.deleteMin();
            } else if (methodLetterToInvokeInPriorityQueue == 'e') {
                priorityQueueAdt.createEmpty();
            } else if (methodLetterToInvokeInPriorityQueue == 'f') {
                Entry<int, std::string> entry(stoi(test.getElement(1)),
                                              test.getElement(1));
                priorityQueueAdt.insert(&entry);
            } else if (methodLetterToInvokeInPriorityQueue == 'g') {
                std::cout << priorityQueueAdt.median();
            }
        } catch (std::exception &e) {

            // TODO: remember to throw inside PriorityQueue.
            /*
             * Should occur when trying to delete and the priority-queue is
             * already empty.
             */
            // std::cout << Constants::WRONG_INPUT << std::endl;
            throw;
        }
    }
};

#endif // TEST_RUNNER_H
