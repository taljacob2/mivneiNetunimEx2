
#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include "Entry.h"
#include "Input.h"
#include "Polymorpher.h"
#include "PriorityQueue.h"
#include <string>

class TestRunner {

  public:
    static void runAllTests(BaseArray<std::string> &testArray) {
        // TODO: polymorph with adt
        PriorityQueue<Entry<int, std::string>> priorityQueue;
        // PriorityQueueAdt<E> *priorityQueueAdt = &priorityQueue;


        for (unsigned long i = 0; i < testArray.size(); i++) {
            BaseArray<std::string> test = Input::getTest(testArray, ' ', i);
            runTest<Entry<int, std::string>>(test, priorityQueue);
        }


        // TODO: checking methods here. bug here.
        priorityQueue.print(std::cout); // TODO: bug here.
        std::cout << "min:" << *priorityQueue.min() << std::endl;
        std::cout << "max:" << *priorityQueue.max() << std::endl;
        std::cout << "median:" << *priorityQueue.median() << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        priorityQueue.insert(Entry<int, std::string>(4, "4"));
        priorityQueue.print(std::cout); // TODO: bug here.
        std::cout << "min:" << *priorityQueue.min() << std::endl;
        std::cout << "max:" << *priorityQueue.max() << std::endl;
        std::cout << "median:" << *priorityQueue.median() << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        priorityQueue.insert(Entry<int, std::string>(5, "5"));
        priorityQueue.print(std::cout); // TODO: bug here.
        std::cout << "min:" << *priorityQueue.min() << std::endl;
        std::cout << "max:" << *priorityQueue.max() << std::endl;
        std::cout << "median:" << *priorityQueue.median() << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++" << std::endl;
        priorityQueue.insert(Entry<int, std::string>(9, "9"));
        priorityQueue.print(std::cout); // TODO: bug here.
        std::cout << "min:" << *priorityQueue.min() << std::endl;
        std::cout << "max:" << *priorityQueue.max() << std::endl;
        std::cout << "median:" << *priorityQueue.median() << std::endl;
        std::cout << "++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    }

  private:
    template<typename E>
    static void runTest(BaseArray<std::string> &test,
                        PriorityQueue<E> &      priorityQueue) {
        // TODO: do something with `test` here...
        invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
                test, priorityQueue);
    }

  private:
    static void invokeMethodInPriorityQueueBySwitchAndPrintReturnValuesIfExist(
            BaseArray<std::string> &                test,
            PriorityQueue<Entry<int, std::string>> &priorityQueue) {
        try {
            char methodLetterToInvokeInPriorityQueue = test.getElement(0)[0];
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
                priorityQueue.insert(Entry<int, std::string>(
                        stoi(test.getElement(1)),
                        test.getElement(2))); // TODO: debug disabled
                // priorityQueue.print(std::cout); // TODO: debug
            } else if (methodLetterToInvokeInPriorityQueue == 'g') {
                std::cout << priorityQueue.median();
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
