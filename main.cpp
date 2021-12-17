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
    try {
        auto testArray = Input::getTestArray();

        // TestRunner::runAllTests(testArray);

        // TODO: testing heaps:
        auto  priorityQueue = PriorityQueue<int, std::string>();
        auto &priorityQueueAdt =
                Polymorpher::polymorphLValue<PriorityQueueAdt<int, std::string>,
                                             PriorityQueue<int, std::string>>(
                        priorityQueue);

        auto  minHeap = MinHeap<int, std::string>(1);
        auto &heap    = Polymorpher::polymorphLValue<HeapAdt<int, std::string>,
                                                  MinHeap<int, std::string>>(
                minHeap);

        Entry<int, std::string> entry(3, "hello");
        heap.insert(&entry);
        // Entry<int, std::string> entry2(32, "hey");
        // heap->insert(&entry2);
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
        std::cout << "root is: " << *(heap.getRoot());
        // priorityQueue->print(std::cout, *priorityQueue);
        heap.print(std::cout, heap);
        // std::cout << priorityQueue;
        // delete priorityQueue;
        // delete heap;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
