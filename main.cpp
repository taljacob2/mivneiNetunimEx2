#include "Constants.h"
#include "Input.h"
#include "MaxHeap.h"
#include "MinHeap.h"
#include "TestRunner.h"
#include <iostream>

/**
 * @mainpage mivnei_netunim targil tichnuti 2
 *
 * @author Tal Yacob, ID: 208632778.
 * @version 1.0
 */
int main() {
    std::string *testArray = nullptr;
    try {
        int testArraySize = 0;
        testArray         = Input::getTestArray(testArraySize);

        TestRunner::runAllTests(testArray, testArraySize);

        // TODO: testing heaps:
        PriorityQueueAdt<int, std::string> *priorityQueue =
                new PriorityQueue<int, std::string>();

        Entry<int, std::string> entry(3, "hello");
        priorityQueue->insert(entry);
        // std::cout << "min is: " << (priorityQueue->min());
        // priorityQueue->insert(&entry);
        // priorityQueue->insert(new Entry<int, std::string>(4, "yes"));
        // priorityQueue->insert(new Entry<int, std::string>(5, "hi"));
        // priorityQueue->insert(new Entry<int, std::string>(2, "hey"));
        // priorityQueue->insert(new Entry<int, std::string>(1, "no"));
        // priorityQueue->insert(new Entry<int, std::string>(7, "oye"));
        // std::cout << "root is: " << *(priorityQueue->root());
        // priorityQueue->print(std::cout, *priorityQueue);
        // std::cout << priorityQueue;
        delete priorityQueue;

        delete[] testArray;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        delete[] testArray;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
