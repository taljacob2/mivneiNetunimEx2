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
        std::cout << "root is: " << *(heap.getRoot()) << std::endl;
        heap.print(std::cout);
        priorityQueueAdt.print(std::cout);
    } catch (std::exception &e) {
        std::cout << Constants::WRONG_INPUT << std::endl;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
