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
        HeapAdt<int, std::string> *heap = new MinHeap<int, std::string>();
        heap->insert(new Entry<int, std::string>(3, "hello"));
        heap->insert(new Entry<int, std::string>(4, "yes"));
        heap->insert(new Entry<int, std::string>(5, "hi"));
        heap->insert(new Entry<int, std::string>(2, "hey"));
        heap->insert(new Entry<int, std::string>(1, "no"));
        heap->insert(new Entry<int, std::string>(7, "oye"));
        std::cout << "root is: " << *(heap->root());
        heap->print(std::cout, *heap);


        delete[] testArray;
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        delete[] testArray;
        return Constants::MAIN_ERROR;
    }

    return 0;
}
