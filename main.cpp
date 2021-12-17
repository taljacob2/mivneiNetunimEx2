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
    // try {
        auto testArray = Input::getTestArray();

        // TODO: print test
        // std::cout << testArray << std::endl;

        // TestRunner::runAllTests(testArray);

        // TODO: testing heaps:
        // PriorityQueueAdt<int, std::string> *priorityQueue =
        //         new PriorityQueue<int, std::string>();

        HeapAdt<int, std::string> *heap = new MinHeap<int, std::string>();

        Entry<int, std::string> entry(3, "hello");
        heap->insert(&entry);
        // TestRunner::runAllTests(testArray);
        // priorityQueue->insert(entry);
        // std::cout << "min is: " << (priorityQueue->min());
        // heap->insert(new Entry<int, std::string>(5, "hi"));
        // heap->insert(new Entry<int, std::string>(2, "hey"));
        // heap->insert(new Entry<int, std::string>(1, "no"));
        // heap->insert(new Entry<int, std::string>(7, "oye"));
        // heap->insert(&(Entry<int, std::string>(9, "yoyo")));
        // heap->insert(&(Entry<int, std::string>(9, "yoyo")));
        // std::cout << "root is: " << *(priorityQueue->root());
        std::cout << "root is: " << *(heap->getRoot());
        // priorityQueue->print(std::cout, *priorityQueue);
        heap->print(std::cout, *heap);
        // std::cout << priorityQueue;
        // delete priorityQueue;
        delete heap;
    // } catch (std::exception &e) {
    //     std::cout << e.what() << std::endl;
    //     return Constants::MAIN_ERROR;
    // }

    return 0;
}
